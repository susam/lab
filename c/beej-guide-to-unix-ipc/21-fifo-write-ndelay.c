#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define FIFO "fifo"

int main()
{
    int fd;

    printf("ENXIO: %d\n", ENXIO);

    if (mknod(FIFO, S_IFIFO | 0644, 0) == -1) {
        perror("writer: mknod()");
    } else {
        printf("writer: created fifo\n");
    }

    do {
        printf("writer: opening fifo ...\n");
        fd = open(FIFO, O_WRONLY | O_NDELAY);

        if (fd == -1) {
            fprintf(stderr, "open(): %d: %s\n", errno, strerror(errno));
        } else {
            printf("writer: opened fifo\n");
        }

        sleep(1);
    } while (fd == -1);

    for (int i = 0; i < 3; i++) {
        int bytes;
        char buffer[100];

        printf("writer: writing to pipe ...\n");        
        snprintf(buffer, sizeof buffer, "writer: hello %d\n", i);
        bytes = write(fd, buffer, strlen(buffer));
        if (bytes == -1) {
            perror("writer: write()");
        } else {
            printf("writer: wrote %d bytes\n", bytes);
        }
        sleep(1);
    }

    return EXIT_SUCCESS;
}
