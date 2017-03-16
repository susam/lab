#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    printf("begin parent\n");

    /* Child 1 */
    pid = fork();

    if (pid == -1) {
        perror("fork()");
        return EXIT_FAILURE;
    } else if (pid == 0) {
        printf("child1 %jd begin\n", (intmax_t) getpid());
        sleep(2);
        printf("child1 %jd end\n", (intmax_t) getpid());
        return 0;
    }

    printf("parent %jd forked child1 %jd\n",
           (intmax_t) getpid(), (intmax_t) pid);

    /* Child 2 */
    pid = fork();

    if (pid == -1) {
        perror("fork()");
        return EXIT_FAILURE;
    } else if (pid == 0) {
        printf("child2 %jd begin\n", (intmax_t) getpid());
        sleep(4);
        printf("child2 %jd end\n", (intmax_t) getpid());
        return 0;
    }

    printf("parent %jd forked child2 %jd\n",
           (intmax_t) getpid(), (intmax_t) pid);

    do {

        printf("waiting ...\n");
        pid = wait(NULL);
        printf("wait() returned: pid: %jd; errno: %d\n", (intmax_t) pid, errno);

    } while (errno != ECHILD);

    perror("wait()");
    printf("exiting ...\n");

    return EXIT_SUCCESS;
}
