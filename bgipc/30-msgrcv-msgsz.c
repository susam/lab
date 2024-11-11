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

void rcv(int msgid, size_t msgsz, int msgflag)
{
    unsigned char buf[100];
    ssize_t bytes;
    if ((bytes = msgrcv(msgid, buf, msgsz, 0, msgflag)) == -1) {
        perror("msgrcv()");
        return;
    }

    printf("msgtyp: ");
    for (size_t i = 0; i < sizeof (long); i++) {
        printf("%02x ", buf[i]);
    }

    printf("; data: ");
    for (size_t i = sizeof (long); i < bytes + sizeof (long); i++) {
        printf("%02x ", buf[i]);
    }
    printf("\n");
}

int main()
{
    key_t key;
    int msgid;

    if ((key = ftok("/tmp/msgkey", 0)) == -1) {
        // If the file does not exist, errno = ENOENT.
        // error 2: No such file or directory
        fprintf(stderr, "ftok(): error %d: %s\n", errno, strerror(errno));
        return EXIT_FAILURE;
    }

    if ((msgid = msgget(key, IPC_CREAT | 0600)) == -1) {
        perror("msgget()");
        return EXIT_FAILURE;
    }

    printf("msgsz: key: 0x%jx; semid: %d\n", (intmax_t) key, msgid);

    rcv(msgid, 100, 0);
    rcv(msgid, 8, 0);
    rcv(msgid, 4, 0); // Error E2BIG: Argument list too long
    rcv(msgid, 4, MSG_NOERROR); // Suppresses E2BIG and truncates data
    rcv(msgid, 100, 0);
    rcv(msgid, 100, 0);

    printf("msgrcv: exiting ...\n");
    return EXIT_SUCCESS;
}
