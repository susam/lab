#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int status;

    printf("begin parent\n");
    pid = fork();

    if (pid == -1) {
        return EXIT_FAILURE;
    }
    
    if (pid == 0) {
        printf("begin child 1\n");
        sleep(2);
        printf("end child 1\n");
        return 1;

    }

    pid = fork();

    if (pid == 0) {
        printf("begin child 2\n");
        sleep(6);
        printf("end child 2\n");
        return 2;
    }
        
    sleep(4);
    printf("begin wait 1\n");
    wait(&status);
    printf("end wait 1; %d, %d \n", status, WEXITSTATUS(status));

    sleep(4);
    printf("begin wait 2\n");
    wait(&status);
    printf("end wait 2; %d, %d\n", status, WEXITSTATUS(status));

    sleep(2);
    printf("end parent\n");

    return EXIT_SUCCESS;
}
