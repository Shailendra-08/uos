#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/msg.h>
#include<string.h>

#define SIZE 128
#define KEY 215

typedef struct msgbuf
{
    long mtype;
    char content[SIZE];
}message_buffer;


int main(){

    int msgid;
    int buffer_length;
    message_buffer sender_buffer;

    if(msgid=msgget(KEY, IPC_CREAT | 0666) == -1){
        perror("Error");
        exit(0);
    }


    sender_buffer.mtype =1;
    strcpy(sender_buffer.content,"Greeting from Shailendra Mahadule");
    buffer_length = strlen(sender_buffer.content)+1;


    if(msgsnd(msgid,&sender_buffer,buffer_length,IPC_NOWAIT) < 0){
        perror("Error in sending data\n");
        exit(1);
    }else{
        printf("Message: \"%s\" sent\n",sender_buffer.content);
    }

    exit(0);
}
