#include "network.h"
#include "libft/libft.h"
#include <ifaddrs.h>
#include <netpacket/packet.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <net/if.h>

// Finds the name of the first active, non-loopback interface
static char *get_first_active_interface_name(struct ifaddrs *ifaddrs)
{
    struct ifaddrs *ifa;
    for (ifa = ifaddrs; ifa != NULL; ifa = ifa->ifa_next)
    {
        if (ifa->ifa_addr && (ifa->ifa_flags & IFF_UP) && !(ifa->ifa_flags & IFF_LOOPBACK) && ifa->ifa_addr->sa_family == AF_INET)
        {
            return (ft_strdup(ifa->ifa_name));
        }
    }
    return (NULL);
}

t_interface_info *get_active_interface_info(void)
{
    struct ifaddrs *ifaddrs, *ifa;
    t_interface_info *info = NULL;
    char *if_name = NULL;

    if (getifaddrs(&ifaddrs) == -1)
    {
        fprintf(stderr, "getifaddrs: %s\n", strerror(errno));
        return (NULL);
    }

    if_name = get_first_active_interface_name(ifaddrs);
    if (!if_name)
    {
        fprintf(stderr, "No active network interface found.\n");
        freeifaddrs(ifaddrs);
        return (NULL);
    }

    info = ft_calloc(1, sizeof(t_interface_info));
    if (!info)
    {
        free(if_name);
        freeifaddrs(ifaddrs);
        return (NULL);
    }

    for (ifa = ifaddrs; ifa != NULL; ifa = ifa->ifa_next)
    {
        if (ft_strncmp(if_name, ifa->ifa_name, IFNAMSIZ) == 0)
        {
            if (ifa->ifa_addr->sa_family == AF_INET)
            {
                struct sockaddr_in *sa = (struct sockaddr_in *)ifa->ifa_addr;
                info->ip_addr = sa->sin_addr;
            }
            else if (ifa->ifa_addr->sa_family == AF_PACKET)
            {
                struct sockaddr_ll *sll = (struct sockaddr_ll *)ifa->ifa_addr;
                ft_memcpy(info->mac_addr, sll->sll_addr, 6);
            }
        }
    }

    ft_strlcpy(info->name, if_name, IFNAMSIZ);
    info->index = if_nametoindex(if_name);

    free(if_name);
    freeifaddrs(ifaddrs);

    if (info->ip_addr.s_addr == 0 || info->mac_addr[0] == 0)
    {
        fprintf(stderr, "Could not retrieve complete information for interface %s\n", info->name);
        free(info);
        return (NULL);
    }

    return (info);
}