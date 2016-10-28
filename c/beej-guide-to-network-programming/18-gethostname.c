#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <arpa/inet.h>

#define arrlen(x) (sizeof (x) / sizeof *(x))

int main()
{
    char hostname[64]; 
    struct addrinfo *ai, *aii; 
    int ret;

    if (gethostname(hostname, sizeof hostname / sizeof *hostname) == -1) {
        fprintf(stderr, "gethostname() error: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    printf("hostname: %s\n", hostname);


    if ((ret = getaddrinfo(hostname, NULL, NULL, &ai)) == -1) {
        fprintf(stderr, "getaddrinfo() error %d: %s\n", ret, gai_strerror(ret));
        return EXIT_FAILURE;
    }

    for (aii = ai; aii != NULL; aii = aii->ai_next) {
        char ip[INET6_ADDRSTRLEN];

        if (aii->ai_family == AF_INET) {

            struct sockaddr_in *addr = (struct sockaddr_in *) aii->ai_addr;
            printf("IPv4: %s; Port: %d; Protocol: %d; Canonical: %s\n",
                   inet_ntop(AF_INET, &addr->sin_addr, ip, arrlen(ip)),
                   ntohs(addr->sin_port), aii->ai_protocol, aii->ai_canonname);

        } else if (aii->ai_family == AF_INET6) {

            struct sockaddr_in6 *addr = (struct sockaddr_in6 *) aii->ai_addr;
            printf("IPv6: %s; Port: %d; Protocol: %d; Canonical: %s\n",
                   inet_ntop(AF_INET6, &addr->sin6_addr, ip, arrlen(ip)),
                   ntohs(addr->sin6_port), aii->ai_protocol, aii->ai_canonname);
        }
    }
    printf("\n");

    freeaddrinfo(ai);
    return EXIT_SUCCESS;
}
