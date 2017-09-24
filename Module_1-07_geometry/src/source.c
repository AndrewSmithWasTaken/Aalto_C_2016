#include <stdio.h>
#include <math.h>
#include "source.h"


void multi_table(unsigned int xsize, unsigned int ysize)
{
    for (int y = 1; y <= ysize; y++) {
        for (int x = 1; x <= xsize; x++) {
            printf("%4d", x*y);
            if (x == xsize) {
                printf("\n");
            }
        }
    }
}

void draw_triangle(unsigned int size)
{
    int dot;
    int hash;
    
    for (int i=1; i<=size; i++)
    {
        for (dot = (size - i); dot > 0; dot--)
        {
            printf("."); 
        }
        for (hash = 1; hash <= i; hash++)
        {   
            printf("#"); 
        }
        printf("\n");
    }
}

double distance(int x, int y)
{
    return sqrt(x * x + y * y);
}
 

void draw_ball(unsigned int radius)
{
    int new_radius = (int) radius;
    for (int y = -new_radius; y <= new_radius; y++) {
        for (int x = -new_radius; x <= new_radius; x++) {
            if (distance(x,y) <= radius) {
                printf("*");
            }
            else printf(".");
            if (x == radius) {
                printf("\n");
            }
        }
    }
}