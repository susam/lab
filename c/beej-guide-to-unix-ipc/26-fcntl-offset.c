#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    struct flock fl;
    int fd;

    int l_type;
    int o_flags;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s r|w r|w\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strncmp(argv[1], "r", 2) == 0) {
        l_type = F_RDLCK;
        o_flags = O_RDONLY;
    } else if (strncmp(argv[1], "w", 2) == 0) {
        l_type = F_WRLCK;
        o_flags = O_WRONLY;
    } else {
        fprintf(stderr, "Bad argument: \"%s\"\n", argv[1]);
        return EXIT_FAILURE;
    }

    fl.l_type = l_type;
    fl.l_whence = SEEK_SET;
    fl.l_start = atoi(argv[2]);
    fl.l_len = atoi(argv[3]);
    fl.l_pid = 0;

    printf("%d: opening file ...\n", getpid());
    if ((fd = open("lock", o_flags | O_CREAT, 0644)) == -1) {
        perror("open()");
        return EXIT_FAILURE;
    }

    printf("%d: locking file ...\n",getpid());
    if (fcntl(fd, F_SETLK, &fl) == -1) {
        perror("fcntl()");
        return EXIT_FAILURE;
    }

    printf("%d: acquired lock; sleeping ...\n", getpid());
    sleep(4);

    printf("%d: unlocking ....\n", getpid());
    fl.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLKW, &fl) == -1) {
        perror("fcntl()");
        return EXIT_FAILURE;
    }

    printf("%d: exiting ...\n", getpid());
    return EXIT_SUCCESS;
}
