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
    struct sockaddr_storage c_addr;
    socklen_t c_addr_len;
    int sockfd;
    int c_sockfd;
    int ret;
    ssize_t bytes;
    char buffer[1024];
    int how;
    int yes = 1;

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
    hints.ai_flags = AI_PASSIVE;

    /* Listen on 0.0.0.0:9090. */
    if ((ret = getaddrinfo("localhost", "9090", &hints, &ai)) == -1) {
        printf("getaddrinfo() error: %s\n", gai_strerror(ret));
        return EXIT_FAILURE;
    }

    if ((sockfd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol)) == -1) {
        printf("socket() error: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    if ((ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,
                          &yes, sizeof yes)) == -1) {
        printf("setsockopt() error: %s\n", strerror(errno));
        close(sockfd);
        return EXIT_FAILURE;
    }

    if ((ret = bind(sockfd, ai->ai_addr, ai->ai_addrlen)) == -1) {
        printf("bind() error: %s\n", strerror(errno));
        close(sockfd);
        return EXIT_FAILURE;
    }

    freeaddrinfo(ai);

    if ((ret = listen(sockfd, 10)) == -1) {
        printf("listen() error: %s\n", strerror(errno));
        close(sockfd);
        return EXIT_FAILURE;
    }

    /* Test 1: Accept before shutdown. */
    c_addr_len = sizeof c_addr;
    if ((c_sockfd =
         accept(sockfd, (struct sockaddr *) &c_addr, &c_addr_len)) == -1) {
        
        printf("accept() error: %s\n", strerror(errno));
    }
    printf("accept() #1 succeeded.\n");

    /* Test 1.1: send()/recv() before shutdown. */
    /* Test SHUT_RD: Receive "aa". */
    /* Test SHUT_RW: Send "msg1". */
    bytes = recv(c_sockfd, buffer, 1024, 0);
    printf("recv() #1.1 returned %d bytes: %.*s\n", (int) bytes, (int) bytes, buffer);
    bytes = send(c_sockfd, "msg1\n", 5, 0);
    printf("send() #1.1 sent %d bytes.\n", (int) bytes);

    /* Shutdown/Close. */
    /* Time Elapsed: 2 s (connect delay by netcat) */
    /* Test SHUT_RW/RWRD: netcat terminates as soon as shutdown() completes. */
    if (how >= 0)  {

        if (shutdown(c_sockfd, how) == -1) {
            printf("shutdown() error: %s\n", strerror(errno));
            close(sockfd);
            close(c_sockfd);
            return EXIT_FAILURE;
        }
        printf("shutdown() complete\n");

    } else {

        if (close(c_sockfd) == -1) {
            printf("close () error: %s\n", strerror(errno));
            close(sockfd);
            return EXIT_FAILURE;
        }
        printf("close() complete\n");
    }

    /* Test 1.2: After shutdown/close. */
    /* Test SHUT_RD: recv() returns 0 immediately. send() succeeds. */
    /* Test SHUT_RW/RWRD: Program exits on send() with status 141 (SIGPIPE). */
    /* Test close(): Both recv() and send() return -1. */
    bytes = recv(c_sockfd, buffer, 1024, 0);
    printf("recv() #1.2 returned %d bytes: %.*s\n", (int) bytes, (int) bytes, buffer);
    bytes = send(c_sockfd, "msg2\n", 5, 0);
    printf("send() #1.2 sent %d bytes.\n", (int) bytes);

    /* Test 1.3. */
    sleep (4);
    /* Time Elapsed: 6s */
    /* Test SHUT_RD: recv() returns "bb". */
    /* TEST SHUT_RW/RWRD: Unreachable code; program has exited already. */
    /* Test close(): Both recv() and send() return -1. */
    bytes = recv(c_sockfd, buffer, 1024, 0);
    printf("recv() #1.3 returned %d bytes: %.*s\n", (int) bytes, (int) bytes, buffer);
    bytes = send(c_sockfd, "msg3\n", 5, 0);
    printf("send() #1.3 sent %d bytes.\n", (int) bytes);

    /* Test 1.4. */
    sleep (4);
    /* Elapsed: 10 s */
    /* Test SHUT_RD: Receive "cc". */
    /* TEST SHUT_RW/RWRD: Unreachable code; program has exited already. */
    /* Test close(): Both recv() and send() return -1. */
    bytes = recv(c_sockfd, buffer, 1024, 0);
    printf("recv() #1.4 returned %d bytes: %.*s\n", (int) bytes, (int) bytes, buffer);
    bytes = send(c_sockfd, "msg4\n", 5, 0);
    printf("send() #1.4 sent %d bytes.\n", (int) bytes);

    /* Test 1.5. */
    sleep (2);
    /* Elapsed: g2 s */
    /* Test SHUT_RD: recv() returns 0 immediately. */
    /* TEST SHUT_RW/RWRD: Unreachable code; program has exited already. */
    /* Test close(): Both recv() and send() return -1. */
    bytes = recv(c_sockfd, buffer, 1024, 0);
    printf("recv() #1.5 returned %d bytes: %.*s\n", (int) bytes, (int) bytes, buffer);
    bytes = send(c_sockfd, "msg5\n", 5, 0);
    printf("send() #1.5 sent %d bytes.\n", (int) bytes);

    close(c_sockfd);

    /* Test 2: Accept after shutdown. */
    /* Test SHUT_RD: accept() works fine. */
    /* TEST SHUT_RW/RWRD: Unreachable code; program has exited already. */
    /* Test close(): accept() works fine. */
    c_addr_len = sizeof c_addr;
    if ((c_sockfd =
         accept(sockfd, (struct sockaddr *) &c_addr, &c_addr_len)) == -1) {
        
        printf("accept() error: %s\n", strerror(errno));
    }
    printf("accept() #2 succeeded.\n");

    /* Test 2.1: send()/recv() before shutdown. */
    /* Test SHUT_RD: Receive "aa". */
    /* TEST SHUT_RW/RWRD: Unreachable code; program has exited already. */
    /* Test close(): Receive "aa". */
    bytes = recv(c_sockfd, buffer, 1024, 0);
    printf("recv() #2.1 returned %d bytes: %.*s\n", (int) bytes, (int) bytes, buffer);
    bytes = send(c_sockfd, "msg1\n", 5, 0);
    printf("send() #2.1 sent %d bytes.\n", (int) bytes);

    close(c_sockfd);
    close(sockfd);
}
