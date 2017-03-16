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

    if ((fd = open("/tmp/foo.txt", O_RDONLY)) == -1) {
        perror("open()");
        return EXIT_FAILURE;
    }

    pagesize = sysconf(_SC_PAGESIZE);
    printf("pagesize: %ld\n", pagesize);

    data = mmap(NULL, pagesize, PROT_READ, MAP_SHARED, fd, pagesize);
    if (data == (void *) -1) {
        perror("mmap()");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < 5; i++) {
        printf("data[%d]: %d\n", i, data[i]);
    }

    return EXIT_SUCCESS;
}
