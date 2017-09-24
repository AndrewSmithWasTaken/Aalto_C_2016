#include <stdio.h>
#include "source.h"


/* Number swap
 * Swap the content of integers add addresses a and b
 */
void number_swap(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
    
}

/* Array Sum
 * Calculate the sum of integers in array starting at address <array>.
 * There will be <count> elements in array. Return the sum as return value.
 */
int array_sum(int *array, int count)
{
    (void) array;
    (void) count;
    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += array[i];
    }
    return sum;
}

/* Array Reader */
/* Parameters:
 * vals: array to be filled 
 * n: maximum size of array
 * returns: number of values read */
int array_reader(int *vals, int n)
{
    int x;
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &x) == 1) {
            vals[i] = x;
        } else {
            return i;
        }
    }
    return n;
}