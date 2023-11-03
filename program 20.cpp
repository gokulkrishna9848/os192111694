#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


int sharedData = 0;
int readerCount = 0;


sem_t mutex;          
sem_t writeMutex;    

void *reader(void *arg) {
    while (1) {
        sem_wait(&mutex); 
        readerCount++;
        if (readerCount == 1) {
            sem_wait(&writeMutex); 
        }
        sem_post(&mutex); 

      
        printf("Reader %ld is reading: %d\n", (long)arg, sharedData);
        usleep(100000); 

        sem_wait(&mutex); 
        readerCount--;
        if (readerCount == 0) {
            sem_post(&writeMutex); 
        }
        sem_post(&mutex); 

        usleep(500000); 
    }
    return NULL;
}

void *writer(void *arg) {
    while (1) {
        sem_wait(&writeMutex);

       
        sharedData++;
        printf("Writer %ld is writing: %d\n", (long)arg, sharedData);
        usleep(100000); 

        sem_post(&writeMutex);

        usleep(500000); 
    }
    return NULL;
}

int main() {
    pthread_t readers[3];  
    pthread_t writers[2]; 

   
    sem_init(&mutex, 0, 1);
    sem_init(&writeMutex, 0, 1);


    for (long i = 0; i < 3; i++) {
        pthread_create(&readers[i], NULL, reader, (void *)i);
    }

   
    for (long i = 0; i < 2; i++) {
        pthread_create(&writers[i], NULL, writer, (void *)i);
    }

   
    pthread_join(readers[0], NULL);
    pthread_join(writers[0], NULL);

  
    sem_destroy(&mutex);
    sem_destroy(&writeMutex);

    return 0;
}