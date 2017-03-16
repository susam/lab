#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int fds[2];
    pid_t cpid;

    if (pipe(fds) == -1) {
        perror("pipe()");
        return EXIT_FAILURE;
    }

    if ((cpid = fork()) == -1) {
        perror("fork()");
        return EXIT_FAILURE;
    } else if (cpid != 0) {
        // parent
        close(0);
        close(fds[1]);
        dup(fds[0]);
        execlp("wc", "wc", "-l", NULL);
    } else {
        // child
        close(1);
        close(fds[0]);
        dup(fds[1]);
        execlp("ls", "ls", NULL);
    }

    // If we interchange, the code blocks for parent and child, i.e. if
    // the parent runs 'ls' and the child runs 'wc -l', then the parent
    // would exit first, shell prompt would return and then the child
    // would generate its output and return.
    //
    // With the current code, the parent is forced to exit after the
    // child exits.

    return EXIT_SUCCESS;
}
