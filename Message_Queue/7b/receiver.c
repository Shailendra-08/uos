#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>


#define KEY 12345

struct message {
    long mtype;
    char mtext[100];
};

int main() {
    int msgid;
    struct message msg;

   

    // Get the message queue
    msgid = msgget(KEY, 0666 | IPC_CREAT);

    // Receiving message
    msgrcv(msgid, &msg, sizeof(msg), 1, 0);
    printf("Process 2: Received message - \"%s\"\n", msg.mtext);

    // Sending reply
    msg.mtype = 2;
    sprintf(msg.mtext, "Loud and Clear");
    msgsnd(msgid, &msg, sizeof(msg), 0);
    printf("Process 2: Sent reply - \"%s\"\n", msg.mtext);

    // Receiving acknowledgment
    msgrcv(msgid, &msg, sizeof(msg), 1, 0);
    printf("Process 2: Received acknowledgment - \"%s\"\n", msg.mtext);

    return 0;
}
