#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

extern volatile int running_threads; // Declaration of global variable

extern int numOfElements; // Declaration of global variable

extern struct Results Results;

// Function declarations
void *findMin(void *array_ptr);
void *findMax(void *array_ptr);
void *findAverage(void *array_ptr);
int getArrayInput(int n, int *array_ptr);
void joinThreads(int numberOfThreads);
void createThreads(int *array_ptr);

#endif // UTILS_H
