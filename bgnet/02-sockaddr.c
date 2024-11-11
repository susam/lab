#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

void print_addr(const char *node, const char *service)
{
    struct addrinfo *ai, *p;
    int ret;

    printf("node: %s\n", node);
    printf("service: %s\n\n", service);

    ret = getaddrinfo(node, service, NULL, &ai);

    if (ret != 0) {
        fprintf(stderr, "Error %d: %s\n", ret, gai_strerror(ret));
        return;
    }

    for (p = ai; p != NULL; p = p->ai_next) {
        printf("ai_flags: %d\n", p->ai_flags);
        printf("ai_family: %d\n", p->ai_family);
        printf("ai_socktype: %d\n", p->ai_socktype);
        printf("ai_protocol: %d\n", p->ai_protocol);
        printf("ai_addrlen: %ju\n", (uintmax_t) p->ai_addrlen);

        if (p->ai_family == AF_INET) {

            struct sockaddr_in *ai_addr = (struct sockaddr_in *) p->ai_addr;
            char ipv4[INET_ADDRSTRLEN];

            printf("ai_addr->sin_family: %jd\n",
                   (uintmax_t) ai_addr->sin_family);

            printf("ai_addr->sin_port: %jd\n",
                   (uintmax_t) ai_addr->sin_port);

            printf("ai_addr->sin_addr.s_addr: ");
            for (int i = 0; i < 4; i++) {
                printf("%d ", (ai_addr->sin_addr.s_addr >> (i * 8)) & 0xff);
            }
            printf("\n");

            inet_ntop(AF_INET, &ai_addr->sin_addr,
                      ipv4, sizeof ipv4 / sizeof *ipv4);
            printf("inet_ntop(): ai_addr->sin_addr: %s\n", ipv4);

        } else if (p->ai_family == AF_INET6) {

            struct sockaddr_in6 *ai_addr = (struct sockaddr_in6 *) p->ai_addr;
            char ipv6[INET6_ADDRSTRLEN];

            printf("ai_addr->sin6_family: %jd\n",
                   (uintmax_t) ai_addr->sin6_family);

            printf("ai_addr->sin6_port: %jd\n",
                   (uintmax_t) ai_addr->sin6_port);

            printf("ai_addr->sin6_flowinfo: %jd\n",
                   (uintmax_t) ai_addr->sin6_flowinfo);

            printf("ai_addr->sin6_addr.s6_addr: ");
            for (int i = 0; i < 16; i++) {
                printf("%02x ", ai_addr->sin6_addr.s6_addr[i]);
            }
            printf("\n");

            inet_ntop(AF_INET6, &ai_addr->sin6_addr,
                      ipv6, sizeof ipv6 / sizeof *ipv6);
            printf("inet_ntop(): ai_addr->sin6_addr: %s\n", ipv6);

            printf("ai_addr->sin6_scope_id: %jd\n",
                   (uintmax_t) ai_addr->sin6_scope_id);
        }

        printf("ai_canonname: %s\n\n", p->ai_canonname);
    }

    freeaddrinfo(ai);
}


int main()
{
    print_addr("localhost", "http");
    print_addr("example.com", "http");

    printf("AF_UNSPEC: %d; AF_INET: %d; AF_INET6: %d;\n",
            AF_UNSPEC, AF_INET, AF_INET6);

    printf("SOCK_STREAM: %d; SOCK_DGRAM: %d\n\n",
           SOCK_STREAM, SOCK_DGRAM);

}
