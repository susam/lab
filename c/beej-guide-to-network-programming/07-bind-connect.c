#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <ifaddrs.h>
#include <unistd.h>
#include <stdlib.h>

#define arrlen(a) (sizeof (a) / sizeof (*(a)))

void print_addrinfo(struct addrinfo *ai)
{
    char ip[INET6_ADDRSTRLEN];

    printf("family: %d; socktype: %d; protocol: %d; ",
           ai->ai_family, ai->ai_socktype, ai->ai_protocol);

    if (ai->ai_family == AF_INET) {
        struct sockaddr_in *addr = (struct sockaddr_in *) ai->ai_addr;
        printf("ipv4: %s; port: %d\n",
               inet_ntop(AF_INET, &addr->sin_addr, ip, arrlen(ip)),
               ntohs(addr->sin_port));
    } else if (ai->ai_family == AF_INET6) {
        struct sockaddr_in6 *addr = (struct sockaddr_in6 *) ai->ai_addr;
        printf("ipv6: %s; port: %d\n",
               inet_ntop(AF_INET6, &addr->sin6_addr, ip, arrlen(ip)),
               ntohs(addr->sin6_port));
    } else {
        printf("unsupported address family: %d\n", ai->ai_family);
    }
}

void print_ifaddrs(struct ifaddrs *ifa)
{
    char ip[INET6_ADDRSTRLEN];

    printf("family: %d; name: %s; ", ifa->ifa_addr->sa_family,
                                       ifa->ifa_name);
    if (ifa->ifa_addr->sa_family == AF_INET) {
        struct sockaddr_in *addr = (struct sockaddr_in *) ifa->ifa_addr;
        printf("ipv4: %s; port: %d\n",
               inet_ntop(AF_INET, &addr->sin_addr, ip, arrlen(ip)),
               ntohs(addr->sin_port));
    } else if (ifa->ifa_addr->sa_family == AF_INET6) {
        struct sockaddr_in6 *addr = (struct sockaddr_in6 *) ifa->ifa_addr;
        printf("ipv6: %s; port: %d\n",
               inet_ntop(AF_INET6, &addr->sin6_addr, ip, arrlen(ip)),
               ntohs(addr->sin6_port));
    } else {
        printf("unsupported address family: %d\n", ifa->ifa_addr->sa_family);
    }
}

int main()
{
    struct addrinfo *ai, *p;
    struct ifaddrs *ifa, *lp;
    int sockfd;
    int ret;
    ssize_t bytes;
    size_t msglen;
    char *msg;
    char buffer[10240];

    in_port_t port = htons(50000);

    ret = getaddrinfo("example.com", "http", NULL, &ai);
    if (ret != 0) {
        fprintf(stderr, "getaddrinfo(example.com) error %d: %s\n", ret, gai_strerror(ret));
        return EXIT_FAILURE;
    }

    ret = getifaddrs(&ifa);
    if (ret != 0) {
        fprintf(stderr, "getifaddrs() error %d: %s\n", ret, gai_strerror(ret));
        return EXIT_FAILURE;
    }

    for (p = ai; p != NULL; p = p->ai_next) {

        printf("Found remote address: ");
        print_addrinfo(p);

        for (lp = ifa; lp != NULL; lp = lp->ifa_next) {
            socklen_t addrlen;
            
            printf("    Found local interface: ");
            print_ifaddrs(lp);

            printf("    Creating socket ...\n");
            sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
            if (sockfd == -1) {
                fprintf(stderr, "    socket() error %d: %s\n",
                        errno, strerror(errno));
                continue;
            }


            switch (lp->ifa_addr->sa_family) {
                case AF_INET:
                    addrlen = sizeof (struct sockaddr_in);
                    ((struct sockaddr_in *) lp->ifa_addr)->sin_port = port;
                    break;
                case AF_INET6:
                    addrlen = sizeof (struct sockaddr_in6);
                    ((struct sockaddr_in6 *) lp->ifa_addr)->sin6_port = port;
                    break;
                default:
                    fprintf(stderr, "    Unsupported address family.\n");
                    close(sockfd);
                    continue;
            }
            
            printf("    Binding ...\n");
            ret = bind(sockfd, lp->ifa_addr, addrlen);
            if (ret == -1) {
                fprintf(stderr, "    bind() error %d: %s\n",
                        errno, strerror(errno));
                close(sockfd);
                continue;
            }

            printf("    Connecting ...\n");
            ret = connect(sockfd, p->ai_addr, p->ai_addrlen);
            if (ret == -1) {
                fprintf(stderr, "    connect() error %d: %s\n",
                        errno, strerror(errno));
                close(sockfd);
                continue;
            }

            goto end_of_loop;
        }

    }

end_of_loop:

    freeaddrinfo(ai);
    freeifaddrs(ifa);

    if (p == NULL) {
        fprintf(stderr, "Error: No address succeeded!\n");
        close(sockfd);
        return EXIT_FAILURE;
    }

    msg = "GET / HTTP/1.0\nHost: example.com\n\n";
    msglen = strlen(msg);

    printf("Sending %zu bytes ...\n", msglen);
    bytes = send(sockfd, msg, msglen, 0);
    if (bytes == -1) {
        fprintf(stderr, "send() error %d: %s\n", errno, strerror(errno));
        close(sockfd);
        return EXIT_FAILURE;
    }
    printf("Sent %jd bytes.\n", (intmax_t) bytes);

    printf("Receiving ...\n");
    bytes = recv(sockfd, buffer, arrlen(buffer), 0);
    if (bytes == -1) {
        fprintf(stderr, "recv() error %d: %s\n", errno, strerror(errno));
        close(sockfd);
        return EXIT_FAILURE;
    }
    printf("Received %jd bytes:\n\n", (intmax_t) bytes);

    printf("%s\n", buffer);

    printf("Sleeping ...\n");
    sleep(5);
    printf("Done!\n");
    close(sockfd);
    return EXIT_SUCCESS;
}
