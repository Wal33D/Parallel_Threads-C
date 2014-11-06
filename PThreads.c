/**************************************************************************************
* Course: CS 4540 – Fall 2014
* Assignment <3>
* Name: <Waleed Gudah>
* E-mail: <waleed.h.gudah@wmich.edu>
* Submitted: <11/6/14>

	This is a multithreaded program that calculates various statistical values
	for a list of numbers. This program will be passed a series of numbers on 
	the command line and will then create three separate worker threads:

	1) Thread 1 will determine the average of the numbers
	2) Thread 2 will determine the maximum value
	3) Thread 3 will determine the minimum value

 NOTE: 
	I used a dynamically increasing integer array, the same array I used in part 
	3 of Assignment 1, I mention this becuase my program looks slightly different, 
	on the cmd console, then the demo we were provided Instead of first specifying a # of 
	elements for the array my array size increases as needed.
/****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

/*Error handling for pthread_create and pthread_join*/
/*from the pthread_create man page*/
#define handle_error_en(en, msg) \
        do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error(msg) \
        do { perror(msg); exit(EXIT_FAILURE); } while (0)

/* # of running threads */
volatile int running_threads = 0;

/*Descriptors for our 3 threads*/
pthread_t thread[3];

/*Struct to hold the statistical results*/
struct Results{
	
	int min;
	int max;
	int average;

}Results;

/*Total # of elements from the user*/
int numOfElements;

/*This function finds the minimum element of an array*/
void *findMin(void *array_ptr){
	
	int i; /*counter*/
	
	int *elements = (int*)array_ptr; /*re reference void array pointer*/ 

	Results.min = elements[0]; /*set minimum to first element */

	/*iterate through array*/
	for(i = 0; i < numOfElements; i++){
		/*if the current element is less than the current min*/
		if(elements[i] < Results.min){

			/*store the new min*/
			Results.min = elements[i];
		}
	}
	/*Decrement thread count*/
	running_threads -= 1;

	return NULL;

}

/*This function finds the maximum element of an array*/
void *findMax(void *array_ptr){
	
	int i;	/*counter*/

	int *elements = (int*)array_ptr; /*re reference void array pointer*/ 
	/*iterate through array*/
	for(i = 0; i < numOfElements; i++){
		/*if the current element is greater than the current max*/
		if(elements[i] > Results.max){
			/*store the new max*/
			Results.max = elements[i];

		}
	}

	/*Decrement thread count*/
	running_threads -= 1;

	return NULL;
}

/*This function finds the average of an array*/
void *findAverage(void *array_ptr){
	
	int i; /*counter*/

	int *elements = (int*)array_ptr; /*re reference void array pointer*/
	/*iterate through array*/
	for(i = 0; i < numOfElements; i++){
		/*add element @ i to average*/
			Results.average += elements[i];

	}
	/*Divide the sum by the number of elements*/
	Results.average = Results.average/numOfElements;
	/*Decrement running threads counter*/
	running_threads -= 1;

	return NULL;
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
   
    		//Get Int from console, store at address of input

			if (scanf("%d",&input) != 1){

				printf("\nOops that wasn't an Integer\nlets try filling the array again\nRemember INTEGERS only!\n");

				exit(EXIT_FAILURE);
			
			}

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

/*This function joins our n number of threads */
void joinThreads(){
	
	int i; /*count*/

	int s; /*error #*/
	
	/*Join our threads*/
	for(i = 0; i < 3; i++){
					
		s = pthread_join(thread[i], NULL);
		 /*if we recieve anything other than 0 we have a join error*/
		 if (s != 0){
		 	/*handle error*/
			handle_error_en(s, "pthread_create");
		 
		 }
	
	}
		
}

/*This function creates the 3 threads we need and supplys
  error catching for pthread_create, it could be 
  modified easily to create any # of threads automatically
*/
void createThreads(int *array_ptr){
	
	int s; /*error #*/
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
		
		 createThreads(array_ptr);
		
			/*Wait for each thread to decrement*/
	    	while(running_threads>0){
	
				sleep(1);

			}

		joinThreads();

		/*Prompt the user with our results*/
		printf("\nAverage: %d\nMax: %d\nMin: %d\n",Results.average, Results.max, Results.min);

	return(0);

}