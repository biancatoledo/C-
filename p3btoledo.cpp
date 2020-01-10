/* bianca toledo
operating systems
project 3
*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <iostream>
#include <cstdlib>

using namespace std;
 
#define SIZE 10
#define PRODUCER_LOOPS 2
 
typedef int buffer_t;
buffer_t buffer[SIZE];
int buffer_index;
 
pthread_mutex_t buffer_mutex;
sem_t full_sem;  /* when 0, buffer is full */
sem_t empty_sem;
 
 
void insertbuffer(buffer_t value) {
    if (buffer_index < SIZE) {
        buffer[buffer_index++] = value;
    } else {
        printf("Buffer overflow\n");
    }
}
 
buffer_t dequeuebuffer(int value) {
    if (buffer_index > 0) {
        return buffer[--buffer_index];
    } else {
        printf("Buffer underflow\n");
    }
    return 0;
}
 
 
void *producer(void *thread_n) {
    int thread_numb = *(int *)thread_n;
    buffer_t value;
    int i=0;
    while (i++ < PRODUCER_LOOPS) {
        sleep(rand() % 10);
        value = rand() % 100;
        sem_wait(&full_sem); 
        pthread_mutex_lock(&buffer_mutex); /* blocks  critical section */
        insertbuffer(value);
        pthread_mutex_unlock(&buffer_mutex);
        sem_post(&empty_sem); 
        printf("Producer %d produced  %d in buffer %d\n", thread_numb, value, buffer_index);
    }
    pthread_exit(0);
}
 
void *consumer(void *thread_n) {
    int thread_numb = *(int *)thread_n;
    buffer_t value;
    int i=0;
    while (i++ < PRODUCER_LOOPS) {
        sem_wait(&empty_sem);
        pthread_mutex_lock(&buffer_mutex);
        value = dequeuebuffer(value);
        pthread_mutex_unlock(&buffer_mutex);
        sem_post(&full_sem); 
        printf("Consumer %d consumed %d from buffer %d\n", thread_numb, value, buffer_index);
   }
    pthread_exit(0);
}
 
int main(int argc, char **argv) {
    buffer_index = 0;
    int mainZzz;
    int NUMB_THREADS, CONS_THREADS;

   pthread_mutex_init(&buffer_mutex, NULL);
    sem_init(&full_sem, // sem_t *sem
             0, SIZE);
    sem_init(&empty_sem, 0, 0);
    // full_sem is initialized to buffer size

	cout << "Enter the number of seconds for the main() function to sleep: ";
	cin >> mainZzz;
	cout << "\nEnter number of Producer threads: ";
	cin >> NUMB_THREADS;
	cout << "\nEnter the number of consumer threads: ";
	cin >> CONS_THREADS;
	cout << endl;

    pthread_t thread[NUMB_THREADS];
    int thread_numb[NUMB_THREADS];
    int i;
    for (i = 0; i < NUMB_THREADS; ) {
        thread_numb[i] = i;
        pthread_create(thread + i, NULL, producer, thread_numb + i);
        i++;
   }

    for (i = 0; i < CONS_THREADS;) {
        thread_numb[i] = i;
        pthread_create(&thread[i], NULL, consumer, &thread_numb[i]);
        i++;
    }
 
    for (i = 0; i < NUMB_THREADS; i++)
        pthread_join(thread[i], NULL);
 
    pthread_mutex_destroy(&buffer_mutex);
    sem_destroy(&full_sem);
    sem_destroy(&empty_sem);
    sleep(mainZzz); 
    return 0;
}
