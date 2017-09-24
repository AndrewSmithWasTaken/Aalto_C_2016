#include "source.h"


/* Selection sort */
/* Parameters:
 * start: start of an array
 * size: length of an array
 */
void sort(int *start, int size)
{
    for (int i = 0; i < size-1; i++) {
        int min = i;
        for (int j = i; j < size; j++) {
            if (start[j] < start[min]) {
                min = j;
            }
        }
        if (min != i) {
            int temp = start[min];
            start[min] = start[i];
            start[i] = temp;
        }
    }
}