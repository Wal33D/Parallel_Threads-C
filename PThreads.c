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
#include <errno.h>

/*Error handling for pthread_create and pthread_join*/
#define handle_error_en(en, msg) \
        do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error(msg) \
        do { perror(msg); exit(EXIT_FAILURE); } while (0)
/* # of running threads */
volatile int running_threads = 0;

pthread_t thread[3];
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

	running_threads -= 1;
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

	running_threads -= 1;
}

void *findAverage(void *array_ptr){
	
	int i;

	int average = 0;

	int *elements = (int*)array_ptr;

	for(i = 0; i < numOfElements; i++){
		
			average += elements[i];

	}
	
	Results.average = average/numOfElements;

	running_threads -= 1;
}

/* This method accepts a int n(initial size of array) and
   pointer to an array and returns # of elements in the array
*/

int getArrayInput(int n, int *array_ptr){
		
		int input;/*Store user input */
		int numberOfElements = 0;/*Number of Integers inputed*/

    	printf("Creating Dynamic Array...\n-\n");

		for(;;){  /*infinite loop*/

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

/* The main function initialiazes the dynamic array as well
   as allocating space for it, Then it creates, using pthread_create,
   3 Threads 1 to calculate the min, the max, and the average.
   We then wait until each thread completes its task and then
   join the 3 threads and prompt the user with the results
 */

int main(){

	int s, n = 1; /* Initial Array Size*/
	int *array_ptr = malloc(n * sizeof(int));/*Initialize array pointer*/
		
		 /*get an n sized array of elements from the user and save count*/
		 numOfElements = getArrayInput(n, array_ptr);
		
		 /*Create a thread and passing in the function to begin 
		 exectuing as well as that functions required arguments*/ 
		 s = pthread_create(&thread[0], NULL, findMin, (void *)array_ptr);

		 if (s != 0){

			handle_error_en(s, "pthread_create");
		 
		 }
		 	running_threads += 1;

		 /*Create a thread and passing in the function to begin 
		 exectuing as well as that functions required arguments*/ 
		 s = pthread_create(&thread[1], NULL, findMax, (void *)array_ptr);

		 if (s != 0){
        
            handle_error_en(s, "pthread_create");
       	
       	 }
        	 running_threads += 1;

		 /*Create a thread and passing in the function to begin 
		 exectuing as well as that functions required arguments*/ 
		 s = pthread_create(&thread[2], NULL, findAverage, (void *)array_ptr);
		 		 
		 if (s != 0){

           handle_error_en(s, "pthread_create");
       	
       	 }
			running_threads += 1;

			/*Wait for each thread to decrement*/
	    	while(running_threads>0){
	
				sleep(1);

			}
			/*Join our threads*/
			for(n = 0; n < 3; n++){
		
			 	pthread_join(thread[n], NULL);
			
			}
		/*Prompt the user with our results*/
		printf("\nAverage: %d\nMax: %d\nMin: %d\n",Results.average, Results.max, Results.min);

}