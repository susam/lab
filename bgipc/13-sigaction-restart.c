#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>


void handler(int sig)
{
    printf("Received signal %d\n", sig); 
}

int main(int argc, char **argv)
{
    struct sigaction sa;
    char s[200];
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
        printf("Setting SA_RESTART flag ...\n");
        sa.sa_flags = SA_RESTART;
    }

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction()");
        return EXIT_FAILURE;
    }

    printf("Enter some input and press ^C: ");
    if (fgets(s, sizeof s, stdin) == NULL) {
        perror("fgets()");
    } else {
        printf("You entered: %s\n", s);
    }

    return EXIT_SUCCESS;
}
