#include "source.h"
#include <string.h>
#include <stdio.h>

/* Korsoraattori
 */
void korsoroi(char *dest, const char *src)
{
    int len = strlen(src);
    int nii = 0;
    int tot = 0;
    
    for (int i = 0, j = 0; i < len; i++, j++) {
        if (src[i] == 'k' && src[i+1] == 's') {
            dest[j] = 'x';
            i++;
        }
        else if (src[i] == 't' && src[i+1] == 's') {
            dest[j] = 'z';
            i++;
        }
        else if (src[i] == ' ') {
            nii++;
            tot++;
            dest[j] = ' ';
            if (nii == 3) {
                j++;
                dest[j] = 'n';
                j++;
                dest[j] = 'i';
                j++;
                dest[j] = 'i';
                j++;
                dest[j] = 'n';
                j++;
                dest[j] = 'k';
                j++;
                dest[j] = 'u';
                j++;
                dest[j] = ' ';
                nii = 0;
            }
            else if (tot == 4) {
                j++;
                dest[j] = 't';
                j++;
                dest[j] = 'o';
                j++;
                dest[j] = 't';
                j++;
                dest[j] = 'a';
                j++;
                dest[j] = 'n';
                j++;
                dest[j] = 'o';
                j++;
                dest[j] = 'i';
                j++;
                dest[j] = 'n';
                j++;
                dest[j] = ' ';
                tot = 0;
            }
        }
        else dest[j] = src[i];
    }
    for (int i = 0; i < strlen(dest); i++) {
        if ((!isalpha(dest[i])) && dest[i] != ' ') {
            dest[i] = '\0';
        }
    }
}
