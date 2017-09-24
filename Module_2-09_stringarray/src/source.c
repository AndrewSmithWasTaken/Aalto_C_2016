#include "source.h"
#include <stdio.h>
#include <string.h>

/* Print string array, last element is NULL */
/* Parameters:
 * array: string array to be printed, each string on own line */
void print_strarray(char *array[])
{
    int i = 0;
    while (array[i] != NULL) {
        printf("%s\n", array[i]);
        i++;
    }
}

/* Put strings from string separated by space to a string array */
/* Parameters:
 * string: string to be cut into parts and placed into the array, 
   remember to add ending zeros '\0' for strings and NULL to the end of the whole array!
 * arr: ready-made array that the strings will be put into */
void str_to_strarray(char* string, char** arr)
{
    int x = 0;
    int y = 0;
    int len = strlen(string); 
    
    for (int i = 0; i < len; i++) {
        if (string[i] != ' ') {
            arr[x][y] = string[i];
            y++;
        }
        if (string[i] == ' ') {
            arr[x][y] = '\0';
            x++;
            y = 0;
        }
    }
    arr[x][y] = '\0';
    arr[x+1] = '\0';
}