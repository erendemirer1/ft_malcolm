#ifndef ARGS_PARSER_H
#define ARGS_PARSER_H

#include <netinet/in.h>
#include <stddef.h>


typedef struct s_program_args {
    struct in_addr      source_ip_addr;
    unsigned char       source_mac_addr[6];
    struct in_addr      target_ip_addr;
    unsigned char       target_mac_addr[6];
} t_program_args;


int parse_program_arguments(int argc, char **argv, t_program_args *args);
#endif