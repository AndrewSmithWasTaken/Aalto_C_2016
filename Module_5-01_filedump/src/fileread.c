#include "fileread.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

/* Prints the given file as text on the screen.
 * Only printable characters are shown. Non-printable characters are printed
 * as '?'. <filename> parameter is the name of the file.
 * 
 * Returns the number of characters read
 */
int textdump(const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f) {
        return -1;
    }
    char c;
    int bytesRead = 0;
    while ((c = fgetc(f)) != EOF) {
        if (isprint(c)) {
            printf("%c", c);
        }
        else {
            printf("?");
        }
        bytesRead++;
    }
    fclose(f);
    return bytesRead;
}

/* Prints the given file as hexdump, at most 16 numbers per line.
 * <filename> parameter is the name of the file.
 * 
 * Returns the number of characters read
 */
int hexdump(const char *filename)
{
    FILE *f = fopen(filename, "r");
    char *buffer;
    int size, i, j;
    if (!f) {
        return -1;
    }
    // Get file size
    fseek(f, 0, SEEK_END);
    size = ftell(f);
    rewind(f);
    // Allocate memory for buffer
    buffer = malloc(sizeof(char) * size);
    if (!buffer) {
        fprintf(stderr, "Nope.\n");
        return -1;
    }
    // Copy the file to the buffer
    fread(buffer, sizeof(char), size, f);
    // Can print with this function
    //fwrite (buffer, 1, size, stdout);
    // Print 16 bytes per line
    for (i = 0, j = 1; i < size; i++, j++) {
        printf("%02x ", buffer[i]);
        if (j == 16) {
            printf("\n");
            j = 0;
            continue;
        }
    }
    free(buffer);
    fclose(f);
    return i;
}

/* "Aalto solution"
 int hexdump(const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f)
        return -1;
    int c;
    int i = 0;
    while ((c = fgetc(f)) != EOF) {
        printf("%02x ", c);
        i++;
        if (!(i % 16))
            fputc('\n', stdout);
    }
    fclose(f);
    return i;
}
 */