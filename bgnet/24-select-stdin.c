#include <stdio.h>
#include <sys/select.h>
#include <sys/time.h>
#include <stdint.h>
#include <stdlib.h>

void checkfds(fd_set *fds)
{
    int timeout = 1;

    for (int fd = 0; fd < 3; fd++) {
        if (FD_ISSET(fd, fds)) {
            printf("fd %d ready\n", fd);
            timeout = 0;
        }
    }

    if (FD_ISSET(0, fds)) {
        char buffer[1024];
        printf("Reading from stdin ...\n");
        fgets(buffer, sizeof buffer / sizeof *buffer, stdin);
        printf("fgets(): %s", buffer);
    }

    if (timeout) {
        printf("timeout\n");
    }
}

void reselect(fd_set *fds)
{
    struct timeval tv; /* For use with select. */
    struct timeval tv0, tv1; /* For tracking time spent ourselves. */
    tv.tv_sec = 10;
    tv.tv_usec = 0;

    FD_ZERO(fds);
    FD_ZERO(fds);
    FD_SET(0, fds);
    FD_SET(1, fds);
    FD_SET(2, fds);

    printf("Waiting ...\n");
    if (gettimeofday(&tv0, NULL) == -1) {
        perror("gettimeofday() error");
        exit(EXIT_FAILURE);
    }

    if (select(3, fds, NULL, NULL, &tv) == -1) {
        perror("select() error");
        exit(EXIT_FAILURE);
    }

    if (gettimeofday(&tv1, NULL) == -1) {
        perror("gettimeofday() error");
        exit(EXIT_FAILURE);
    }

    /* On Linux, select() modifies timeout to reflect the amount of time
     * not slept; most other implementations do not do this.
     * Consider timeout to be undefined after select() returns. */
    printf("time_elapsed (10  - tv ): %f\n",
           10 - (tv.tv_sec + tv.tv_usec / 1000000.0));

    printf("time_elapsed (tv1 - tv0): %f\n",
           tv1.tv_sec + tv1.tv_usec / 1000000.0 -
           tv0.tv_sec - tv0.tv_usec / 1000000.0);
}


int main()
{
    fd_set readfds;

    reselect(&readfds);
    checkfds(&readfds);

    reselect(&readfds);
    checkfds(&readfds);

    return EXIT_SUCCESS;
}
