// Write a program for alarm clock using alarm and signal system call.

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void handler() {
    printf("Alarm clock\n");
    signal(SIGALRM, handler);
    exit(0);
}
int main(){
    signal(SIGALRM, handler);
    printf("Setting alam for 5 sec\n");
    alarm(5);
    for(;;);
    return 0;
}