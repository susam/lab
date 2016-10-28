#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

void assert_no_error(int code, const char *func_name)
{
    if (code == -1) {
        fprintf(stderr, "%s error: %s\n", func_name, strerror(errno));
        exit(EXIT_FAILURE);
    }
}

int main()
{
    struct addrinfo *ai, hints;
    struct sockaddr c_addr;
    socklen_t c_addr_len = sizeof c_addr;
    int sockfd, c_sockfd;
    int bytes;
    int ret;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    ret = getaddrinfo(NULL, "9090", &hints, &ai);
    if (ret != 0) {
        fprintf(stderr, "getaddrinfo() error %d: %s\n", ret, gai_strerror(ret));
    }

    sockfd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
    assert_no_error(sockfd, "socket()");

    ret = bind(sockfd, ai->ai_addr, ai->ai_addrlen);
    assert_no_error(ret, "bind()");

    freeaddrinfo(ai);

    ret = listen(sockfd, 10);
    assert_no_error(ret, "listen()");
    printf("Listening ...\n");

    c_sockfd = accept(sockfd, (struct sockaddr *) &c_addr, &c_addr_len);
    assert_no_error(c_sockfd, "accept()");

    bytes = send(c_sockfd, "hello\n", 6, 0);
    assert_no_error(bytes, "send()");

    printf("Sent %jd bytes.\n", (intmax_t) bytes);

    close(c_sockfd);
    close(sockfd);
}
