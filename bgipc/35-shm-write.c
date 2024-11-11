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
    int i;

    if ((key = ftok("/tmp/shmkey", 0)) == -1) {
        fprintf(stderr, "%d: ftok() error: %d: %s\n",
                getpid(), errno, strerror(errno));
        return EXIT_FAILURE;
    }

    // With 0777 permissions, ipcs also shows 0777.
    // 0x0001085a 1900552    susam      777        100        1

    // If shm is created with size = 100 by an earlier process, and then
    // another process gets the shm with a larger size, e.g. size = 101,
    // the following error occurs.
    //
    // shmget() error: 22: Invalid argument
    //
    // This error does not occur if the new size is less than the
    // original size.

    // With 0200 or 0400 permissions, the shmat() call below fails. See
    // man shmat: SHM_RDONLY for more details.
    //
    // shmat() error: 13: Permission denied
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

    for (i = 0; i < 3; i++) {
        snprintf(mem, 100, "hello %d", i);
        printf("%d: write: %s\n", getpid(), mem);
        sleep(3);
    }

    snprintf(mem, 100, "exit");
    printf("%d: final write: %s\n", getpid(), mem);

    return EXIT_SUCCESS;
}
