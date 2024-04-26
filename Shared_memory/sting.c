#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>


#define SIZE 1024

#define KEY 1234

int main(){
    int shmid;
    char *shm;

    char const message[] = "Data Dictionary";

    // Create
    shmid = shmget(KEY,SIZE,IPC_CREAT|0666);

    if(shmid == -1){
        perror("Error creating shared Memory Segment");
        exit(1);
    }

   
    shm = shmat(shmid, NULL, 0);
    if (shm == (char *) -1) {
        perror("shmat");
        exit(1);
    }


    strcpy(shm,message);
    printf("Data stored in shared memory\n");

    printf("Creating process\n");

    int pid = fork();

    if(pid < 0){
        perror("Fork Failed");
        exit(1);
    }
    else if(pid == 0){
        printf("Child Process created with ID: %d\n",getpid());
        printf("Child Process modifying shared resource\n");
        strcat(shm,"- modified by child process");
        printf("Modified Data--> %s\n",shm);
        exit(0);
    }
    else{
        printf("Parent Process with ID: %d\n",getpid());
        wait(NULL);
        printf("Parent process Accessing shared resource\n");
        printf("Shared Resource --> %s\n",shm);
    }

    printf("detaching shared memory segment\n");

    if(shmdt(shm) == -1){
        perror("Error");
        exit(1);
    }
    
    printf("deleting shared memory segment");
    if(shmctl(shmid,IPC_RMID,NULL)==-1){
        perror("Error");
        exit(1);
    }
    return 0;

}