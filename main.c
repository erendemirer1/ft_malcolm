#include "args_parser.h"
#include "network.h"
#include "arp.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <netinet/if_ether.h>
#include <netinet/in.h>
#include <netpacket/packet.h>

volatile sig_atomic_t g_running = 1;

void sigint_handler(int signum) {
    (void)signum;
    g_running = 0;
    printf("\nCaught signal, cleaning up and exiting...\n");
}

void send_arp_reply(t_program_args *args, t_interface_info *interface, struct arp_hdr *req_arp, int sock) {
    unsigned char buffer[sizeof(struct eth_hdr) + sizeof(struct arp_hdr)];
    struct eth_hdr *eth = (struct eth_hdr *)buffer;
    struct arp_hdr *arp = (struct arp_hdr *)(buffer + sizeof(struct eth_hdr));
    struct sockaddr_ll sll;

    // Ethernet Header
    memcpy(eth->dest_mac, req_arp->sender_mac, 6);
    memcpy(eth->src_mac, args->source_mac_addr, 6);
    eth->eth_type = htons(ETH_P_ARP);

    // ARP Header
    arp->hw_type = htons(ARPHRD_ETHER);
    arp->pro_type = htons(ETH_P_IP);
    arp->hw_len = 6;
    arp->pro_len = 4;
    arp->opcode = htons(ARPOP_REPLY);
    memcpy(arp->sender_mac, args->source_mac_addr, 6);
    memcpy(arp->sender_ip, &args->source_ip_addr, 4);
    memcpy(arp->target_mac, req_arp->sender_mac, 6);
    memcpy(arp->target_ip, req_arp->sender_ip, 4);

    ft_memset(&sll, 0, sizeof(sll));
    sll.sll_family = AF_PACKET;
    sll.sll_ifindex = interface->index;

    if (sendto(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&sll, sizeof(sll)) < 0) {
        fprintf(stderr, "sendto failed: %s\n", strerror(errno));
    } else {
        printf("Sent an ARP reply packet, you may now check the arp table on the target.\n");
    }
}

void handle_arp_packet(unsigned char *buffer, ssize_t len, t_program_args *args) {
    if (len < (ssize_t)(sizeof(struct eth_hdr) + sizeof(struct arp_hdr))) return;

    struct arp_hdr *arp = (struct arp_hdr *)(buffer + sizeof(struct eth_hdr));

    if (ntohs(arp->opcode) == ARPOP_REQUEST &&
        memcmp(arp->sender_ip, &args->target_ip_addr, 4) == 0 &&
        memcmp(arp->target_ip, &args->source_ip_addr, 4) == 0)
    {
        printf("An ARP request has been broadcast.\n");
        g_running = 0; // Stop listening after handling one request
    }
}

int main(int argc, char **argv) {
    t_program_args args;
    t_interface_info *interface;
    int sock;

    if (getuid() != 0) {
        fprintf(stderr, "This program requires root privileges.\n");
        return 1;
    }

    if (parse_program_arguments(argc, argv, &args) != 0) return 1;

    signal(SIGINT, sigint_handler);

    interface = get_active_interface_info();
    if (!interface) {
        fprintf(stderr, "Failed to find a suitable network interface.\n");
        return 1;
    }
    printf("Found available interface: %s\n", interface->name);
    
    sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
    if (sock < 0) {
        fprintf(stderr, "socket: %s\n", strerror(errno));
        free(interface);
        return 1;
    }

    if (setsockopt(sock, SOL_SOCKET, SO_BINDTODEVICE, interface->name, strlen(interface->name)) < 0) {
        fprintf(stderr, "setsockopt: %s\n", strerror(errno));
        close(sock);
        free(interface);
        return 1;
    }

    printf("Waiting for ARP requests...\n");
    while (g_running) {
        unsigned char buffer[ETH_FRAME_LEN];
        ssize_t len = recvfrom(sock, buffer, sizeof(buffer), 0, NULL, NULL);
        if (len <= 0) {
            if (g_running) fprintf(stderr, "recvfrom failed\n");
            continue;
        }

        struct arp_hdr *arp = (struct arp_hdr *)(buffer + sizeof(struct eth_hdr));
        if (ntohs(arp->opcode) == ARPOP_REQUEST &&
            memcmp(arp->sender_ip, &args.target_ip_addr, 4) == 0 &&
            memcmp(arp->target_ip, &args.source_ip_addr, 4) == 0)
        {
            printf("An ARP request has been broadcast.\n");
            send_arp_reply(&args, interface, arp, sock);
            g_running = 0;
        }
    }

    close(sock);
    free(interface);
    printf("Exiting program...\n");
    return 0;
}
