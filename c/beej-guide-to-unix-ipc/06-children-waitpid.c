#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid1, pid2;
    int status;

    printf("begin parent\n");
    pid1 = fork();

    if (pid1 == -1) {
        return EXIT_FAILURE;
    }
    
    if (pid1 == 0) {
        printf("begin child 1\n");
        sleep(2);
        printf("end child 1\n");
        return 1;

    }

    pid2 = fork();

    if (pid2 == 0) {
        printf("begin child 2\n");
        sleep(6);
        printf("end child 2\n");
        return 2;
    }
        
    printf("begin wait 2\n");
    waitpid(pid2, &status, 0);
    printf("end wait 2; exit status: %d\n", WEXITSTATUS(status));

    printf("begin wait 1\n");
    waitpid(pid1, &status, 0);
    printf("end wait 1; exit status: %d\n", WEXITSTATUS(status));

    printf("end parent\n");

    return EXIT_SUCCESS;
}
