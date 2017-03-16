#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#define UNUSED(x) (void) (x)

#ifdef SIGATOMIC
volatile sig_atomic_t run;
#elif VOLATILE
volatile int run;
#else
int run;
#endif

void sigusr1_handler(int sig)
{
    UNUSED(sig);
    write(1, "signalled\n", 10);
    run = 0;
}

int main()
{
    struct sigaction sa;

    sa.sa_handler = sigusr1_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction()");
        return EXIT_FAILURE;
    }

    run = 1;
    while (run)
        ;

    printf("Exiting ...\n");
    return 0;
}
