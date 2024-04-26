#include<stdio.h>
#include<stdlib.h>
#include<sys/msg.h>
#include<sys/wait.h>
#include<string.h>
#include<sys/ipc.h>

#define KEY 215
#define SIZE 128

typedef struct msgbuff  
{
    long mtype;
    char content[SIZE];
}message_buffer;


int main(){

    int msgid;
    int buffer_length;

    message_buffer receiver_buffer;

    if(msgid = msgget(KEY,0666) < 0){
        perror("Error");
        exit(1);
    }

    if(msgrcv(msgid,&receiver_buffer,SIZE,1,0) < 0){
        perror("Error");
        exit(1);
    }

    if ((msgid = msgget(KEY, 0666)) < 0) {
        perror("msgget");
        exit(1);
    }


    printf("%s\n", receiver_buffer.content);



}