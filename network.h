#ifndef NETWORK_H
# define NETWORK_H

#include <netinet/in.h> // struct in_addr ve sockaddr_in için
#include <net/if.h>     // IFNAMSIZ için

// Arayüz bilgilerini tutan yapı
typedef struct s_interface_info {
    char            name[IFNAMSIZ]; // Arayüz adı (örn: eth0)
    int             index;          // Arayüz indeksi
    unsigned char   mac_addr[6];    // Arayüzün MAC adresi
    struct in_addr  ip_addr;        // Arayüzün IP adresi
} t_interface_info;

// Fonksiyon prototipi
t_interface_info *get_active_interface_info(void);

#endif