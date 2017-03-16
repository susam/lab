#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>


void handler(int sig)
{
    printf("Received signal %d\n", sig); 
    sleep(4);
    printf("Handled signal %d\n", sig); 
}


int main(int argc, char **argv)
{
    struct sigaction sa;
    int block_term;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s 0|1\n", argv[0]);
        return EXIT_FAILURE;
    }

    block_term = atoi(argv[1]);

    sa.sa_handler = handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    if (block_term) {
        printf("Blocking SIGTERM in handler\n");
        sigaddset(&sa.sa_mask, SIGTERM);
    }

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
