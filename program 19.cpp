#include <stdio.h>
#include <pthread.h>


pthread_mutex_t mutex;

int counter = 0;


void *increment(void *args) {
    for (int i = 0; i < 100000; i++) {
     
        pthread_mutex_lock(&mutex);

      
        counter++;

      
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}


void *decrement(void *args) {
    for (int i = 0; i < 100000; i++) {
        
        pthread_mutex_lock(&mutex);

       
        counter--;

       
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    
    pthread_mutex_init(&mutex, NULL);

  
    if (pthread_create(&thread1, NULL, increment, NULL) != 0) {
        perror("Thread 1 creation failed");
        return 1;
    }
    if (pthread_create(&thread2, NULL, decrement, NULL) != 0) {
        perror("Thread 2 creation failed");
        return 1;
    }

   
    if (pthread_join(thread1, NULL) != 0) {
        perror("Thread 1 join failed");
        return 1;
    }
    if (pthread_join(thread2, NULL) != 0) {
        perror("Thread 2 join failed");
        return 1;
    }

    
    pthread_mutex_destroy(&mutex);

  
    printf("Counter value: %d\n", counter);

    return 0;
}