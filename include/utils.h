#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>

// Declare the structure Results
struct Results {
    int min;
    int max;
    int average;
};

// Declare the variable Results as an external variable to be defined in one .c file
extern struct Results Results;

extern volatile int running_threads; // Declaration of global variable
extern int numOfElements; // Declaration of global variable

// Function declarations
void *findMin(void *array_ptr);
void *findMax(void *array_ptr);
void *findAverage(void *array_ptr);
int getArrayInput(int n, int *array_ptr);
void joinThreads(int numberOfThreads);
void createThreads(int *array_ptr);

#endif // UTILS_H
