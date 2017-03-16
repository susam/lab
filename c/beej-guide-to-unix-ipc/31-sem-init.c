#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <sys/sem.h>

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
    int nsems = 4;
    int i;
    union semun arg;
    unsigned short arg_array[100];

    /* Get semaphore set. */
    if ((key = ftok("/tmp/semkey", 0)) == -1) {
        fprintf(stderr, "error %d: %s\n", errno, strerror(errno));
        return EXIT_FAILURE;
    }

    if ((semid = semget(key, nsems, IPC_CREAT | 0600)) == -1) {
        fprintf(stderr, "error %d: %s\n", errno, strerror(errno));
        return EXIT_FAILURE;
    }

    printf("init: key: 0x%jx; semid: %d\n", (intmax_t) key, semid);

    /* Initialize semaphore set. */
    for (i = 0; i < nsems; i++) {
        arg_array[i] = 0;
    }

    arg.array = arg_array;

    if (semctl(semid, 0, SETALL, arg) == -1) {
        fprintf(stderr, "error %d: %s\n", errno, strerror(errno));
        return EXIT_FAILURE;
    }

    print_sem(semid, "init");

    return EXIT_SUCCESS;
}
