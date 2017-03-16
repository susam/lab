#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
    key_t key;
    int msgid;

    key = ftok("/tmp/msgkey", 0);
    printf("msgrcv: key: 0x%jx\n", (intmax_t) key);

    if ((msgid = msgget(key, IPC_CREAT | 0600)) == -1) {
        perror("msgget()");
        return EXIT_FAILURE;
    }

    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl()");
        return EXIT_FAILURE;
    }

    printf("Removed queue with key 0x%jx and msgid %d.\n",
           (intmax_t) key, msgid);

    return EXIT_SUCCESS;
}
