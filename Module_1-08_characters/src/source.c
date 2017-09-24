#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "source.h"

/* Don't touch the definition of msgs array! Checker uses this. */
char *msgs[10] = {
    "'6=*w+~)._", "J65+~5+~=0/*69,~+9;,9*~19++=79"
};


void ascii_chart(char min, char max)
{
    int c;
    for (int i = min, c = 1; i <= max; i++, c++) {
        if (isprint(i) == 0) {
            printf("%3d 0x%02x ?", i, i);
        }
        else printf("%3d 0x%02x %c", i, i, i);
        if (c % 4 == 0) {
            printf("\n");
        }
        else printf("\t");
    }
}

char get_character(int msg, unsigned int cc) {
    if (msg >= 10 || !msgs[msg])
        return 0;

    if (strlen(msgs[msg]) <= cc)
        return 0;
    
    return msgs[msg][cc];
}


void secret_msg(int msg)
{
    int cc = 0;
    while (get_character(msg, cc) != 0) {
        printf("%c", 158 - get_character(msg, cc));
        cc++;
    }
    
}
