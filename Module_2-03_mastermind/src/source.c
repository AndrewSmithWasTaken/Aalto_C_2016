#include <stdio.h>
#include "source.h"


#ifndef MAWKKE
// longer solution by Pasi

/* 03-mastermind
 */
void mastermind(const int *solution, const int *guess, char *result, unsigned int len) {
    
    unsigned int i, j, k, l, val;
    for (i = 0; i < len; i++) {
            result[i] = '-';
    }
    j= 0;
    for (j = 0; j< len; j++) {
        for (k = 0; k < len; k++) {
            if (solution[k] == guess[j]) {
                result[j] = '*';
            }
        }
    }
    for (l = 0; l < len; l++) {
        if (guess[l] == solution[l]) {
            result[l] = '+';
        }
    }
}
#endif