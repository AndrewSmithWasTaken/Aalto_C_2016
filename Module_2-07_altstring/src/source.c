#include "source.h"
#include <stdbool.h>


/* Print string */
/* Parameters:
 * s: string to be printed */
void es_print(const char *s)
{
    char buffer[50];
    for (int i = 0; i < es_length(s); i++) {
        if (s[i] != '#') {
            buffer[i] = s[i];
        }
        else {
            buffer[i] = '\0';
            break;
        }
    }
    printf("%s", buffer);
}

/* String length */
/* Parameters:
 * s: string to be evaluated
 * Returns: length of the string */
unsigned int es_length(const char *s)
{
    int count = 0;
    while (s[count] != '#') {
        count++;
    }
    return count;
}

/* String copy */
/* Parameters:
 * dst: buffer to which the new string is copied
 * src: original string
 * Returns: Number of characters copied
 */
int es_copy(char *dst, const char *src)
{
    int count = 0;
    int length = es_length(src);
    for (int i = 0; i < length +1; i++) {
            dst[i] = src[i];
            count++;
            if (i == length) {
                dst[i] = '#';
                count--;
            }
    }
    return count;
}

/* String tokenizer */
/* Parameters:
 * s: string to be processed
 * c: character to be replaced by '#'
 * Returns: pointer to the character following the replaced character,
 *          NULL if end of string reached */
char *es_token(char *s, char c)
{
    bool result;
    char *ptr;
    for (int i = 0; i < es_length(s); i++) {
        if (s[i] == c) {
            s[i] = '#';
            ptr = &s[i+1];
            result = true;
            break;
        }
    }
    if (!result) {
            return NULL;
    }   
    else return ptr;
}
