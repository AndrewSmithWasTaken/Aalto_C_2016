#include <stdio.h>
#include "base64.h"

int main(int argc, char *argv[])
{
    /* You can modify this file as needed, for example to test different
     * files. If you run on command line, this function optionally reads
     * the filename from command line, if one is given. */
    
    char *filename = "test/testi.txt.ref"; //"src/oneline.txt"; // //
    if (argc > 1) {
        filename = argv[1];
    }
    
    // Write encoded file to 'testi.enc'
    int n = to_base64("testi.enc", filename);
    printf("to_base64 returned: %d\n", n);
    
    // Follow with reverse operation -- 'testi.ver' should be same as
    // your original source file
    n = from_base64("testi.ver", "testi.enc");
    printf("from_base64 returned: %d\n", n);
}


//size_t fwrite ( const void * ptr, size_t size, size_t count, FILE * stream );
//Write block of data to stream
//Writes an array of count elements, each one with a size of size bytes, from the block of memory pointed by ptr to the current position in the stream.
//
//The position indicator of the stream is advanced by the total number of bytes written.
//
//Internally, the function interprets the block pointed by ptr as if it was an array of (size*count) elements of type unsigned char, and writes them sequentially to stream as if fputc was called for each byte.