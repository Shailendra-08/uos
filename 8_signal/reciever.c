#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

void signal_handler(int signal_num) {
    printf("Signal %d received from PID %d.\n", signal_num, getpid());
}

int main() {
    pid_t pid;
    pid = getpid(); // Get the PID of the current process

    printf("Receiver process started. PID: %d\n", pid);

    // Register signal handler for SIGUSR1
    signal(SIGUSR1, signal_handler);

    printf("Receiver process waiting for signals...\n");

    // Keep running until terminated
    while(1) {
        sleep(1);
    }

    return 0;
}
