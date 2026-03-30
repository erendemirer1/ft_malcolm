#ifndef PARSING_H
#define PARSING_H

#include <netinet/in.h>

int parse_mac_address(const char *mac_str, unsigned char *mac_array);


int validate_ipv4_address(const char *ip_str, struct in_addr *ip_addr);

#endif