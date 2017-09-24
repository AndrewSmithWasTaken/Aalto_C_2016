#include "source.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>


/* Count Alpha
 * Count number of alphabetic characters in the given string <str>,
 * and return the count
 */
int count_alpha(const char *str)
{
    int count = 0;
    while (*str) {
        if (isalpha(*str)) {
            count++;
        }
        str++;
    }
    return count;
//    for (int i = 0; i < strlen(str); i++) {
//        if (isalpha(str[i])) {
//            count ++;
//        }
//    }
}
/* Count Substring
 * Count number of occurances of substring <sub> in string <str>,
 * and return the count.
 */
int count_substr(const char *str, const char *sub) {
    int count = 0;
    while ( (str = strstr(str, sub)) != NULL ) {
        count++;
        str++;
    }
    return count;
}