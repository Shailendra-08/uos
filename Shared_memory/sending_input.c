#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/wait.h>
#include<sys/shm.h>

#define KEY 1234
#define SHM_SIZE 1024

int main(){

    int shmid;
    char *shm;


    // 1) create shared memory segment

    shmid = shmget(KEY,SHM_SIZE, IPC_CREAT | 0666);
    if(shmid == -1){
        perror("Shared memory cannot be created\n");
        exit(1);
    }


    // 2) Attach shared memory  segment

    shm = (char *)shmat(shmid,NULL,0);
    if(shm == (char *) -1){
        perror("Cannot be attached to the Shared Memory Segment\n");
        exit(1);
    }

    int pid_input = fork();

    if(pid_input == -1){
        perror("Cannot create a process\n");
        exit(0);
    }else if(pid_input == 0){
        printf("Enter the content to be placed in the shared memory segmet\n");
        fgets(shm,SHM_SIZE,stdin);
        exit(0);
    }


    // 3) waiting for input process to complete
    waitpid(pid_input,NULL,0);

    // 4) fork for a child process to Receiving the message
    int pid_output = fork();

    if(pid_output == -1){
        perror("Error in creating fork() \n");
        exit(0);
    }
    else if(pid_output == 0){
        printf("Recieved -- > %s",shm);
        exit(0);
    }


    // 5) waitpid for the output to be execute completely

    waitpid(pid_output,NULL,0);

    // 6) Detached the memory segment 

    if(shmdt(shm) == -1){
        perror("shared memory detached\n");
        exit(1);
    }


    // destroy the Shared memory

    if(shmctl(shmid, IPC_RMID,NULL) == -1){
        perror("Exit");
        exit(1);
    }

    return 0;
}