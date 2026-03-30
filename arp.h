#ifndef ARP_H
#define ARP_H

#include <stdint.h>

// Ethernet header
struct eth_hdr {
    uint8_t dest_mac[6];
    uint8_t src_mac[6];
    uint16_t eth_type;
};

// ARP header
struct arp_hdr {
    uint16_t hw_type;   // Hardware Type
    uint16_t pro_type;  // Protocol Type
    uint8_t hw_len;     // Hardware Address Length
    uint8_t pro_len;    // Protocol Address Length
    uint16_t opcode;    // Operation Code
    uint8_t sender_mac[6]; // Sender hardware address
    uint8_t sender_ip[4];  // Sender IP address
    uint8_t target_mac[6]; // Target hardware address
    uint8_t target_ip[4];  // Target IP address
};

#endif