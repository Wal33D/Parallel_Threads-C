#define ANSI_COLOR_RED     "\x1b[31m"	//Just Some Cool Colors for Console Output     
#define ANSI_COLOR_GREEN   "\x1b[34m"
#define ANSI_COLOR_BLUE    "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#include <dirent.h> 
#include <string.h>
#include <unistd.h>
#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <syscall.h>

char fileName[100][100];
char *directory;
pthread_t thread[4];
pthread_mutex_t lock;
int totalN;


////////////////spinTheThreads()////////////////////
////////////////////////////////////////////////////
void spinTheThreads(int numberOfThreads){

    	pthread_create(&thread[0], NULL, ProcessFile,  (void *) &fileName[i]);
    	
    	pthread_create(&thread[0], NULL, ProcessFile,  (void *) &fileName[i]);
   		
   		pthread_create(&thread[0], NULL, ProcessFile,  (void *) &fileName[i]);

	 printf("    Number of Threads Spun\n" );

}
////////////////tieSomeKnots()////////////////////
//////////////////////////////////////////////////
void tieSomeKnots(fileFinderReturn){
	
	int i;
	
	for(i = 0; i < fileFinderReturn; i++){

		  pthread_join(thread[i], NULL);
	}
		
	  	printf("   [%d] Thread Joining Succesfull!\n", i);
}

////////////////main()//////////////////////////////
////////////////////////////////////////////////////
int main(int argc, char *argv[]){	
	
	pthread_mutex_init(&lock, NULL);
	
	int fileFinderReturn;
	
	totalN = 0;
	
	fileFinderReturn = fileFinder(argv[1]);

	if(fileFinderReturn == -1){
		
		 printf("Sorry, No files were found in %s\n", argv[1]);
		
		return 1;
		
	}else{
		 
		printf("\n\n---Welcome to W@L33D'z A4: Parallel Sort---\n"ANSI_COLOR_RESET);
		printf("    Search Path[%s]\n    Unsorted Files[%d]\n"ANSI_COLOR_RESET , argv[1],fileFinderReturn);
		
		int i =0;
		
		//At this point fileFinderReturn == # of Files 0 - N//
		
		spinTheThreads(fileFinderReturn);
		
		tieSomeKnots(fileFinderReturn);
		
	    printf("[%d] Records Sorted Sucessfull!\n" ,totalN );

     	//At this point our threads have been 
		//created, everything has been read 
		//from the scrambled files into our 
		//Global Array and, Merged, then sorted
		//And our threads have been joined
		
		//Now write it to yay.txt
		
		writeToFile(totalN);
		
		//If you made it this far you will have a
		//file named yay.txt in the programs root
	
  		}
	
return 0;
	
}
////////////////End//////////////////////////////
////////////////////////////////////////////////
	
		

