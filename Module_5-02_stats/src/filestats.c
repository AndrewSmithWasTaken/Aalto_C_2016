#include "filestats.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_CHAR 1024

/* Returns the line count in given file
 * 
 * Parameters:
 * filename: name of the file to be investigated.
 * 
 * Returns:
 * The number of lines in file. */
int line_count(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        return -1;
    }
    int lines = 0;
    char line[MAX_CHAR];
    while (fgets(line, MAX_CHAR, fp) != NULL) {
        lines++;
    }
    fclose(fp);
    return lines;
}


/* Count the number of words in the file. Word has to include at least one
 * alphabetic character, and words are separated by whitespace.
 * 
 * Parameters:
 * filename: name of the file to be investigated.
 * 
 * Returns:
 * number of words in the file */
int word_count(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        return -1;
    }
    int flag = 0;
    int words = 0;
    char c;
    while ((c = fgetc(fp)) != EOF) {
        if (isalpha(c)) {
            flag = 1;
        }
        if ((c == ' ' || c == '\t' || c == '\n') && flag == 1) {
            words++;
            flag = 0;
        }
    }
    if (flag == 1) {
        words++;
    }
    fclose(fp);
    return words;
}