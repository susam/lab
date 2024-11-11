#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/ipc.h>

union semun {
   int              val;    /* Value for SETVAL */
   struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
   unsigned short  *array;  /* Array for GETALL, SETALL */
};

void print_sem(int semid, char *msg)
{
    unsigned long i;
    union semun arg;
    unsigned short arg_array[100];
    arg.array = arg_array;

    if (semctl(semid, 0, IPC_STAT, arg) == -1) {
        fprintf(stderr, "semctl IPC_STAT error %d: %s\n", errno, strerror(errno));
    }

    if (semctl(semid, 0, GETALL, arg) == -1) {
        fprintf(stderr, "semctl GETALL error %d: %s\n", errno, strerror(errno));
    }

    printf("%s: %lu:", msg, arg.buf->sem_nsems);
    for (i = 0; i < arg.buf->sem_nsems && i < 100; i++) {
        printf(" %hu", arg.array[i]);
    }
    printf("\n");
}

int main()
{
    key_t key;
    int semid;

    /* Get semaphore set. */
    if ((key = ftok("/tmp/semkey", 0)) == -1) {
        fprintf(stderr, "%d: ftok() error %d: %s\n",
                getpid(), errno, strerror(errno));
        return EXIT_FAILURE;
    }

    if ((semid = semget(key, 0, 0)) == -1) {
        fprintf(stderr, "%d: semget() error %d: %s\n",
                getpid(), errno, strerror(errno));
        return EXIT_FAILURE;
    }

    printf("%d: key: 0x%jx; semid: %d\n", getpid(), (intmax_t) key, semid);

    /* Remove semaphore. */
    if ((semid == semctl(semid, 0, IPC_RMID)) == -1) {
        fprintf(stderr, "%d: semctl() error %d: %s\n",
                getpid(), errno, strerror(errno));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
