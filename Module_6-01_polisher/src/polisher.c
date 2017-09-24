#include <stdlib.h>
#include "polisher.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>


/* Read given file <filename> to dynamically allocated memory.
 * Return pointer to the allocated memory with file content, or
 * NULL on errors.
 */
char *read_file(const char *filename)
{
    // Open file, declare variables
    FILE *f = fopen(filename, "r");
    char *code;
    int size;
    if (!f) {
        return NULL;
    }
    // Get file size
    fseek(f, 0, SEEK_END);
    size = ftell(f);
    rewind(f);
    // Allocate memory
    code = malloc(sizeof(char) * size + 1);
    if (!code) {
        return NULL;
    }
    // Read into buffer (adding terminator), close file, return pointer
    fread(code, sizeof(char), size, f);
    code[size] = '\0';
    fclose(f);
    return code;
}


/* Remove C comments from the program stored in memory block <input>.
 * Returns pointer to code after removal of comments.
 * Calling code is responsible of freeing only the memory block returned by
 * the function.
 */
char *remove_comments(char *input)
{
    //reserve space for output buffer
    int len = strlen(input);
    char *output = calloc(len, 1);
    char *ptr = input;
    int flag = 1;
    int i = 0;
    while (*ptr) {
        //if we're in code
        if (flag == 1) {
            //if starts a // comment, note that, maybe move input if playing with pointers
            if (*ptr == '/' && *(ptr + 1) == '/') {
                flag = 2;
                ptr++;
            }
            //if starts a /* */ comment, note that, maybe move input if playing with pointers
            if (*ptr == '/' && *(ptr + 1) == '*') {
                flag = 3;
                ptr++;
            }
            //otherwise just save to output the content
            if (flag == 1) {
                output[i] = *ptr;
                i++;
            }
        }
        //if we're in //
        if (flag == 2) {
            //if we've got '\n'
            if (*ptr == '\n') 
                //now we're in code again!
                flag = 1;
        }
        //if we're in /* */
        if (flag == 3) {
            //if we've got */, skip the */ and then
            if (*ptr == '*' && *(ptr + 1) == '/') {
                //we're in code!
                flag = 1;
                ptr++;
            }
        }
        //move forward
        ptr++;
    }
    //set the '\0'
    output[i] = '\0';
    //free original
    free(input);
    return output;
}

/* Indent the C-code at memory block <indent>. String <pad> represents
 * one block of indentation. Only opening curly braces '{' increase the
 * indentation level, and closing curly braces '}' decrease the indentation level.
 * Return the pointer to the code after modification.
 * Calling code is responsible of freeing only the memory block returned by
 * the function.
 */

char *indent(char *input, const char *pad)
{
    int indent_level = 0;
    int padLen = strlen(pad);
    int c = 0;
    char *crawler = input;
    char *output = calloc(100000, 1);
    // Loop through input
    while (*crawler) {
        // If we find a left brace..
        if (*crawler == '{') {
            //  Increase indent, output and move forward
            indent_level++;
            output[c] = *crawler;
            c++;
            crawler++;
        }
        // If we find a newline..
        if (*crawler == '\n') {
            char *waitHere = crawler;
            // If the next char is a right brace, decrease indent before we get there
            if (*(crawler + 1) == '}') {
                indent_level--;
            }
            // If the next char is blank, consume until non-blank is found
            while (isblank(*(crawler + 1))) {
                crawler++;
            }
            output[c] = *waitHere;
            c++;
            crawler++;
            if (indent_level) {
                if (*crawler != '\n') {
                    for (int h = 0; h < indent_level; h++) {
                        for (int i = 0; i < padLen; i++) {
                            output[c] = pad[i];
                            c++;
                        }
                    }
                }
                
            }
        }
        else {
            output[c] = *crawler;
            c++;
            crawler++;
        }
    }
    output[c] = '\0';
    free(input);
    return output;
}