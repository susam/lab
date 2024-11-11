#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#define arrlen(a) (sizeof (a) / sizeof (*(a)))

void print_addr_info(const char *node, const char *service,
                     int flags, int family, int socktype, int protocol)
{
    struct addrinfo hints, *res, *p; 
    int status;

    memset(&hints, 0, sizeof hints);
    hints.ai_flags = flags;
    hints.ai_family = family;
    hints.ai_socktype = socktype;
    hints.ai_protocol = protocol;

    printf("%s:%s\n", node, service);

    status = getaddrinfo(node, service, &hints, &res);
    if (status != 0) {
        fprintf(stderr, "    Error %d: %s\n\n", status, gai_strerror(status));
        return;
    }

    for (p = res; p != NULL; p = p->ai_next) {
        char ip[INET6_ADDRSTRLEN];

        if (p->ai_family == AF_INET) {

            struct sockaddr_in *addr = (struct sockaddr_in *) p->ai_addr;
            printf("    IPv4: %s; Port: %d; Protocol: %d; Canonical: %s\n",
                   inet_ntop(AF_INET, &addr->sin_addr, ip, arrlen(ip)),
                   ntohs(addr->sin_port), p->ai_protocol, p->ai_canonname);

        } else if (p->ai_family == AF_INET6) {

            struct sockaddr_in6 *addr = (struct sockaddr_in6 *) p->ai_addr;
            printf("    IPv6: %s; Port: %d; Protocol: %d; Canonical: %s\n",
                   inet_ntop(AF_INET6, &addr->sin6_addr, ip, arrlen(ip)),
                   ntohs(addr->sin6_port), p->ai_protocol, p->ai_canonname);
        } else {
            printf("Unsupported family: %d\n", p->ai_family);
        }
    }
    printf("\n");

    freeaddrinfo(res);
}

int main()
{
    printf("----- No hints -----\n");
    print_addr_info(NULL, "http", 0, 0, 0, 0);
    print_addr_info(NULL, "80", 0, 0, 0, 0);
    print_addr_info("localhost", NULL, 0, 0, 0, 0);
    print_addr_info(NULL, NULL, 0, 0, 0, 0);

    /* Either node name or service name must be specified. From
     * POSIX.1-2001 > getaddrinfo > ERRORS section:
     *
     *   [EAI_NONAME]
     *       The name does not resolve for the supplied parameters.
     *
     *       Neither nodename nor servname were supplied. At least one
     *       of these shall be supplied.
     * 
     * From man getaddrinfo:
     *
     *   Either node or service, but not both, may be NULL.
     *
     * As a result of the above, the last call above leads to error.
     */


    /* If node is NULL and AI_PASSIVE flag is set, wildcard addresses
     * are returned. */
    printf("----- AI_PASSIVE -----\n");
    print_addr_info(NULL, "http", AI_PASSIVE, 0, 0, 0);

    /* If node is not NULL, AI_PASSIVE flag is ignored. */
    printf("----- AI_PASSIVE ignored -----\n");
    print_addr_info("localhost", "http", AI_PASSIVE, AF_INET, SOCK_STREAM, 0);
    print_addr_info("example.com", "http", AI_PASSIVE, AF_INET, SOCK_STREAM, 0);

    /* AI_CANONNAME flag */
    printf("----- AI_CANONNAME -----\n");
    print_addr_info("localhost", "http", AI_CANONNAME, AF_INET, SOCK_STREAM, 0);
    print_addr_info("www.example.com", "http", AI_CANONNAME, AF_INET, SOCK_STREAM, 0);

    /* Select IPv4 and TCP only. */
    printf("----- IPv4, SOCK_STREAM -----\n");
    print_addr_info(NULL, "http", 0, AF_INET, SOCK_STREAM, 0);

    /* Select IPv4 and TCP only. */
    printf("----- IPv4, SOCK_DGRAM -----\n");
    print_addr_info(NULL, "http", 0, AF_INET, SOCK_DGRAM, 0);

    /* Specify both family and protocol in hints. */
    printf("----- Consistent socktype and protocol -----\n");
    print_addr_info(NULL, "http", 0, 0, SOCK_STREAM, IPPROTO_TCP);
    print_addr_info(NULL, "http", 0, 0, SOCK_DGRAM, IPPROTO_UDP);

    /* Specify inconsistent family and protocol in hints. */
    printf("----- Inconsistent socktype and protocol -----\n");
    print_addr_info(NULL, "http", 0, 0, SOCK_STREAM, IPPROTO_UDP);
    print_addr_info(NULL, "http", 0, 0, SOCK_DGRAM, IPPROTO_TCP);

    /* Error codes. */
    printf("EAI_NONAME: %d; EAI_SOCKTYPE: %d\n",
           EAI_NONAME, EAI_SOCKTYPE);

    printf("AF_UNSPEC: %d; AF_INET: %d; AF_INET6: %d;\n",
            AF_UNSPEC, AF_INET, AF_INET6);

    printf("SOCK_STREAM: %d; SOCK_DGRAM: %d\n",
           SOCK_STREAM, SOCK_DGRAM);

    printf("IPPROTO_IP: %d; IPPROTO_TCP: %d; IPPROTO_UDP: %d\n",
           IPPROTO_IP, IPPROTO_TCP, IPPROTO_UDP);
}
