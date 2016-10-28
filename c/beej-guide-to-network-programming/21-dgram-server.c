#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#define arrlen(a) (sizeof (a) / sizeof (*(a)))

void print_sockaddr(const char *msg, struct sockaddr *sa)
{
    char ip[INET6_ADDRSTRLEN];

    printf("%s", msg);

    if (sa->sa_family == AF_INET) {
        struct sockaddr_in *sin = (struct sockaddr_in *) sa;

        printf("ipv4: %s; port: %d\n",
               inet_ntop(AF_INET, &sin->sin_addr, ip, arrlen(ip)),
               ntohs(sin->sin_port));

    } else if (sa->sa_family == AF_INET6) {
        struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *) sa;

        printf("ipv6: %s; port: %d\n",
               inet_ntop(AF_INET6, &sin6->sin6_addr, ip, arrlen(ip)),
               ntohs(sin6->sin6_port));
    } else {
        printf("Unsupported address family: %d\n", sa->sa_family);
    }
}

void print_addrinfo(const char *msg, struct addrinfo *ai)
{
    printf("%s", msg);
    printf("family: %d; socktype: %d; protocol: %d; ",
           ai->ai_family, ai->ai_socktype, ai->ai_protocol);
    print_sockaddr("", ai->ai_addr);
}

int main()
{
    int sockfd;
    int ret;
    struct addrinfo hints, *ai, *aii;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;

    if ((ret = getaddrinfo(NULL, "9090", &hints, &ai)) == -1) {
        fprintf(stderr, "S: getaddrinfo() error: %s\n", gai_strerror(ret));
        return EXIT_FAILURE;
    }

    for (aii = ai; aii != NULL; aii = aii->ai_next) {
        print_addrinfo("S: Found address: ", aii);

        sockfd = socket(aii->ai_family, aii->ai_socktype, aii->ai_protocol);
        if (sockfd == -1) {
            fprintf(stderr, "S: socket() error: %s\n", strerror(errno));
            continue;
        }

        if (bind(sockfd, aii->ai_addr, aii->ai_addrlen) == -1) {
            fprintf(stderr, "S: bind() error: %s\n", strerror(errno));
            close(sockfd);
            continue;
        }

        break;
    }

    freeaddrinfo(ai);

    if (aii == NULL) {
        fprintf(stderr, "S: error: could not bind to any address\n");
        return EXIT_FAILURE;
    }

    /* recvfrom() loop */
    while (1) {
        struct sockaddr_storage conn_addr;
        socklen_t conn_addr_len = sizeof conn_addr;
        char buffer[1024];
        ssize_t bytes;

        printf("S: Waiting to receive data ...\n");
        bytes = recvfrom(sockfd, buffer, arrlen(buffer), 0,
                         (struct sockaddr *) &conn_addr, &conn_addr_len);
        if (bytes == -1) {
            fprintf(stderr, "S: recvfrom() error: %s\n", strerror(errno));
            close(sockfd);
            return EXIT_FAILURE;
        }

        printf("S: recvfrom() %jd bytes: %.*s",
               (intmax_t) bytes, (int) bytes, buffer);

        if (strncmp(buffer, "exit", 4) == 0)
            break;

        strcpy(buffer, "hello from server\n");
        bytes = sendto(sockfd, buffer, strlen(buffer), 0,
                       (struct sockaddr *) &conn_addr, conn_addr_len);
        if (bytes == -1) {
            fprintf(stderr, "S: sendto() error: %s\n", strerror(errno));
            close(sockfd);
            return EXIT_FAILURE;
        } else {
            printf("S: sendto() %jd bytes: %.*s",
                   (intmax_t) bytes, (int) bytes, buffer);
        }

    }

    close(sockfd);
    printf("S: closed\n");
    return EXIT_FAILURE;
}
