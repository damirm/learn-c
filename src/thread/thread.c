#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 4
#define ERR_CREATE_THREAD -11
#define ERR_JOIN_THREAD -12

void* handle() {
    pthread_t t = pthread_self();
    unsigned id = (unsigned) t;
    printf("thread id: %d\n", id);
    return NULL;
}

int main() {
    int i;
    int status;
    pthread_t threads[NUM_THREADS];

    // Create threads.
    for (i = 0; i < NUM_THREADS; i++) {
        status = pthread_create(&threads[i], NULL, handle, NULL);
        if (status != 0) {
            printf("create thread failed with status %d", status);
            return ERR_CREATE_THREAD;
        }
    }

    // Join threads.
    for (i = 0; i < NUM_THREADS; i++) {
        status = pthread_join(threads[i], NULL);
        if (status != 0) {
            printf("join thread failed with status %d", status);
            return ERR_JOIN_THREAD;
        }
    }

    return 0;
}
