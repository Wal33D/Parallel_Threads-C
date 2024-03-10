#include <pthread.h>
#include "utils.h"

// Macro for error handling in thread creation and joining, adapted from the pthread_create man page
#define handle_error_en(en, msg) \
        do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

// Global variable to track the number of running threads
volatile int running_threads = 0;

// Array to hold thread identifiers for our three worker threads
pthread_t thread[3];

// Global variable to store the total number of elements input by the user
int numOfElements;

// Global instance of the Results structure to hold computation outcomes
struct Results Results;

/**
 * Waits for and joins the specified number of worker threads.
 * @param numberOfThreads The number of threads to join.
 */
void joinThreads(int numberOfThreads) {
    int s; // Variable to capture pthread_join return status

    while (numberOfThreads >= 0) { // Loop to join threads
        s = pthread_join(thread[numberOfThreads], NULL);

        if (s != 0) {
            handle_error_en(s, "pthread_join");
        }
        numberOfThreads--;
    }
}

/**
 * Creates three threads to compute the minimum, maximum, and average values.
 * @param array_ptr Pointer to the array of integers.
 */
void createThreads(int *array_ptr)
{
	int s; // Variable to capture pthread_create return status

	// Creating a thread for finding the minimum value
	s = pthread_create(&thread[0], NULL, findMin, (void *)array_ptr);
	if (s != 0) {
		handle_error_en(s, "pthread_create");
	}
	running_threads += 1;

	// Creating a thread for finding the maximum value
	s = pthread_create(&thread[1], NULL, findMax, (void *)array_ptr);
	if (s != 0) {
		handle_error_en(s, "pthread_create");
	}
	running_threads += 1;

	// Creating a thread for calculating the average
	s = pthread_create(&thread[2], NULL, findAverage, (void *)array_ptr);
	if (s != 0) {
		handle_error_en(s, "pthread_create");
	}
	running_threads += 1;
}

/**
 * Main function to initialize data, create threads, and report results.
 */
int main()
{
	int n = 1; // Initial size of the dynamic array

	// Allocating memory for the dynamic array
	int *array_ptr = malloc(n * sizeof(int)); 

	// Retrieving the number of elements from the user and storing them in the dynamic array
	numOfElements = getArrayInput(n, array_ptr);

	// Creating threads to compute statistical values
	createThreads(array_ptr);

	// Waiting for all threads to complete their tasks
	while (running_threads > 0) {
		sleep(1);
	}

	// Joining all threads
	joinThreads(2);

	// Reporting the computed results to the user
	printf("\nThe average is %d\nThe maximum is %d\nThe minimum is %d\n", Results.average, Results.max, Results.min);

	return 0;
}
