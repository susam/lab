#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main()
{
    int fd;
    long pagesize;
    char *data;

    if ((fd = open("/tmp/foo.txt", O_RDWR)) == -1) {
        perror("open()");
        return EXIT_FAILURE;
    }

    pagesize = sysconf(_SC_PAGESIZE);
    printf("pagesize: %ld\n", pagesize);

    data = mmap(NULL, pagesize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (data == (void *) -1) {
        perror("mmap()");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < 3; i++) {
        printf("data[%d]: %c\n", i, data[i]);
    }

    sleep(4);

    for (int i = 0; i < 3; i++) {
        printf("data[%d]: %c\n", i, data[i]);
    }

    printf("writing ...\n");
    data[2] = 'X';

    for (int i = 0; i < 3; i++) {
        printf("data[%d]: %c\n", i, data[i]);
    }

    printf("exiting ...\n");

    return EXIT_SUCCESS;
}
