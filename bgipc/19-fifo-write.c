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

    // If permissions (0777) is not specified, then the fifo file is
    // created as p--------- and the open() call later fails with
    // "Permission denied".
    if (mknod(FIFO, S_IFIFO | 0777, 0) == -1) {
        perror("writer: mknod()");
    } else {
        printf("writer: created fifo\n");
    }

    sleep(4);

    printf("writer: opening fifo ...\n");
    fd = open(FIFO, O_WRONLY);

    if (fd == -1) {
        perror("writer: open()");
        return EXIT_FAILURE;
    } else {
        printf("writer: opened fifo\n");
    }

    sleep(2);

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
