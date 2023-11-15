#include <stdio.h>
#include <pthread.h>

void* thread_function(void* arg) {
    printf("Thread is running.\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t thread_id;
    
    if (pthread_create(&thread_id, NULL, thread_function, NULL) == 0) {
        printf("Thread created successfully.\n");
    } else {
        printf("Failed to create the thread.\n");
    }

    pthread_join(thread_id, NULL);

    printf("Main thread exiting.\n");
return 0;
}