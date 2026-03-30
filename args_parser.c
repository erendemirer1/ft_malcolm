#include "args_parser.h"
#include "parsing.h"
#include <stdio.h>
#include <stdlib.h>

int parse_program_arguments(int argc, char **argv, t_program_args *args) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <source_ip> <source_mac> <target_ip> <target_mac>\n", argv[0]);
        return -1;
    }

    if (validate_ipv4_address(argv[1], &args->source_ip_addr) != 0) {
        fprintf(stderr, "%s: unknown host or invalid IP address: (%s)\n", argv[0], argv[1]);
        return -1;
    }

    if (parse_mac_address(argv[2], args->source_mac_addr) != 0) {
        fprintf(stderr, "%s: invalid mac address: (%s)\n", argv[0], argv[2]);
        return -1;
    }

    if (validate_ipv4_address(argv[3], &args->target_ip_addr) != 0) {
        fprintf(stderr, "%s: unknown host or invalid IP address: (%s)\n", argv[0], argv[3]);
        return -1;
    }

    if (parse_mac_address(argv[4], args->target_mac_addr) != 0) {
        fprintf(stderr, "%s: invalid mac address: (%s)\n", argv[0], argv[4]);
        return -1;
    }

    return 0;
}