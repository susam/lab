#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_un addr;
    ssize_t bytes;
    char buffer[1024];
    int exit;

    if (argc != 2) {
        printf("Usage: %s 0|1\n", argv[0]);
        return EXIT_FAILURE;
    }

    exit = atoi(argv[1]);

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("C: socket() error");
        return EXIT_FAILURE;
    }

    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, "/tmp/mysock");

    if (connect(sockfd, (struct sockaddr *) &addr, sizeof addr) == -1) {
        perror("C: connect() error");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < 2; i++) {
        snprintf(buffer, sizeof buffer, "hello %d from client\n", i);
        bytes = send(sockfd, buffer, strlen(buffer), 0);
        if (bytes == -1) {
            perror("C: send() error");
            break;
        }
        printf("C: send() %jd bytes: %s", (intmax_t) bytes, buffer);

        bytes = recv(sockfd, buffer, sizeof buffer, 0);
        if (bytes == -1) {
            perror("C: recv() error");
            close(sockfd);
            return EXIT_FAILURE;
        } else if (bytes == 0) {
            printf("C: recv(): connection closed\n");
            close(sockfd);
            return EXIT_SUCCESS;
        } else {
            printf("C: recv() %jd bytes: %.*s",
                   (intmax_t) bytes, (int) bytes, buffer);
        }

        sleep(1);
    }

    if (exit) {
        snprintf(buffer, sizeof buffer, "exit\n");
        bytes = send(sockfd, buffer, strlen(buffer), 0);
        if (bytes == -1) {
            perror("C: send() error");
            return EXIT_FAILURE;
        }
        printf("C: send() %jd bytes: %s", (intmax_t) bytes, buffer);
    }

    return EXIT_SUCCESS;
}
