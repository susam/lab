#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define FIFO "fifo"

int main()
{
    int fd;

    if (mknod(FIFO, S_IFIFO | 0644, 0) == -1) {
        perror("reader: mknod()");
    } else {
        printf("reader: created fifo\n");
    }

    printf("reader: opening file ...\n");
    fd = open(FIFO, O_RDONLY | O_NDELAY);

    if (fd == -1) {
        perror("reader: open()");
        return EXIT_FAILURE;
    } else {
        printf("reader: opened fifo\n");
    }

    while (1) {
        char buffer[100];
        printf("reader: reading from pipe ...\n");
        int bytes = read(fd, buffer, sizeof buffer);
        if (bytes == -1) {
            perror("read()");
        } else if (strncmp(buffer, "exit", 4) == 0) {
            printf("breaking ...\n");
            break;
        } else if (bytes == 0) {
            printf("reader: no data\n");
        } else {
            printf("reader: read %d bytes: %.*s", bytes, bytes, buffer);
        }

        sleep(1);
    }

    printf("exiting ...\n");

    return EXIT_SUCCESS;
}
