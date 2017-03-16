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

int main(int argc, char **argv)
{
    key_t key;
    int semid;
    int nsops;
    struct sembuf sb[1000];
    int i;
    int sleep_duration;

    /* Determine the number of semaphore operations. */
    if (argc < 3) {
        fprintf(stderr, "Usage: %s SLEEP_DURATION SEMVAL1 SEMVAL2 ...\n",
                argv[0]);
        return EXIT_FAILURE;
    } 

    sleep_duration = atoi(argv[1]);
    nsops = argc - 2;
    if (nsops > 1000)
        nsops = 1000;

    /* Prepare semaphore operations. */
    for (i = 0; i < nsops; i++) {
        sb[i].sem_num = i;
        sb[i].sem_op = atoi(argv[i + 2]);
        sb[i].sem_flg = SEM_UNDO;
    }

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

    printf("%d: ", getpid());
    print_sem(semid, "before lock");

    if (semop(semid, sb, nsops) == -1) {
        // If semaphore set is remove when semop() is blocked, errno = EIDRM.
        // semop() error 43: Identifier removed
        fprintf(stderr, "%d: semop() error %d: %s\n",
                getpid(), errno, strerror(errno));
        return EXIT_FAILURE;
    }

    printf("%d: ", getpid());
    print_sem(semid, "after  lock");

    printf("%d: sleeping for %d seconds ...\n", getpid(), sleep_duration);
    sleep(sleep_duration);

    printf("%d: exiting ...\n", getpid());
    return EXIT_SUCCESS;
}
