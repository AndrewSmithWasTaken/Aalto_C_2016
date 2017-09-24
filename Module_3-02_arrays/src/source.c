#include <stdlib.h>
#include "source.h"
#include <stdio.h>


/* Dynamic Array Reader */
/* Parameters:
 * n: Number of values to be read
 * 
 * Returns: pointer to the dynamically allocated array
 */
int *dyn_reader(unsigned int n)
{
    int *array = malloc(n * sizeof(int));
    if (!array) {
        return -1;
    }
    for (unsigned int i = 0; i < n; i++) {
        unsigned int input;
        scanf("%u", &input);
        array[i] = input;
    }
    return array;
}

/* Add to array */
/* Parameters:
 * arr: Existing array of integers
 * num: number of integers in the array before the call
 * newval: new value to be added
 * 
 * Returns: pointer to the allocated array
 */
int *add_to_array(int *arr, unsigned int num, int newval)
{
    int *newArray = realloc(arr, num * sizeof(int) + sizeof(newval));
    if (!newArray) {
        return -1;
    }
    newArray[num] = newval;
    return newArray;
}