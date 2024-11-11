#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc, char **argv)
{
    struct addrinfo hints, *ai;
    int sockfd;
    int ret;
    ssize_t bytes;
    char buffer[1024];
    int how;

    if (argc != 2) {
        printf("Usage: %s 0|1|2\n", argv[0]);
        return EXIT_FAILURE;
    }

    how = atoi(argv[1]);
    printf("how: %d\n", how);

    /* Select TCP/IPv4 address only. */
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    /* Connect to localhost:9090. */
    if ((ret = getaddrinfo("localhost", "9090", &hints, &ai)) == -1) {
        printf("getaddrinfo() error: %s\n", gai_strerror(ret));
        return EXIT_FAILURE;
    }

    if ((sockfd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol)) == -1) {
        printf("socket() error: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    sleep(2);
    /* Elapsed: 2 s */
    if ((connect(sockfd, ai->ai_addr, ai->ai_addrlen)) == -1) {
        printf("connect() error: %s\n", strerror(errno));
        close(sockfd);
        return EXIT_FAILURE;
    }

    freeaddrinfo(ai);

    /* Test 1: Before shutdown. */
    sleep(4);
    /* Elapsed: 6 s */
    /* Test SHUT_RD: Receive "aa". */
    /* Test SHUT_RW: Send "msg1". */
    bytes = recv(sockfd, buffer, 1024, 0);
    printf("recv() #1 returned %d bytes: %.*s\n", (int) bytes, (int) bytes, buffer);
    bytes = send(sockfd, "msg1\n", 5, 0);
    printf("send() #1 sent %d bytes.\n", (int) bytes);

    /* Shutdown/Close. */
    sleep(2);
    /* Elapsed: 8 s */
    /* Test SHUT_RW/RWRD: netcat terminates as soon as shutdown() completes. */
    if (how >= 0)  {

        if (shutdown(sockfd, how) == -1) {
            printf("shutdown() error: %s\n", strerror(errno));
            close(sockfd);
            return EXIT_FAILURE;
        }
        printf("shutdown() complete\n");

    } else {

        if (close(sockfd) == -1) {
            printf("close () error: %s\n", strerror(errno));
            return EXIT_FAILURE;
        }
        printf("close() complete\n");
    }

    /* Test 2: After shutdown/close. */
    sleep (4);
    /* Elapsed: 12 s */
    /* Test SHUT_RD: Receive "bb". */
    /* Test SHUT_RW/RWRD: Program exits on send() with status 141 (SIGPIPE). */
    /* Test close(): Both recv() and send() return -1. */
    bytes = recv(sockfd, buffer, 1024, 0);
    printf("recv() #2 returned %d bytes: %.*s\n", (int) bytes, (int) bytes, buffer);
    bytes = send(sockfd, "msg2\n", 5, 0);
    printf("send() #2 sent %d bytes.\n", (int) bytes);

    /* Test 3. */
    sleep (2);
    /* Elapsed: 14 s */
    /* Test SHUT_RD: recv() returns 0 immediately. */
    /* TEST SHUT_RW/RWRD: Unreachable code; program has exited already. */
    /* Test close(): Both recv() and send() return -1. */
    bytes = recv(sockfd, buffer, 1024, 0);
    printf("recv() #3 returned %d bytes: %.*s\n", (int) bytes, (int) bytes, buffer);
    bytes = send(sockfd, "msg3\n", 5, 0);
    printf("send() #3 sent %d bytes.\n", (int) bytes);

    /* Test 4. */
    sleep (4);
    /* Elapsed: 18 s */
    /* Test SHUT_RD: Receive "cc". */
    /* TEST SHUT_RW/RWRD: Unreachable code; program has exited already. */
    /* Test close(): Both recv() and send() return -1. */
    bytes = recv(sockfd, buffer, 1024, 0);
    printf("recv() #4 returned %d bytes: %.*s\n", (int) bytes, (int) bytes, buffer);
    bytes = send(sockfd, "msg4\n", 5, 0);
    printf("send() #4 sent %d bytes.\n", (int) bytes);

    /* Test 5. */
    sleep (2);
    /* Elapsed: 20 s */
    /* Test SHUT_RD: recv() returns 0 immediately. */
    /* TEST SHUT_RW/RWRD: Unreachable code; program has exited already. */
    /* Test close(): Both recv() and send() return -1. */
    bytes = recv(sockfd, buffer, 1024, 0);
    printf("recv() #5 returned %d bytes: %.*s\n", (int) bytes, (int) bytes, buffer);
    bytes = send(sockfd, "msg5\n", 5, 0);
    printf("send() #5 sent %d bytes.\n", (int) bytes);

    close(sockfd);
    return EXIT_SUCCESS;
}
