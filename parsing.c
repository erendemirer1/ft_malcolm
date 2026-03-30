#include "parsing.h"
#include "libft/libft.h"
#include <arpa/inet.h>

static int hex_char_to_int(char c)
{
    if (c >= '0' && c <= '9')
        return (c - '0');
    if (c >= 'a' && c <= 'f')
        return (c - 'a' + 10);
    if (c >= 'A' && c <= 'F')
        return (c - 'A' + 10);
    return (-1);
}

int parse_mac_address(const char *mac_str, unsigned char *mac_array)
{
    int i = 0;
    int byte_index = 0;
    while (mac_str[i] && byte_index < 6)
    {
        if (mac_str[i] == '\0' || mac_str[i+1] == '\0')
            return (-1);
        int high = hex_char_to_int(mac_str[i]);
        int low = hex_char_to_int(mac_str[i+1]);

        if (high == -1 || low == -1)
            return (-1);
        mac_array[byte_index++] = (high << 4) | low;
        i += 2;
        if (mac_str[i] == ':' && byte_index < 6)
            i++;
        else if (mac_str[i] != '\0' && byte_index != 6)
            return (-1);
    }
    if (byte_index != 6 || mac_str[i] != '\0')
        return (-1);
    return (0);
}

int validate_ipv4_address(const char *ip_str, struct in_addr *ip_addr)
{
    if (inet_pton(AF_INET, ip_str, ip_addr) == 1)
    {
        return 0;
    }
    return -1;
}