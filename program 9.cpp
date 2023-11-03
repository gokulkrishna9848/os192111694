#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHM_SIZE 1024  

int main() {
    int shmid;        
    key_t key = 1234;  
    if ((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

   
    char *shm = shmat(shmid, NULL, 0);
    if (shm == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    
    strcpy(shm, "Hello, shared memory!");

   
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {  
        char *child_data = shmat(shmid, NULL, 0);
        if (child_data == (char *)-1) {
            perror("shmat");
            exit(1);
        }

        printf("Child process reads: %s\n", child_data);

       
        shmdt(child_data);
    } else {  
        wait(NULL);

        printf("Parent process reads: %s\n", shm);

        
        shmdt(shm);
        
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}
