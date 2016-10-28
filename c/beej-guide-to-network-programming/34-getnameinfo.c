#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>

int main()
{
    char host[256];
    char serv[256];
    struct sockaddr_in sa;

    sa.sin_family = AF_INET;
    sa.sin_port = htons(80);
    inet_pton(AF_INET, "127.0.0.1", &sa.sin_addr);

    getnameinfo((struct sockaddr *) &sa, sizeof sa,
                host, sizeof host,
                serv, sizeof serv, 0);

    printf("host: %s\n", host);
    printf("serv: %s\n", serv); 
    return EXIT_SUCCESS;
}
