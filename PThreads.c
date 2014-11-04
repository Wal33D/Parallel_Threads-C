/*************************************************
* Course: CS 4540 – Fall 2014
* Assignment <3>
* Name: <Waleed Gudah>
* E-mail: <waleed.h.gudah@wmich.edu>
* Submitted: <11/3/14>
/*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> 
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <syscall.h>

pthread_t thread[4];
pthread_mutex_t lock;

struct Results{
	
	int min;
	int max;
	int average;

}Results;

int numOfElements;

void *findMin(void *array_ptr){
	
	int i;
	int *elements = (int*)array_ptr;
	int min = elements[0];

	for(i = 0; i < numOfElements; i++){
		
		if(elements[i] < min){
		
			min = elements[i];
		}
	}
	
	Results.min = min;

}

void *findMax(void *array_ptr){
	
	int i;

	int max = 0;

	int *elements = (int*)array_ptr;

	for(i = 0; i < numOfElements; i++){
		
		if(elements[i] > max){
		
			max = elements[i];
		}
	}
	
	Results.max = max;

}

void *findAverage(void *array_ptr){
	
	int i;

	int average = 0;

	int *elements = (int*)array_ptr;

	for(i = 0; i < numOfElements; i++){
		
			average += elements[i];

	}
	
	Results.average = average/numOfElements;

}

/*This method accepts a int n(initial size of array) and
 pointer to an array and returns # of elements in the array*/

int getArrayInput(int n, int *array_ptr){
		
		int input;//Store user input 
		int numberOfElements = 0;//Number of Integers inputed

    	printf("Creating Dynamic Array...\n-\n");

		for(;;){  //infinite loop

    		printf("Enter a positive value:\nNegative Number to Stop\n-\n");
   
    		scanf("%d",&input);//Get Int from console, store at address of input

    		if (input >= 0){ 

       		 	if (numberOfElements == n){

          	  	  n += 1; //Make room for the current input
            		
          		  array_ptr = realloc(array_ptr, n * sizeof(int));//realloc array and set pointer
            
       			 }

        		array_ptr[numberOfElements++] = input;//Store input at next empty element
    
    		}else{
        
       		 printf("\nNumber of Integers: %d\n", numberOfElements);
       
       		 break;

   				 }

			}

	return numberOfElements;
	
		}

int main(){

	int n = 1; // Initial Array Size
	int *array_ptr = malloc(n * sizeof(int));//Initialize array pointer
		
		numOfElements = getArrayInput(n, array_ptr);
		
		 pthread_create(&thread[0], NULL, findMin, (void *)array_ptr);
		 wait(10000);
		 pthread_join(thread[0], NULL);
		// findMin(n, array_ptr);

		 pthread_create(&thread[1], NULL, findMax,  (void *)array_ptr);
		 wait(10000);
		 pthread_join(thread[1], NULL);
		// findMax(n, array_ptr);
		
		 pthread_create(&thread[2], NULL, findAverage, (void *)array_ptr);
		 wait(10000);	
		 pthread_join(thread[2], NULL);	
		 // findAverage(n, array_ptr);
 		
 		
 		
		printf("\nAverage: %d\nMax: %d\nMin: %d\n",Results.average, Results.max, Results.min);

}