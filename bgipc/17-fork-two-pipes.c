#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/wait.h>

int main()
{
    int cpfds[2]; // Child to parent pipe
    int pcfds[2]; // Parent tto child pipe

    char buf[10];
    ssize_t bytes;
    int ret;

    if (pipe(cpfds) == -1) {
        perror("pipe(cpfds)");
        return EXIT_FAILURE;
    }

    if (pipe(pcfds) == -1) {
        perror("pipe(pcfds)");
        return EXIT_FAILURE;
    }

    ret = fork();
    if (ret == -1) {
        perror("fork()");
        return EXIT_FAILURE;
    }

    if (ret != 0) {
        close(cpfds[1]);
        close(pcfds[0]);

        printf("parent: reading ...\n");
        bytes = read(cpfds[0], buf, 10);

        if (bytes == -1) {
            perror("parent: read()");
        } else {
            printf("parent: read %jd bytes: %s\n", (intmax_t) bytes, buf);
        }

        printf("parent: writing ...\n");
        bytes = write(pcfds[1], "hey", 4);

        if (bytes == -1) {
            perror("parent: write()");
        } else {
            printf("parent: written %jd bytes\n", (intmax_t) bytes);
        }

        if (wait(NULL) == -1) {
            perror("parent: wait()");
        }
    } else {
        close(cpfds[0]);
        close(pcfds[1]);

        printf("child: writing ...\n");
        bytes = write(cpfds[1], "hello", 6);

        if (bytes == -1) {
            perror("child: write()");
        } else {
            printf("child: written %jd bytes\n", (intmax_t) bytes);
        }

        printf("child: reading ...\n");
        bytes = read(pcfds[0], buf, 10);

        if (bytes == -1) {
            perror("child: read()");
        } else {
            printf("child: read %jd bytes: %s\n", (intmax_t) bytes, buf);
        }
    }

    return EXIT_SUCCESS;
}
