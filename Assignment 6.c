/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t lock; // Mutex lock
int shared_data = 0;  // Shared variable

void* write_thread(void* arg) {
    for (int i = 1; i <= 5; i++) {
        pthread_mutex_lock(&lock); // Lock the mutex
        shared_data = i;          // Write to shared variable
        printf("Thread_1 wrote: %d\n", shared_data);
        pthread_mutex_unlock(&lock); // Unlock the mutex
        sleep(1); // Simulate processing time
    }
    return NULL;
}

void* read_thread(void* arg) {
    for (int i = 1; i <= 5; i++) {
        pthread_mutex_lock(&lock); // Lock the mutex
        printf("Thread_2 read: %d\n", shared_data); // Read the shared variable
        pthread_mutex_unlock(&lock); // Unlock the mutex
        sleep(1); // Simulate processing time
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Initialize the mutex
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("Mutex initialization failed\n");
        return 1;
    }

    // Create threads
    pthread_create(&thread1, NULL, write_thread, NULL);
    pthread_create(&thread2, NULL, read_thread, NULL);

    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroy the mutex
    pthread_mutex_destroy(&lock);

    return 0;
}
