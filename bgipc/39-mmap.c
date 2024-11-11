#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main()
{
    int fd;
    int pagesize;
    long pagesz;
    char *data;

    if ((fd = open("/tmp/foo.txt", O_RDONLY)) == -1) {
        perror("open()");
        return EXIT_FAILURE;
    }

    // getpagesize() is dropped in POSIX.1-2001, therefore it requires
    // _BSD_SOURCE macro to be defined. sysconf() call should be used
    // instead.
    pagesize = getpagesize();
    printf("pagesize: %d\n", pagesize);

    // This is the current way of finding page size.
    pagesz = sysconf(_SC_PAGESIZE);
    printf("pagesz: %ld\n", pagesz);

    // If PROT_READ | PROT_WRITE is passed instead, the following call
    // returns -1 and the error is "Permission denied".
    data = mmap(NULL, pagesz, PROT_READ, MAP_SHARED, fd, 0);
    printf("data: %p\n", data);
    if (data == (void *) -1) {
        perror("mmap()");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < 2; i++) {
        printf("data[%d]: %d\n", i, data[i]);
    }

    for (int i = pagesz - 2; i < pagesz + 2; i++) {
        printf("data[%d]: %d\n", i, data[i]);
    }

    // The following statement leads to: Segmentation fault.
    // data[0] = 'B';

    return EXIT_SUCCESS;
}
