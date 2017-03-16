#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int ret;
    int status;

    pid = fork();

    switch (pid) {
        case -1:
            perror("fork");
            return 1;
        
        case 0:
            printf("child: fork(): 0\n");
            printf("child: PID: %d\n", getpid());
            printf("child: PPID: %d\n", getppid());
            return 2;

        default:
            printf("parent: fork(): %d\n", pid);
            printf("parent: PID: %d\n", getpid());
            printf("parent: PPID: %d\n", getppid());
            printf("parent: waiting ...\n");
            ret = wait(&status);
            printf("parent: wait(): %d\n", ret);
            printf("parent: status: %d\n", status);
            printf("parent: WIFEXITED(): %d\n", WIFEXITED(status));
            printf("parent: WEXITSTATUS(): %d\n", WEXITSTATUS(status));
    }
}
