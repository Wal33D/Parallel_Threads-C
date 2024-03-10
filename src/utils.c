#include "utils.h"

/* Global variables and struct definitions are declared in utils.h */

/*This function finds the minimum element of an array*/
void *findMin(void *array_ptr)
{

    int i; /*counter*/

    int *elements = (int *)array_ptr; /*re reference void array pointer*/

    Results.min = elements[0]; /*set minimum to first element */

    for (i = 0; i < numOfElements; i++)
    { /*iterate through array*/

        if (elements[i] < Results.min)
        { /*if the current element is less than the current min*/

            Results.min = elements[i]; /*store the new min*/
        }
    }

    running_threads -= 1; /*Decrement thread count*/

    return NULL;
}

/*This function finds the maximum element of an array*/
void *findMax(void *array_ptr)
{

    int i; /*counter*/

    int *elements = (int *)array_ptr; /*re reference void array pointer*/

    for (i = 0; i < numOfElements; i++)
    { /*iterate through array*/

        if (elements[i] > Results.max)
        { /*store the new max*/

            Results.max = elements[i];
        }
    }

    running_threads -= 1; /*Decrement thread count*/

    return NULL;
}

/*This function finds the average of an array*/
void *findAverage(void *array_ptr)
{

    int i; /*counter*/

    int *elements = (int *)array_ptr; /*re reference void array pointer*/

    for (i = 0; i < numOfElements; i++)
    { /*iterate through array*/

        Results.average += elements[i]; /*add element @ i to average*/
    }

    Results.average = Results.average / numOfElements; /*Divide the sum by the number of elements*/

    running_threads -= 1; /*Decrement running threads counter*/

    return NULL;
}

/* This method accepts a int n(initial size of array) and
   pointer to an array and returns # of elements in the array
*/
int getArrayInput(int n, int *array_ptr)
{

    int input; /*Store user input */

    int numberOfElements = 0; /*Number of Integers inputed*/

    printf("Creating Dynamic Array...\n-\n");

    for (;;)
    { /*infinite loop*/

        printf("Enter a positive value:\nNegative Number to Stop\n-\n");

        // Get Int from console, store at address of input

        if (scanf("%d", &input) != 1)
        {

            printf("\nOops that wasn't an Integer\nlets try filling the array again\nRemember INTEGERS only!\n");

            exit(EXIT_FAILURE);
        }

        if (input >= 0)
        {

            if (numberOfElements == n)
            {

                n += 1; // Make room for the current input

                array_ptr = realloc(array_ptr, n * sizeof(int)); // realloc array and set pointer
            }

            array_ptr[numberOfElements++] = input; // Store input at next empty element
        }
        else
        {

            printf("\nNumber of Integers: %d\n", numberOfElements);

            break;
        }
    }

    return numberOfElements;
}
