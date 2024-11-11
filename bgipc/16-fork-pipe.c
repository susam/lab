#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/wait.h>

int main()
{
    int fds[2];
    char buf[10];
    ssize_t bytes;
    int ret;

    if (pipe(fds) == -1) {
        perror("pipe()");
        return EXIT_FAILURE;
    }

    ret = fork();
    if (ret == -1) {
        perror("fork()");
        return EXIT_FAILURE;
    }

    if (ret != 0) {
        close(fds[1]);

        printf("parent: reading ...\n");
        bytes = read(fds[0], buf, 6);

        if (bytes == -1) {
            perror("parent: read()");
        } else {
            printf("parent: read %jd bytes: %s\n", (intmax_t) bytes, buf);
        }

        if (wait(NULL) == -1) {
            perror("parent: wait()");
        }
    } else {
        close(fds[0]);

        printf("child: writing ...\n");
        bytes = write(fds[1], "hello", 6);

        if (bytes == -1) {
            perror("child: write()");
        } else {
            printf("child: written %jd bytes\n", (intmax_t) bytes);
        }
    }

    return EXIT_SUCCESS;
}
