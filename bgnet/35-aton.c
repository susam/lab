#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>

int main()
{
    struct sockaddr_in addr;

    if (inet_aton("10.0.0.1", &addr.sin_addr)) {
        for (int i = 0; i < 4; i++) {
            printf("%d ", (addr.sin_addr.s_addr >> (i * 8)) & 0xff);
        }
        printf("\n");
    } else {
        perror("inet_aton()");
    }

    printf("%s\n", inet_ntoa(addr.sin_addr));

    addr.sin_addr.s_addr = inet_addr("10.0.0.2");
    for (int i = 0; i < 4; i++) {
        printf("%d ", (addr.sin_addr.s_addr >> (i * 8)) & 0xff);
    }
    printf("\n");
    printf("%s\n", inet_ntoa(addr.sin_addr));

    return EXIT_SUCCESS;
}
