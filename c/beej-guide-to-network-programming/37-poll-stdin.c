#include <stdio.h>
#include <sys/time.h>
#include <stdint.h>
#include <stdlib.h>
#include <poll.h>

void checkfds(struct pollfd *fds)
{
    for (int fd = 0; fd <= 2; fd++) {
        printf("fd %d:", fd);
        if (fds[fd].revents & POLLIN) {
            printf(" POLLIN");
        }
        
        if (fds[fd].revents & POLLPRI) {
            printf(" POLLPRI");
        }
        
        if (fds[fd].revents & POLLOUT) {
            printf(" POLLOUT");
        }
        
        if (fds[fd].revents & POLLERR) {
            printf(" POLLERR");
        }
        
        if (fds[fd].revents & POLLHUP) {
            printf(" POLLHUP");
        }
        
        if (fds[fd].revents & POLLNVAL) {
            printf(" POLLNVAL");
        }
        printf("\n");
    }

    if (fds[0].revents & POLLIN) {
        char buffer[1024];
        printf("Reading from stdin ...\n");
        fgets(buffer, sizeof buffer / sizeof *buffer, stdin);
        printf("fgets(): %s", buffer);
    }
}

void repoll(struct pollfd *fds)
{
    struct timeval tv0, tv1;
    int ret;

    printf("Waiting ...\n");
    if (gettimeofday(&tv0, NULL) == -1) {
        perror("gettimeofday() error");
        return;
    }


    ret = poll(fds, 3, 10000);

    if (ret == -1) {
        perror("poll() error");
        return;
    } else if (ret == 0) {
        printf("timed out\n");
        return;
    }

    if (gettimeofday(&tv1, NULL) == -1) {
        perror("gettimeofday() error");
        return;
    }

    printf("time_elapsed (tv1 - tv0): %f\n",
           tv1.tv_sec + tv1.tv_usec / 1000000.0 -
           tv0.tv_sec - tv0.tv_usec / 1000000.0);
}


int main()
{
    struct pollfd fds[16];

    for (int fd = 0; fd <=2; fd++) {
        fds[fd].fd = fd;
        fds[fd].events = POLLIN | POLLPRI;
    }

    repoll(fds);
    checkfds(fds);

    repoll(fds);
    checkfds(fds);

    repoll(fds);
    checkfds(fds);

    return EXIT_SUCCESS;
}
