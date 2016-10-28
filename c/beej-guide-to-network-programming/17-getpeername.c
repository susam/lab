#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <arpa/inet.h>

#define arrlen(x) (sizeof (x) / sizeof *(x))

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
    struct sockaddr_storage client_addr;
    socklen_t c_addr_len;
    int sockfd, c_sockfd;
    int ret;
    int yes = 1;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((ret = getaddrinfo(NULL, "9090", &hints, &ai)) != 0) {
        fprintf(stderr, "getaddrinfo() error %d: %s\n", ret, gai_strerror(ret));
        return EXIT_FAILURE;
    }

    sockfd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
    assert_no_error(sockfd, "socket()");

    ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);
    assert_no_error(ret, "setsockopt()");

    ret = bind(sockfd, ai->ai_addr, ai->ai_addrlen);
    assert_no_error(ret, "bind()");

    freeaddrinfo(ai);

    ret = listen(sockfd, 10);
    assert_no_error(ret, "listen()");
    
    // getpeername() error: Transport endpoint is not connected
    // ret = getpeername(sockfd, (struct sockaddr *) &client_addr, &c_addr_len);

    c_addr_len = sizeof client_addr;
    printf("before accept(): c_addr_len: %jd\n", (intmax_t) c_addr_len);

    c_sockfd = accept(sockfd, (struct sockaddr *) &client_addr, &c_addr_len);
    assert_no_error(c_sockfd, "accept()");

    printf("after accept(): c_addr_len: %jd\n", (intmax_t) c_addr_len);
    print_sockaddr("Accepted: ", (struct sockaddr *) &client_addr);

    c_addr_len = sizeof client_addr;
    printf("before getpeername(): c_addr_len: %jd\n", (intmax_t) c_addr_len);

    ret = getpeername(c_sockfd, (struct sockaddr *) &client_addr, &c_addr_len);
    assert_no_error(ret, "getpeername()");

    printf("after getpeername(): c_addr_len: %jd\n", (intmax_t) c_addr_len);
    print_sockaddr("getpeername(): ", (struct sockaddr *) &client_addr);

    ssize_t bytes;
    char buffer[1024];

    bytes = recv(c_sockfd, buffer, arrlen(buffer), 0);
    assert_no_error(bytes, "recv()");
    printf("Received %jd bytes: %.*s\n", (intmax_t) bytes, (int) bytes, buffer);

    bytes = send(c_sockfd, "hello\n", 6, 0); 
    assert_no_error(bytes, "send()");
    printf("Sent %jd bytes\n", (intmax_t) bytes);

    printf("Done!\n");

    close(sockfd);
    close(c_sockfd);
    return EXIT_SUCCESS;
}
