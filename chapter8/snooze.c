#include "csapp.h"

void sigint_handler(int sig) {/* SIGINT handler */
    printf("CTRL+C\n");
    sleep(3);
    printf("Slept for 3 secs.\n");
    exit(0);
}

int main() {
    /* Install the SIGINT handler */
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        unix_error("signal error");
    }
    pause(); /* wait for the receipt of a signal */

    return 0;
}