#define _GNU_SOURCE
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <net/ethernet.h>
#include <net/if_arp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv)
{
    if (argc == 5) {
        const char *source_ip = argv[1];
        const char *source_mac = argv[2];
        const char *target_ip = argv[3];
        const char *target_mac = argv[4];
        
        unsigned char buffer[65536];
        int raw_socket;
        raw_socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
        if (raw_socket < 0) {
            perror("Socket creation failed");
            return 1;
        }
        while (1)
        {
        int len = recvfrom(raw_socket, buffer, sizeof(buffer), 0, NULL, NULL);
        if (len <= 0)
            continue;
                
        struct ethhdr *eth = (struct ethhdr *)buffer;
        if (ntohs(eth->h_proto) != ETH_P_ARP)
            continue;
                
        struct ether_arp *arp = (struct ether_arp *)(buffer + sizeof (struct ethhdr));
                
        if (ntohs(arp->ea_hdr.ar_op) != ARPOP_REQUEST)
            continue;
            
        struct in_addr wanted;
        if (inet_pton(AF_INET, source_ip, &wanted) != 1)
            return 1;
                
        if (memcmp(arp->arp_tpa, &wanted, 4) != 0)
            continue;
                
        struct in_addr target;
        if (inet_pton(AF_INET, target_ip, &target) != 1)
            return 1;
                
        if (memcmp(arp->arp_spa, &target, 4) != 0)
            continue;
                
        break; // DOĞRU ARP REQUEST BULUNDU
        }


        }
    else {
        perror("Invalid number of arguments. Expected 4 arguments.\n");
        return 1;
    }
}