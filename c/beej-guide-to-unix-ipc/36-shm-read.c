#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
    key_t key;
    int shmid;
    char *mem;

    if ((key = ftok("/tmp/shmkey", 0)) == -1) {
        fprintf(stderr, "%d: ftok() error: %d: %s\n",
                getpid(), errno, strerror(errno));
        return EXIT_FAILURE;
    }

    if ((shmid = shmget(key, 100, 0400 | IPC_CREAT)) == -1) {
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

    do {
        printf("%d: read: %s\n", getpid(), mem);
        sleep(1);
    } while (strncmp(mem, "exit", 4) != 0);

    printf("%d: final read: %s\n", getpid(), mem);

    return EXIT_SUCCESS;
}
