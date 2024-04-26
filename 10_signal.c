#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>


void signal_handler(){
    printf("Timeout has Occured");
    exit(0);

}

int main(){
    int a;
    printf("Enter the Number:");
    alarm(10);
    signal(SIGALRM,signal_handler);
    scanf("%d",&a);
    printf("You have Entered: %d,\n",a);
    return 0;

}