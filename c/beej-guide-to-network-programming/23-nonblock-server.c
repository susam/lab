#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

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
    int sockfd, connfd;
    int ret;
    int yes = 1;

    struct addrinfo hints, *ai, *aii;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
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

        ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);
        if (ret == -1) {
            fprintf(stderr, "S: setsockopt() error: %s\n", strerror(errno));
            close(sockfd);
            return EXIT_FAILURE;
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

    if (listen(sockfd, 2) == -1) {
        fprintf(stderr, "S: listen() error: %s\n", strerror(errno));
        close(sockfd);
        return EXIT_FAILURE;
    }

    printf("S: Listening ...\n");
    if (fcntl(sockfd, F_SETFL, O_NONBLOCK) == -1) {
        fprintf(stderr, "S: fcntl() error: %s\n", strerror(errno));
        close(sockfd);
        return EXIT_FAILURE;
    }

    printf("%d, %d\n", EAGAIN, EWOULDBLOCK);
    /* accept() loop */
    while (1) {
        struct sockaddr_storage conn_addr;
        socklen_t conn_addr_len = sizeof conn_addr;
        pid_t pid;

        printf("S: Waiting for new connection ...\n");
        connfd = accept(sockfd, (struct sockaddr *) &conn_addr, &conn_addr_len);
        if (connfd == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                printf("S: accept(): %s; Sleeping ...\n", strerror(errno));
                sleep(5);
            } else {
                fprintf(stderr, "S: accept() error: %s\n", strerror(errno));
            }
            continue;
        }

        print_sockaddr("S: Accepted: ", (struct sockaddr *) &conn_addr);

        pid = fork();
        if (pid == -1) {
            fprintf(stderr, "S: fork() error: %s\n", strerror(errno));
            continue;
        } else if (pid == 0) {
            /* We are in the child process. */
            char buffer[1024];
            ssize_t bytes;

            close(sockfd);

            /* It is necessary to set the non-blocking file status flag
             * for the client socket as well. Otherwise, the recv() call
             * below would block. */
            if (fcntl(connfd, F_SETFL, O_NONBLOCK) == -1) {
                fprintf(stderr, "S: fcntl() error: %s\n", strerror(errno));
                close(connfd);
                return EXIT_FAILURE;
            }

            while (1) {
                printf("S: Waiting for data ...\n");
                bytes = recv(connfd, buffer, arrlen(buffer), 0);
                if (bytes == -1) {
                    if (errno == EAGAIN || errno == EWOULDBLOCK) {
                        printf("S: read(): %s; Sleeping ...\n", strerror(errno));
                        sleep(2);
                        continue;
                    } else {
                        fprintf(stderr, "S: recv() error: %s\n", strerror(errno));
                        close(connfd);
                        return EXIT_FAILURE;
                    }
                } else if (bytes == 0) {
                    printf("S: recv(): connection closed\n");
                    close(connfd);
                    return EXIT_SUCCESS;
                } else {
                    printf("S: recv() %jd bytes: %.*s",
                           (intmax_t) bytes, (int) bytes, buffer);
                    break;
                }
            }

            strcpy(buffer, "hello from server\n");
            bytes = send(connfd, buffer, strlen(buffer), 0);
            if (bytes == -1) {
                fprintf(stderr, "S: send() error: %s\n", strerror(errno));
                close(connfd);
                return EXIT_FAILURE;
            }
            printf("S: send() %jd bytes: %s", strlen(buffer), buffer);
            close(connfd);
            return EXIT_SUCCESS;
        } else {
            /* We are in the parent process. */
            close(connfd);
            continue;
        }
    }
}
