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

    // It is okay to mmap with PROD_READ only when file is opened with O_RDWR.
    data = mmap(NULL, pagesize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (data == (void *) -1) {
        perror("mmap()");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < 5; i++) {
        printf("data[%d]: %d\n", i, data[i]);
    }

    data[2] = 'X';
    data[3] = 'Y';
    data[4] = 'Z';

    sleep(4);
    printf("exiting ...\n");

    return EXIT_SUCCESS;
}
