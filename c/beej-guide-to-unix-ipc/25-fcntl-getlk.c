#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    struct flock fl;
    int fd;

    int l_type;
    int o_flags;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s r|w r|w\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strncmp(argv[1], "r", 2) == 0) {
        l_type = F_RDLCK;
    } else if (strncmp(argv[1], "w", 2) == 0) {
        l_type = F_WRLCK;
    } else {
        fprintf(stderr, "Bad argument: \"%s\"\n", argv[1]);
        return EXIT_FAILURE;
    }

    if (strncmp(argv[2], "r", 2) == 0) {
        o_flags = O_RDONLY;
    } else if (strncmp(argv[2], "w", 2) == 0) {
        o_flags = O_WRONLY;
    } else {
        fprintf(stderr, "Bad argument: \"%s\"\n", argv[1]);
        return EXIT_FAILURE;
    }

    fl.l_type = l_type;
    fl.l_whence = SEEK_SET;
    fl.l_start = fl.l_len = fl.l_pid = 0;

    printf("%d: opening file ...\n", getpid());
    if ((fd = open("lock", o_flags | O_CREAT, 0644)) == -1) {
        perror("open()");
        return EXIT_FAILURE;
    }

    printf("%d: getting lock information ...\n",getpid());
    if (fcntl(fd, F_GETLK, &fl) == -1) {
        close(fd);
        perror("fcntl()");
        return EXIT_FAILURE;
    }

    printf("F_RDLCK: %d; F_WRLCK: %d; F_UNLCK: %d\n",
           F_RDLCK, F_WRLCK, F_UNLCK);
    printf("l_type: %jd\n", (intmax_t) fl.l_type);
    printf("l_whence: %jd\n", (intmax_t) fl.l_whence);
    printf("l_start: %jd\n", (intmax_t) fl.l_start);
    printf("l_len: %jd\n", (intmax_t) fl.l_len);
    printf("l_pid: %jd\n", (intmax_t) fl.l_pid);

    printf("%d: exiting ...\n", getpid());
    close(fd);
    return EXIT_SUCCESS;
}
