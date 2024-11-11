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

void print_sockaddr(struct sockaddr *sa)
{
    char ip[INET6_ADDRSTRLEN];

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
    
    print_sockaddr(ai->ai_addr);
}


int main()
{
    struct addrinfo hints, *ai, *aii;
    struct sockaddr_storage c_addr;
    socklen_t c_addr_len = sizeof c_addr;
    int sockfd;
    int ret;
    
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;

    ret = getaddrinfo(NULL, "9090", &hints, &ai);
    assert_no_error(ret, "getaddrinfo()");

    for (aii = ai; aii != NULL; aii = aii->ai_next) {
        print_addrinfo("Found address: ", aii);

        sockfd = socket(aii->ai_family, aii->ai_socktype, aii->ai_protocol);
        if (sockfd == -1) {
            fprintf(stderr, "socket() error %d: %s\n", errno, strerror(errno));
            continue;
        }

        ret = bind(sockfd, aii->ai_addr, aii->ai_addrlen);
        if (ret == -1) {
            fprintf(stderr, "bind() error %d: %s\n", ret, strerror(errno));
            close(sockfd);
            continue;
        }

        break;
    }

    freeaddrinfo(ai);

    if (aii == NULL) {
        fprintf(stderr, "Error: No address succeeded!\n");
        return EXIT_FAILURE;
    }

    // listen() error: Operation not supported
    // ret = listen(sockfd, 10);
    // assert_no_error(ret, "listen()");

    for (int i = 0; i < 3; i++) 
    {
        ssize_t bytes;
        char buffer[1024];

        bytes = recvfrom(sockfd, buffer, arrlen(buffer), 0,
                         (struct sockaddr *) &c_addr, &c_addr_len);
        if (bytes == -1) {
            fprintf(stderr, "recv() error %d: %s\n", errno, strerror(errno));
            break;
        } else if (bytes == 0) {
            fprintf(stderr, "recv() returned 0; connection closed\n");
            break;
        }

        printf("Received %jd bytes from: ", bytes);
        print_sockaddr((struct sockaddr *) &c_addr);
        printf("\n");
        printf("Data: %.*s\n", (int) bytes, buffer);

        snprintf(buffer, arrlen(buffer), "hello %d\n", i);
        bytes = sendto(sockfd, buffer, strlen(buffer), 0,
                       (struct sockaddr *) &c_addr,
                       sizeof (struct sockaddr_storage));
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
