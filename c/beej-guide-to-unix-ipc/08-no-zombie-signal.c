
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main()
{
    pid_t pid;

    printf("begin parent\n");
    signal(SIGCHLD, SIG_IGN);

    pid = fork();

    if (pid == -1) {
        return EXIT_FAILURE;
    } else if (pid == 0) {
        printf("begin child\n");
        sleep(2);
        printf("end child\n");
    } else {
        sleep(4);
        printf("end parent\n");
    }

    return EXIT_SUCCESS;
}
