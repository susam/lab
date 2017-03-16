#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>


void handler(int sig)
{
    int left;
    printf("Received signal %d\n", sig); 
    left = sleep(6);
    if (left > 0) {
        printf("sleep was interrupted with %d seconds left\n", left);
    } else {
        printf("sleep completed\n");
    }
    printf("Handled signal %d\n", sig); 
}


int main()
{
    struct sigaction sa;

    sa.sa_handler = handler;
    sa.sa_flags = SA_NODEFER;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction()");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < 100; i++) {
        printf("%d\n", i);
        sleep(1);
    }

    return EXIT_SUCCESS;
}
