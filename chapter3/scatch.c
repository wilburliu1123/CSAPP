#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

/* global variables */
#define MAX_RESULTS 100
int* start_index;
int length;
int section_size;
// array of numbers to search
int* data;

// Number to be found
int target;

// Array of indices of target number
int results[MAX_RESULTS];

// Number of results we have so far
int num_results = 0;

// Used for synchronization
pthread_mutex_t find_number;
sem_t semaphore;

// All the threads (an array)
pthread_t* threads;

// The function that each thread will run to look for the target value in the array
// the argument provided is a pointer to the array
// the where this thread should start looking for the target
// this can be either the index or the address.
// Each thread will look at a max of section_size elements.
void* DoSearch(void* start_address) {
    // int idx = *(int *)start_address; 
        sem_wait(&semaphore);
    
    int i;
    int index = *(int *) start_address; // start_address is an index in our data array
    int size = index + section_size;
    printf("entered in starting idx with %d...\n", index);
    
    for (i = index; i < size && i < length; i++) {
        if (data[i] == target) {
            printf("target found at thread id: %d at index: %d, target is : %d\n", pthread_self(), i, data[i]);
            results[num_results++] = i;
        } else {
            printf("target not found at idx: %d\n", i);
        }
    }
    sem_post(&semaphore);
    return NULL;
}

// Creates all the thread and starts them running
// makes sure the thread IDs are stored in the global threads array

void MakeThreads(int num_threads) {
    pthread_t threads_id[num_threads];
    threads = threads_id;
    if (length % num_threads != 0) {
        section_size = length / num_threads + 1;
        printf("given number of thread cannot evenly divide the input array, sections size is: %d\n", section_size);
    } else {
        section_size = length / num_threads;
    }
    printf("section size is: %d\n", section_size);
    printf("Start creating threads...\n");
    int i;
    for (i = 0; i < num_threads; i++) {
        printf("start thread %d\n", i);
        // send disjoint portion of the array to each thread
        pthread_create(&threads_id[i], NULL, DoSearch, &start_index[i*section_size]);
    }
    for (i = 0; i < num_threads; i++) {
        pthread_join(threads_id[i], NULL);
    }
    printf("Threads have joined\n");
}

int main(int argc, char **argv) {
    if (argc < 5) {
        printf("Please enter the command with: <filename> <number to search for> <number of threads> <num lines>\n");
        exit(1);
    }
    sem_init(&semaphore, 0, 1);
    FILE *fp;
    // first argument is our file path
    fp = fopen(argv[1], "r");
    // second argument is our target
    target = atoi(argv[2]);
    printf("our target is %d\n", target);
    // third argument is number of threads we will create
    int num_of_threads = atoi(argv[3]);
    printf("number of threads is: %d\n", num_of_threads);
    // fourth number is the number of lines this file has
    length = atoi(argv[4]);
    printf("length is %d\n", length);
    int dataArray[length];
    int idxArray[length];
    data = dataArray;
    start_index = idxArray;
    char str[60];
    // initialize length of our data
    int i;
    if (fp == NULL) {
        perror("Error opening file");
        return(-1);
    }
    for (i = 0; i < length; i++) {
        if (fgets(str, 60, fp) != NULL) {
            dataArray[i] = atoi(str);
            idxArray[i] = i;
            // printf("input str is: %s\n",str);
            printf("%d\n", dataArray[i]);
        }
    }
    // create threads
    MakeThreads(num_of_threads);
    printf("input array:\n[");
    for (i = 0; i < length; i++) {
        printf("%d, ", dataArray[i]);
    }
    printf("\n");
    for (i = 0; i < num_results; i++) {
        printf("line number %d has our target: %d \n", results[i], target);
    }
    fclose(fp);
    return(0);
}