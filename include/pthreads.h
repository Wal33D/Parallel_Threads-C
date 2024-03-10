#ifndef PTHREAD_H
#define PTHREAD_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

extern volatile int running_threads; // Declaration of global variable

extern int numOfElements; // Declaration of global variable

struct Results
{ //Struct to hold the statistical results

	int min;
	int max;
	int average;

} Results;


extern struct Results Results; // Declaration of global struct

// Function declarations
void *findMin(void *array_ptr);
void *findMax(void *array_ptr);
void *findAverage(void *array_ptr);
int getArrayInput(int n, int *array_ptr);
void joinThreads(int numberOfThreads);
void createThreads(int *array_ptr);

#endif // PTHREAD_H
