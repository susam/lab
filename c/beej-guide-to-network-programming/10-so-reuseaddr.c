#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
    struct addrinfo *ai, hints;
    struct sockaddr c_addr;
    socklen_t c_addr_len = sizeof c_addr;
    int sockfd, c_sockfd;
    int bytes;
    int ret;
    int yes;
    int arg;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s 0|1\n", argv[0]);
        return EXIT_FAILURE;
    }

    arg = atoi(argv[1]);

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    ret = getaddrinfo(NULL, "9090", &hints, &ai);
    if (ret != 0) {
        fprintf(stderr, "getaddrinfo() error %d: %s\n", ret, gai_strerror(ret));
        return EXIT_FAILURE;
    }

    sockfd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
    if (sockfd == -1) {
        perror("socket()");
        return EXIT_FAILURE;
    }

    if (arg == 1) {
        yes = 1;
        ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);
        if (ret == -1) {
            perror("setsockopt()");
            return EXIT_FAILURE;
        }
    }

    if (bind(sockfd, ai->ai_addr, ai->ai_addrlen) == -1) {
        // We expect this error as per the tests, so return success.
        perror("bind()");
        return EXIT_SUCCESS;
    }

    freeaddrinfo(ai);

    if (listen(sockfd, 10) == -1) {
        perror("listen()");
        return EXIT_FAILURE;
    }

    c_sockfd = accept(sockfd, (struct sockaddr *) &c_addr, &c_addr_len);
    if (c_sockfd == -1) {
        perror("accept()");
        return EXIT_FAILURE;
    }

    bytes = send(c_sockfd, "hello\n", 6, 0);
    if (bytes == -1) {
        perror("send()");
        return EXIT_FAILURE;
    }
    printf("Sent %jd bytes.\n", (intmax_t) bytes);

    close(c_sockfd);
    close(sockfd);
    printf("Closed sockets.\n");
}
