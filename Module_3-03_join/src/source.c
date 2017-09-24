#include "source.h"
#include <stdio.h>

int *join_arrays(unsigned int n1, int *a1, unsigned int n2, int *a2, unsigned int n3, int *a3) {
    
    int *joinedArray = malloc((n1+n2+n3) * sizeof(unsigned int));
    
    if (!joinedArray) {
        return -1;
    }
    
    for (int i = 0; i < n1; i++) {
        joinedArray[i] = a1[i];
    }
    for (int i = n1, j = 0; j < n2; i++, j++) {
        joinedArray[i] = a2[j];
    }
    for (int i = (n1)+(n2), j = 0; j < n3; i++, j++) {
        joinedArray[i] = a3[j];
    }
    
    return joinedArray;
}
