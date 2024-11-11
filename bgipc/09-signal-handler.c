#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>


void handler(int sig)
{
    printf("Received signal %d\n", sig); 
}


int main()
{
    if (signal(SIGTERM, handler) == SIG_ERR) {
        perror("signal()");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < 100; i++) {
        printf("%d\n", i);
        sleep(1);
    }
}
