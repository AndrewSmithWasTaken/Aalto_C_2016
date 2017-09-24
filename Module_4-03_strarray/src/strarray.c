#include <stdio.h>
#include "strarray.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Exercise a: Initializes the string array to contain the initial
 * NULL pointer, but nothing else.
 * Returns: pointer to the array of strings that has one element
 *      (that contains NULL)
 */
char **init_array(void)
{
    char **strings = malloc(sizeof(char*));
    strings[0] = NULL;
    return strings;
}

/* Releases the memory used by the strings.
 */
void free_strings(char **array)
{
    int i=0;
    while(array[i] != NULL)
    {
        free(array[i]);
        i++;
    }
    free(array);
}

/* Exercise b: Add <string> to the end of array <array>.
 * Returns: pointer to the array after the string has been added.
 */
char **add_string(char **array, const char *string){
    int i = 0;
    while (array[i] != NULL){        
        i++;
    }
    array[i] = malloc(strlen(string) + 1);
    strcpy(array[i], string);
    char **temp;
    temp = realloc(array, (i+1+1) * sizeof(char *));
    if(temp == NULL){
        return 0;
    } else {
        array = temp;
        array[i+1] = NULL;
    }
    return array;
}


/* Exercise c: Convert letters of all strings in <array> to lower case.
 */
void make_lower(char **array)
{
    int y = 0;
    while (array[y] != NULL) {        
        for (int x = 0; array[y][x] != '\0'; x++) {
            array[y][x] = tolower(array[y][x]);
        }
        y++;
    } 
}


/* Exercise d: reorder strings in <array> to lexicographical order */
void sort_strings(char **array)
{
    for (int i = 0; array[i] != NULL; i++) {
        int min = i;
        for (int j = i; array[j] != NULL; j++) {
            if (strcmp(array[j], array[min]) < 0) {
                min = j;
            }
        }
        if (min != i) {
            char *tmp = array[min];
            array[min] = array[i];
            array[i] = tmp;
        }
    }
}

/* You can use this function to check what your array looks like.
 */
void print_strings(char **array)
{
    if (!array)
        return;
    while (*array) {
        printf("%s  ", *array);
        array++;
    }
    printf("\n");
}
