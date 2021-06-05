  #include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int mails = 0;
pthread_mutex_t mutex;

void* routine() {
    // for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);
        usleep(1 * 1000000);
        mails++;
        pthread_mutex_unlock(&mutex);
    // }
    return (NULL);
}

int main(int argc, char* argv[]) {
    pthread_t th[8];
    int i;
    pthread_mutex_init(&mutex, NULL);
    for (i = 0; i < 8; i++) {
        if (pthread_create(th + i, NULL, &routine, NULL) != 0) {
            perror("Failed to create thread");
            return 1;
        }
        printf("Thread %d has started\n", i);
    }
    for (i = 0; i < 8; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            return 2;
        }
        printf("Thread %d has finished execution\n", i);
    }
    pthread_mutex_destroy(&mutex);
    printf("Number of mails: %d\n", mails);
    return 0;
}