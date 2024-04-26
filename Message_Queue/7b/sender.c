#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include<string.h>

#define KEY 12345
struct message {
    long mtype;
    char mtext[100];
};

int main() {
    
    int msgid;
    struct message msg;


    // Create a message queue
    msgid = msgget(KEY, 0666 | IPC_CREAT);

    // Sending message
    msg.mtype = 1;
    strcpy(msg.mtext, "Are you hearing me?");
    msgsnd(msgid, &msg, sizeof(msg), 0);
    printf("Process 1: Sent message - \"%s\"\n", msg.mtext);

    // Receiving reply
    msgrcv(msgid, &msg, sizeof(msg), 2, 0);
    printf("Process 2: Received reply - \"%s\"\n", msg.mtext);

    // Sending acknowledgment
    msg.mtype = 1;
    strcpy(msg.mtext, "I can hear you too");
    msgsnd(msgid, &msg, sizeof(msg), 0);
    printf("Process 1: Sent acknowledgment - \"%s\"\n", msg.mtext);

    // Clean up
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}

