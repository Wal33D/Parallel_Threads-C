#include <pthreads.h>

/*Error handling for pthread_create and pthread_join*/
/*from the pthread_create man page*/
#define handle_error_en(en, msg) \
        do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

// # of running threads 
volatile int running_threads = 0;

pthread_t thread[3]; //Descriptors for our 3 threads

int numOfElements; //Total # of elements from the user


//This function joins our n number of threads 
void joinThreads(int numberOfThreads)
{

	int i; //count

	int s; //error #

	while (numberOfThreads >= 0)
	{ //Join our threads

		s = pthread_join(thread[numberOfThreads], NULL);

		//if we recieve anything other than 0 we have a join error
		if (s != 0)
		{
			//handle error
			handle_error_en(s, "pthread_create");
		}

		numberOfThreads--;
	}
}

//This function creates the 3 threads we need and supplys
//error catching for pthread_create, it could be
//modified easily to create any # of threads automatically

void createThreads(int *array_ptr)
{

	int s; //error #
	//Create a thread and passing in the function to begin
	//exectuing as well as that functions required arguments

	s = pthread_create(&thread[0], NULL, findMin, (void *)array_ptr);

	if (s != 0)
	{

		handle_error_en(s, "pthread_create");
	}
	running_threads += 1;

	//Create a thread and passing in the function to begin
	//exectuing as well as that functions required arguments
	s = pthread_create(&thread[1], NULL, findMax, (void *)array_ptr);

	if (s != 0)
	{

		handle_error_en(s, "pthread_create");
	}
	running_threads += 1;

	//Create a thread and passing in the function to begin
	//exectuing as well as that functions required arguments
	s = pthread_create(&thread[2], NULL, findAverage, (void *)array_ptr);

	if (s != 0)
	{

		handle_error_en(s, "pthread_create");
	}

	running_threads += 1;
}

// The main function initialiazes the dynamic array as well
// as allocating space for it, Then it creates, using pthread_create, 
//3 Threads 1 to calculate the min, the max, and the average.
//We then wait until each thread completes its task and then
//join the 3 threads and prompt the user with the results
 
int main()
{

	int n = 1; // Initial Array Size

	int *array_ptr = malloc(n * sizeof(int)); //Initialize array pointer

	//get an n sized array of elements from the user and save count
	numOfElements = getArrayInput(n, array_ptr);

	createThreads(array_ptr);

	while (running_threads > 0)
	{ //Wait for each thread to decrement

		sleep(1);
	}

	joinThreads(2); //Call our thread joining function passing # of threads 

	//Prompt the user with our results
	printf("\nThe average is %d\nThe maximum is %d\nThe minimum is %d\n", Results.average, Results.max, Results.min);

	return (0);
}