#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char **argv)
{
    key_t key;
    int shmid;
    char *mem;
    int detach;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s 0|1\n", argv[0]);
        return EXIT_FAILURE;
    }

    detach = atoi(argv[1]);

    if ((key = ftok("/tmp/shmkey", 0)) == -1) {
        fprintf(stderr, "%d: ftok() error: %d: %s\n",
                getpid(), errno, strerror(errno));
        return EXIT_FAILURE;
    }

    if ((shmid = shmget(key, 100, 0600 | IPC_CREAT)) == -1) {
        fprintf(stderr, "%d: shmget() error: %d: %s\n",
                getpid(), errno, strerror(errno));
        return EXIT_FAILURE;
    }

    printf("key: 0x%x; shmid: %d\n", key, shmid);

    if ((mem = shmat(shmid, NULL, 0)) == (void *) -1) {
        fprintf(stderr, "%d: shmat() error: %d: %s\n",
                getpid(), errno, strerror(errno));
        return EXIT_FAILURE;
    }

    printf("shmat() done\n");
    sleep(4);

    if (!detach) {
        printf("detach is false; exiting ...\n");
        return EXIT_SUCCESS;
    }


    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        fprintf(stderr, "%d: shmdt() error: %d: %s\n",
                getpid(), errno, strerror(errno));
        return EXIT_FAILURE;
    }

    printf("shmctl(IPC_RMID) done\n");
    sleep(4);

    if (shmdt(mem) == -1) {
        fprintf(stderr, "%d: shmdt() error: %d: %s\n",
                getpid(), errno, strerror(errno));
        return EXIT_FAILURE;
    }

    printf("shmdt() done\n");
    sleep(4);

    printf("exiting ...\n");
    return EXIT_SUCCESS;
}
