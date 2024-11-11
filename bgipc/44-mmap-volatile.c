#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main()
{
    int fd;
    long pagesize;

#ifdef VOLATILE
    volatile char *data;
#else
    char *data;
#endif

    if ((fd = open("/tmp/foo.txt", O_RDONLY)) == -1) {
        perror("open()");
        return EXIT_FAILURE;
    }

    pagesize = sysconf(_SC_PAGESIZE);
    printf("pagesize: %ld\n", pagesize);

    data = mmap(NULL, pagesize, PROT_READ, MAP_SHARED, fd, 0);
    if (data == (void *) -1) {
        perror("mmap()");
        return EXIT_FAILURE;
    }
    printf("data: %p\n", data);

    while (data[0] != 'X')
        ;

    printf("exiting ...\n");

    return EXIT_SUCCESS;
}
