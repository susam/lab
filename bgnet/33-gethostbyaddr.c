#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

void print_hostent(struct hostent *he)
{
    struct in_addr **addr_list;

    if (he == NULL) {
        herror("gethostbyname");
        return;
    }

    printf("h_name: %s\n", he->h_name);

    printf("h_aliases:\n");
    for (int i = 0; he->h_aliases[i] != NULL; i++) {
        printf("  - %s\n", he->h_aliases[i]);
    }

    printf("h_addrtype: %d\n", he->h_addrtype);
    printf("h_length: %d\n", he->h_length);

    printf("h_addr_list:\n");
    addr_list = (struct in_addr **) he->h_addr_list;
    for (int i = 0; addr_list[i] != NULL; i++) {
        char ip[INET_ADDRSTRLEN]; 
        inet_ntop(AF_INET, addr_list[i], ip, INET_ADDRSTRLEN);
        printf("  - %s\n", ip);
    }
    printf("\n");
}

int main()
{
    struct hostent *he;
    struct in_addr ipv4addr;
    struct in6_addr ipv6addr;
    
    inet_aton("127.0.0.1", &ipv4addr);
    he = gethostbyaddr(&ipv4addr, sizeof ipv4addr, AF_INET);
    print_hostent(he);

    inet_pton(AF_INET, "127.0.1.1", &ipv4addr);
    he = gethostbyaddr(&ipv4addr, sizeof ipv4addr, AF_INET);
    print_hostent(he);

    inet_pton(AF_INET6, "::1", &ipv6addr);
    he = gethostbyaddr(&ipv6addr, sizeof ipv6addr, AF_INET6);
    print_hostent(he);

    inet_pton(AF_INET6, "ff02::1", &ipv6addr);
    he = gethostbyaddr(&ipv6addr, sizeof ipv6addr, AF_INET6);
    print_hostent(he);

    return EXIT_SUCCESS;
}
