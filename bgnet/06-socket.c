#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
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
        printf("unsupported address family\n");
    }
}


int main()
{
    struct addrinfo *ai, *p;
    int sockfd;
    int ret;
    ssize_t bytes;
    size_t msglen;
    char *msg;
    char buffer[10240];

    ret = getaddrinfo("example.com", "http", NULL, &ai);
    
    if (ret != 0) {
        fprintf(stderr, "Error %d: %s\n", ret, gai_strerror(ret));
        return EXIT_FAILURE;
    }

    for (p = ai; p != NULL; p = p->ai_next) {

        printf("Found address: ");
        print_addrinfo(p);

        printf("Creating socket ...\n");
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (sockfd == -1) {
            fprintf(stderr, "Error %d: %s\n", errno, strerror(errno));
            continue;
        }

        printf("Connecting ...\n");
        ret = connect(sockfd, p->ai_addr, p->ai_addrlen);
        if (ret != 0) {
            fprintf(stderr, "Error %d: %s\n", errno, strerror(errno));
            close(sockfd);
            continue;
        }
        break;
    }

    freeaddrinfo(ai);

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
        fprintf(stderr, "Error %d: %s\n", errno, strerror(errno));
        close(sockfd);
        return EXIT_FAILURE;
    }
    printf("Sent %jd bytes.\n", (intmax_t) bytes);

    printf("Receiving ...\n");
    bytes = recv(sockfd, buffer, arrlen(buffer), 0);
    if (bytes == -1) {
        fprintf(stderr, "Error %d: %s\n", errno, strerror(errno));
    }
    printf("Received %jd bytes:\n\n", (intmax_t) bytes);
    printf("%s\n", buffer);

    printf("Sleeping ...\n");
    sleep(5);
    printf("Done!\n");

    close(sockfd);
    return EXIT_SUCCESS;
}
