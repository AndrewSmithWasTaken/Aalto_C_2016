#include <stdio.h>
#include <stdlib.h>
#include "machdr.h"


void print_header(const unsigned char *header)
{
    printf("Frame Control: %02x %02x\n", header[0], header[1]);
}

int main(void)
{
    const unsigned int FrameLen = 36;
    unsigned char *macframe = malloc(FrameLen);  // alloc MAC header until frame body
    
    // fill header with junk, to make this more interesting
    for (unsigned int i = 0; i < FrameLen; i++) {
        macframe[i] = 0xde; // 11011110
    }
    
    set_proto_version(macframe, 1);
    set_type(macframe, 2);
    set_subtype(macframe, 6);
    set_to_ds(macframe, 0);
    set_from_ds(macframe, 1);
    set_retry(macframe, 0);
    set_more_data(macframe, 1);
    
    print_header(macframe);
    
    printf("Protocol version: %d\n", get_proto_version(macframe));
    printf("Type: %d\n", get_type(macframe));
    printf("Subtype: %d\n", get_subtype(macframe));
    printf("Flags: To DS: %d  From DS: %d  Retry: %d  More Data: %d\n",
            get_to_ds(macframe) != 0, get_from_ds(macframe) != 0,
            get_retry(macframe) != 0, get_more_data(macframe) != 0);
    
    free(macframe);
}

//set_proto_version that will set the protocol version header field according to the version argument in the function.
//
//set_type that will set the type field according to the type argument in the function
//
//set_subtype that will set the subtype field according to the subtype argument in the function
//
//set_to_ds, set_from_ds, set_retry, set_more_data that will set the respective flags according to the flag argument in the functions. If the flag argument is non-zero, the flag bit will be set, if it is zero, the flag bit will be cleared.