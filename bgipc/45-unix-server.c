#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

int main()
{
    int sockfd;
    struct sockaddr_un addr;

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("S: socket() error");
        return EXIT_FAILURE;
    }

    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, "/tmp/mysock");
    unlink(addr.sun_path);

    if (bind(sockfd, (struct sockaddr *) &addr, sizeof addr) == -1) {
        perror("S: bind() error");
        close(sockfd);
        return EXIT_FAILURE;
    }

    if (listen(sockfd, 2) == -1) {
        perror("S: listen() error");
        close(sockfd);
        return EXIT_FAILURE;
    }

    while (1) {
        struct sockaddr_un caddr;
        int csockfd;
        socklen_t caddrlen = sizeof caddr;
        ssize_t bytes;

        printf("S: waiting for new connection ...\n");
        
        csockfd = accept(sockfd, (struct sockaddr *) &caddr, &caddrlen);
        if (csockfd == -1) {
            perror("S: accept() error");
            continue;
        }

        while (1) {
            char buffer[1024];
            bytes = recv(csockfd, buffer, sizeof buffer, 0);

            if (bytes == -1) {
                perror("S: recv() error");
                close(csockfd);
                break;
            } else if (bytes == 0) {
                printf("S: recv(): connection closed\n");
                close(csockfd);
                break;
            } else {
                printf("S: recv() %jd bytes: %.*s",
                       (intmax_t) bytes, (int) bytes, buffer);
            }

            if (strncmp(buffer, "exit", 4) == 0) {
                close(csockfd);
                goto exit;
            }

            strcpy(buffer, "hello from server\n");
            bytes = send(csockfd, buffer, strlen(buffer), 0);
            if (bytes == -1) {
                perror("S: send() error");
                break;
            }
            printf("S: send() %jd bytes: %s", (intmax_t) bytes, buffer);
        }
    }

exit:
    printf("exiting ...\n");
    close(sockfd);
    return EXIT_SUCCESS;
}
