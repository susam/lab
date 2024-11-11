#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int sv[2];
    ssize_t bytes;
    char buffer[1024];

    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sv) == -1) {
        perror("socketpair() error");
        return EXIT_FAILURE;
    }

    pid = fork();

    switch (pid) {
        case -1:
            perror("fork() error");
            return EXIT_FAILURE;
        
        case 0:
            close(sv[1]);

            /* Send from child to parent. */
            strcpy(buffer, "hello from child\n");
            bytes = send(sv[0], buffer, strlen(buffer), 0);
            if (bytes == -1) {
                close(sv[0]);
                perror("child: send( error");
                return EXIT_FAILURE;
            }
            printf("child: send() %jd bytes: %s", bytes, buffer);

            /* Receive at child. */
            bytes = recv(sv[0], buffer, sizeof buffer, 0);
            if (bytes == -1) {
                close(sv[0]);
                perror("child: recv() error");
                return EXIT_FAILURE;
            } else if (bytes == 0) {
                close(sv[0]);
                printf("child: recv(): connection closed\n");
                return EXIT_FAILURE;
            } else {
                printf("child: recv() %jd bytes: %.*s",
                       (intmax_t) bytes, (int) bytes, buffer);
            }
            break;

            /* It is not okay for the same process (i.e. either child or
             * parent) to use both sockets. For example, say if the
             * child sends on sv[0] and then receives on sv[1], then it
             * may end up reading its own message. Any messages send to
             * sv[0] are received on sv[1] and vice versa.
             *
             * Thus one process should stick to reading and writing from
             * sv[0], and the other should stick to sv[1]. It does not
             * matter which process chooses sv[0] and which one chooses
             * sv[1] as long as they stick to one socket each.
             */

        default:
            close(sv[0]);

            /* Receive at parent. */
            bytes = recv(sv[1], buffer, sizeof buffer, 0);
            if (bytes == -1) {
                close(sv[1]);
                perror("parent: recv() error");
                return EXIT_FAILURE;
            } else if (bytes == 0) {
                close(sv[1]);
                printf("parent: recv(): connection closed\n");
                return EXIT_FAILURE;
            } else {
                printf("parent: recv() %jd bytes: %.*s",
                       (intmax_t) bytes, (int) bytes, buffer);
            }

            /* Send from parent to child. */
            strcpy(buffer, "hello from parent\n");
            bytes = send(sv[1], buffer, strlen(buffer), 0);
            if (bytes == -1) {
                close(sv[1]);
                perror("child: send( error");
                return EXIT_FAILURE;
            }
            printf("parent: send() %jd bytes: %s", bytes, buffer);

            wait(NULL);
    }

    return EXIT_SUCCESS;
}
