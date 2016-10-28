#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#define arrlen(a) (sizeof (a) / sizeof (*(a)))

void assert_no_error(int code, const char *func_name)
{
    if (code == -1) {
        fprintf(stderr, "%s error: %s\n", func_name, strerror(errno));
        exit(EXIT_FAILURE);
    }
}

void print_addrinfo(const char *msg, struct addrinfo *ai)
{
    char ip[INET6_ADDRSTRLEN];

    printf("%s", msg);
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
        printf("unsupported address family\n");
    }
}

int main()
{
    struct addrinfo hints, *ai, *aii;
    int sockfd;
    int bytes;
    int ret;
    
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    ret = getaddrinfo(NULL, "9090", &hints, &ai);
    assert_no_error(ret, "getaddrinfo()");

    for (aii = ai; aii != NULL; aii = aii->ai_next) {
        print_addrinfo("Found address: ", aii);

        sockfd = socket(aii->ai_family, aii->ai_socktype, aii->ai_protocol);
        if (sockfd == -1) {
            fprintf(stderr, "socket() error %d: %s\n", errno, strerror(errno));
            continue;
        }

        ret = connect(sockfd, aii->ai_addr, aii->ai_addrlen);
        if (ret == -1) {
            fprintf(stderr, "connect() error %d: %s\n", errno, strerror(errno));
            continue;
        }
        printf("Connected.\n");

        break;
    }

    freeaddrinfo(ai);

    if (aii == NULL) {
        fprintf(stderr, "Error: No address succeeded!\n");
        return EXIT_FAILURE;
    }

    bytes = send(sockfd, "hello\n", 6, 0);
    printf("Sent %jd bytes\n", (intmax_t) bytes);

    bytes = sendto(sockfd, "bye\n", 4, 0, aii->ai_addr,
                   sizeof (struct sockaddr_storage));
    printf("Sent %jd bytes\n", (intmax_t) bytes);

    bytes = send(sockfd, "hello\n", 6, 0);
    printf("Sent %jd bytes\n", (intmax_t) bytes);

    bytes = sendto(sockfd, "bye\n", 4, 0, aii->ai_addr,
                   sizeof (struct sockaddr_storage));
    printf("Sent %jd bytes\n", (intmax_t) bytes);

    close(sockfd);
    return EXIT_SUCCESS;
}
