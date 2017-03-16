#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

struct foo_msgbuf {
    long mtype;

    struct {
        int x;
        int y;
    } mdata;
};

int main()
{
    key_t key;
    int msgid;
    struct foo_msgbuf msg;

    if ((key = ftok("/tmp/msgkey", 0)) == -1) {
        // If the file does not exist, errno = ENOENT.
        // error 2: No such file or directory
        fprintf(stderr, "ftok(): error %d: %s\n", errno, strerror(errno));
        return EXIT_FAILURE;
    }

    if ((msgid = msgget(key, IPC_CREAT | 0600)) == -1) {
        fprintf(stderr, "msgget(): error %d: %s\n", errno, strerror(errno));
        return EXIT_FAILURE;
    }

    printf("msgsnd: key: 0x%jx; semid: %d\n", (intmax_t) key, msgid);

    for (int i = 1; i <= 5; i++) {
        msg.mtype = i;
        msg.mdata.x = i == 5 ? -1 : 10 * i;
        msg.mdata.y = 10 * i + 1;

        if (msgsnd(msgid, &msg, sizeof msg.mdata, 0) == -1) {
            // If the message queue is removed, errno = EINVAL.
            // error 22: Invalid argument
            fprintf(stderr, "msgsnd(): error %d: %s\n", errno, strerror(errno));
            return EXIT_FAILURE;
        }

        printf("msgsnd: %ld, (%d, %d) => %d\n",
               msg.mtype, msg.mdata.x, msg.mdata.y, msgid);
        sleep(1);
    }

    return EXIT_SUCCESS;
}
