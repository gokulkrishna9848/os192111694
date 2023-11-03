#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct message {
    long mtype;
    char mtext[100];
};

int main() {
    
    key_t key = ftok("/tmp", 'A');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

   
    int msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    struct message msg;
    msg.mtype = 1; 

    printf("Enter a message to send: ");
    fgets(msg.mtext, sizeof(msg.mtext), stdin);

  
    if (msgsnd(msgid, &msg, sizeof(msg.mtext), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }

    printf("Message sent: %s", msg.mtext);

    return 0;
}