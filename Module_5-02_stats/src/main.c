#include <stdio.h>
#include "filestats.h"

int main(int argc, char *argv[])
{
    /* You can modify this file as needed, for example to test different
     * files. If you run on command line, this function optionally reads
     * the filename from command line, if one is included. */
    char *filename = "oneline.txt";
    if (argc > 1) {
        filename = argv[1];
    }
    
    printf("Line count: %d\n", line_count(filename));
    
    printf("Word count: %d\n", word_count(filename));
}

//Implement function int word_count(const char *filename) that calculates the number of words in the given file and returns the word count. In this exercise we define word like this: Word is a substring that contains at least one alphabetic character. Two words are separated by one or more whitespace characters. If there is an error, the function should return -1. (Note that shell command 'wc -w' defines a "word" differently, and cannot be used to compare results with this function)