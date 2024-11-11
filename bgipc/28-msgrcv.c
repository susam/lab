#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <string.h>
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
        fprintf(stderr, "ftok(): error %d: %s\n", errno, strerror(errno));
        return EXIT_FAILURE;
    }

    if ((msgid = msgget(key, IPC_CREAT | 0600)) == -1) {
        fprintf(stderr, "msgget(): error %d: %s\n", errno, strerror(errno));
        return EXIT_FAILURE;
    }

    // Positive msgtype
    if (msgrcv(msgid, &msg, sizeof msg.mdata, 3, 0) == -1) {
        // If the message queue is removed, errno = EIDRM.
        // error 43: Identifier removed
        fprintf(stderr, "msgrcv(): error %d: %s\n", errno, strerror(errno));
        return EXIT_FAILURE;
    }
    printf("msgrcv: %ld, %d, %d <= %d\n",
           msg.mtype, msg.mdata.x, msg.mdata.y, msgid);

    // Negative msgtype
    if (msgrcv(msgid, &msg, sizeof msg.mdata, -3, 0) == -1) {
        fprintf(stderr, "msgrcv(): error %d: %s\n", errno, strerror(errno));
        return EXIT_FAILURE;
    }
    printf("msgrcv: %ld, %d, %d <= %d\n",
           msg.mtype, msg.mdata.x, msg.mdata.y, msgid);

    // Zero msgtype
    do {
        if (msgrcv(msgid, &msg, sizeof msg.mdata, 0, 0) == -1) {
            fprintf(stderr, "msgrcv(): error %d: %s\n", errno, strerror(errno));
            return EXIT_FAILURE;
        }

        printf("msgrcv: %ld, (%d, %d) <= %d\n",
               msg.mtype, msg.mdata.x, msg.mdata.y, msgid);

    } while (msg.mdata.x != -1);

    printf("msgrcv: exiting ...\n");
    return EXIT_SUCCESS;
}
