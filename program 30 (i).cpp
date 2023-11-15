#include <stdio.h>
#include <pthread.h>

void* thread_function(void* arg) {
    int thread_id = ((int)arg);
    printf("Hello from Thread %d\n", thread_id);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread_id;
    int arg = 1;
    
    if (pthread_create(&thread_id, NULL, thread_function, &arg) == 0) {
        printf("Thread created successfully.\n");
    } else {
        printf("Failed to create the thread.\n");
    }

    pthread_join(thread_id, NULL); // Wait for the thread to finish

    printf("Main thread exiting.\n");
    return 0;
}