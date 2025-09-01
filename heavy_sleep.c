#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handle_sigterm(int sig) {
    printf("Recibí SIGTERM (%d) y lo voy a IGNORAR\n", sig);
}

int main(int argc, char const *argv[]) {
    signal(SIGTERM, handle_sigterm);

    int sleeping_time = 3;
    if (argc > 1){
        sleeping_time = atoi(argv[1]);
    }

    if (sleeping_time == 0){
        sleeping_time = 3;
    }

    printf("Now sleeping for %d seconds...\n",sleeping_time);
    for (int i = 0; i < sleeping_time; i++) {
        printf("zzz...\n");
        sleep(1);
    }
    printf("I got to sleep for %d seconds!\n", sleeping_time);
    return 0;
}