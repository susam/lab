#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

int main()
{
    int fds[2];
    char buf[10];
    ssize_t bytes;

    if (pipe(fds) == -1) {
        perror("pipe()");
        return EXIT_FAILURE;
    }

    /* fds[0] is the read end of the pipe and fds[1] is the write end of
     * the pipe. Trying to write to fds[0] below, or trying to read from
     * fds[1] leads to the following error:
     *
     * Bad file descriptor */
    bytes = write(fds[1], "hello", 5);
    if (bytes == -1) {
        perror("write()");
    } else {
        printf("Written %jd bytes.\n", (intmax_t) bytes);
    }

    bytes = write(fds[1], "world", 6);
    if (bytes == -1) {
        perror("write()");
    } else {
        printf("Written %jd bytes.\n", (intmax_t) bytes);
    }

    bytes = read(fds[0], buf, 6);
    if (bytes == -1) {
        perror("read()");
    } else {
        buf[bytes] = '\0';
        printf("Read %jd bytes: %s\n", (intmax_t) bytes, buf);
    }

    bytes = read(fds[0], buf, 6);
    if (bytes == -1) {
        perror("read()");
    } else {
        buf[bytes] = '\0';
        printf("Read %jd bytes: %s\n", (intmax_t) bytes, buf);
    }

    // The following call blocks because it waits for further input.
    // bytes = read(fds[0], buf, 6);

    return EXIT_SUCCESS;
}
