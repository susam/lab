#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
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
        fprintf(stderr, "%d: semctl IPC_STAT error %d: %s\n",
                getpid(), errno, strerror(errno));
    }

    if (semctl(semid, 0, GETALL, arg) == -1) {
        fprintf(stderr, "%d: semctl GETALL error %d: %s\n",
                getpid(), errno, strerror(errno));
    }

    printf("%d: %s: semid: %d; nsems: %lu; otime: %ld; ctime: %ld; set:",
           getpid(), msg, semid, arg.buf->sem_nsems,
           arg.buf->sem_otime, arg.buf->sem_ctime);

    for (i = 0; i < arg.buf->sem_nsems && i < 100; i++) {
        printf(" %hu", arg.array[i]);
    }

    printf("\n");
}


int initsem(int semval, int nsems)
{
    key_t key;
    int semid;

    /* Get semaphore set. */
    if ((key = ftok("/tmp/semkey", 0)) == -1) {
        int e = errno;
        fprintf(stderr, "%d: ftok() error %d: %s\n",
                getpid(), errno, strerror(errno));
        errno = e;
        return -1;
    }
    printf("%d: key: 0x%x\n", getpid(), key);

    if ((semid = semget(key, nsems, IPC_CREAT | IPC_EXCL | 0600)) == -1 &&
        errno != EEXIST) {

        int e = errno;
        fprintf(stderr, "%d: semget() error %d: %s\n",
                getpid(), errno, strerror(errno));
        errno = e;
        return -1;

    } else if (semid >= 0) {

        union semun arg;
        unsigned short arg_array[100];
        struct sembuf sops[100];
        int i;

        printf("%d: created semaphore set %d\n", getpid(), semid);
        print_sem(semid, "uninitialized");

        /* Prepare initialization data. */
        for (i = 0; i < nsems; i++) {
            arg_array[i] = 0;
        }
        arg.array = arg_array;

        /* Initialize semaphore set. */
        if (semctl(semid, 0, SETALL, arg) == -1) {
            int e = errno;

            fprintf(stderr, "%d: semctl(SETALL) error %d: %s\n",
                    getpid(), errno, strerror(errno));

            if (semctl(semid, 0, IPC_RMID) == -1) {
                fprintf(stderr, "%d: semctl(IPC_RMID) error %d: %s\n",
                        getpid(), errno, strerror(errno));
            }

            errno = e;
            return -1;
        }

        print_sem(semid, "initialized");
        sleep(4);

        /* Prepare semaphore operations to free semaphores. */
        for (i = 0; i < nsems; i++) {
            sops[i].sem_num = i;
            sops[i].sem_op = semval;
            sops[i].sem_flg = SEM_UNDO;
        }

        /* Free semaphores. */
        if (semop(semid, sops, nsems) == -1) {
            int e = errno;

            fprintf(stderr, "%d: semop() error %d: %s\n",
                    getpid(), errno, strerror(errno));

            errno = e;
            return -1;
        }

        print_sem(semid, "freed");
        
        /* Allow another process to acquire lock and consume resources. */
        sleep(5);

    } else { // semid == -1 && errno == EEXIST

        union semun arg;
        struct semid_ds buf;
        int i;
        int max_retries = 5;

        printf("%d: could not create semaphore set\n", getpid());

        if ((semid = semget(key, nsems, 0)) == -1) {
            int e = errno;
            fprintf(stderr, "%d: semget() error %d: %s\n",
                    getpid(), errno, strerror(errno));
            errno = e;
            return -1;
        }

        print_sem(semid, "inspecting");

        arg.buf = &buf;

        for (i = 0; i < max_retries; i++) {
            if ((semctl(semid, 0, IPC_STAT, arg)) == -1) {
                fprintf(stderr, "%d: semctl(IPC_STAT) error %d: %s\n",
                        getpid(), errno, strerror(errno));
                sleep(1);
                continue;
            }

            if (arg.buf->sem_otime == 0) {
                printf("%d: waiting for semaphore set to be initialized ...\n",
                       getpid());
                sleep(1);
                continue;
            }

            break;
        }

        if (i == max_retries) {
            fprintf(stderr, "%d: semaphore set not found initialized\n", getpid());
            errno = ETIME;
            return -1;
        }

        print_sem(semid, "found initialized");
    }

    return semid;
}


int main()
{
    if (initsem(5, 4) == -1) {
        fprintf(stderr, "%d: initsem() error %d: %s\n",
                getpid(), errno, strerror(errno));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
