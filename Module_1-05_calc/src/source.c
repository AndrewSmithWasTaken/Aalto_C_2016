#include <stdio.h>
#include <math.h>
#include "source.h"



void simple_sum(void)
{
    int x;
    scanf("%d", &x);
    int y;
    scanf("%d", &y);
    printf("%d + %d = %d\n", x,y,x+y);
}


void simple_math(void)
{
    float a;
    scanf("%f", &a);
    
    char b;
    scanf(" %c", &b);
    
    switch (b) 
    {
        case '+':
        case '-':
        case '*':
        case '/':
            break;
        default:
            printf("ERR");
            break;
    }
    
    float c;
    scanf("%f", &c);
    
    if (b == '+') 
    {
        printf("%.1f", a+c);
    }
    else if (b == '-') 
    {
        printf("%.1f", a-c);
    } 
    else if (b == '*') 
    {
        printf("%.1f", a*c);
    }
    else if (b == '/') 
    {
        printf("%.1f", a/c);
    } 
}
