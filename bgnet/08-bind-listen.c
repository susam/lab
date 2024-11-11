#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

#define arrlen(a) (sizeof (a) / sizeof *(a))

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
    struct addrinfo *ai, *aii, hints;
    struct sockaddr_storage client_addr;
    socklen_t client_addr_len = sizeof client_addr;
    int sockfd, client_sockfd;
    int ret;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((ret = getaddrinfo(NULL, "9090", &hints, &ai)) != 0) {
        fprintf(stderr, "getaddrinfo() error %d: %s\n", ret, gai_strerror(ret));
        return EXIT_FAILURE;
    }

    for (aii = ai; aii != NULL; aii = aii->ai_next) {
        print_addrinfo("Found address: ", aii);
        
        printf("Creating socket ...\n");
        sockfd = socket(aii->ai_family, aii->ai_socktype, aii->ai_protocol);
        if (sockfd == -1) {
            fprintf(stderr, "socket() error %d: %s\n", ret, strerror(errno));
            continue;
        }

        printf("Binding ...\n");
        if ((ret = bind(sockfd, aii->ai_addr, aii->ai_addrlen)) == -1) {
            fprintf(stderr, "bind() error %d: %s\n", ret, strerror(errno));
            close(sockfd);
            continue;
        }

        break;
    }

    freeaddrinfo(aii);

    if (aii == NULL) {
        fprintf(stderr, "Error: Cannot bind to any address\n");
        return EXIT_FAILURE;
    }

    printf("Listening ...\n");
    if ((ret = listen(sockfd, 10)) == -1) {
        fprintf(stderr, "listen() error %d: %s\n", ret, strerror(errno));
        close(sockfd);
        return EXIT_FAILURE;
    }

    printf("Accepting ...\n");
    printf("before accept(): client_addr_len: %jd\n", (intmax_t) client_addr_len);
    client_sockfd = accept(sockfd, (struct sockaddr *) &client_addr, &client_addr_len);
    printf("after accept(): client_addr_len: %jd\n", (intmax_t) client_addr_len);

    if (client_sockfd == -1) {
        fprintf(stderr, "accept() error %d: %s\n", ret, strerror(errno));
        close(sockfd);
        return EXIT_FAILURE;
    }

    print_sockaddr("Accepted: ", (struct sockaddr *) &client_addr);

    for (int i = 0; i < 3; i++) {
       ssize_t bytes;
       char buffer[1024];

        bytes = recv(client_sockfd, buffer, arrlen(buffer), 0);
        if (bytes == -1) {
            fprintf(stderr, "recv() error %d: %s\n", errno, strerror(errno));
            break;
        } else if (bytes == 0) {
            fprintf(stderr, "recv() returned 0; connection closed\n");
            break;
        }
        printf("Received %jd bytes: %.*s\n", (intmax_t) bytes, (int) bytes, buffer);

        snprintf(buffer, arrlen(buffer), "hello %d\n", i);
        bytes = send(client_sockfd, buffer, strlen(buffer), 0); 
        if (bytes == -1) {
            fprintf(stderr, "send() error %d: %s\n", errno, strerror(errno));
            break;
        }
        printf("Sent %jd bytes: %s\n", (intmax_t) bytes, buffer);
    }

    printf("Done!\n");

    close(sockfd);
    return EXIT_SUCCESS;
}
