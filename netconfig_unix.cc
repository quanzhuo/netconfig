#include <string>
#include <vector>
#include <utility>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

int main()
{
    std::vector<std::pair<std::string, struct in_addr>> if_lists;
    struct ifaddrs *addrs, *tmp;
    getifaddrs(&addrs);
    tmp = addrs;

    while (tmp)
    {
        if(tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_INET)
        {
            std::cout << "interface name: " << tmp->ifa_name << std::endl;

            struct sockaddr_in *sock = (struct sockaddr_in *)(tmp->ifa_addr);
            struct in_addr in = sock->sin_addr;
            std::cout << "IP: " << inet_ntoa(in) << std::endl;
            sock = (struct sockaddr_in *)(tmp->ifa_netmask);
            in = sock->sin_addr;
            std::cout << "Netmask: " << inet_ntoa(in) << std::endl;
        }
        tmp = tmp->ifa_next;
    }
    

    return 0;
}
