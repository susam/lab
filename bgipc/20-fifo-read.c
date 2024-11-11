#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define FIFO "fifo"

int main(int argc, char **argv)
{
    int fd;
    int break_read;

    if (argc != 2) {
        printf("Usage: %s 0|1\n", argv[0]);
        return EXIT_FAILURE;
    }

    break_read = atoi(argv[1]);

    if (mknod(FIFO, S_IFIFO | 0777, 0) == -1) {
        perror("reader: mknod()");
    } else {
        printf("reader: created fifo\n");
    }

    sleep(4);

    printf("reader: opening file ...\n");
    fd = open(FIFO, O_RDONLY);

    if (fd == -1) {
        perror("reader: open()");
        return EXIT_FAILURE;
    } else {
        printf("reader: opened fifo\n");
    }

    sleep(2);

    while (1) {
        char buffer[100];
        int bytes = read(fd, buffer, sizeof buffer);
        if (bytes == -1) {
            perror("read()");
        } else if (bytes == 0) {
            printf("reader: end\n");
            break;
        } else {
            printf("reader: read %d bytes: %.*s", bytes, bytes, buffer);
        }

        if (break_read)
            break;
    }

    printf("exiting ...\n");

    return EXIT_SUCCESS;
}
