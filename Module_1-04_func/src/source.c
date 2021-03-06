#include <math.h>

double vectorlength(double x, double y, double z) {
    return sqrt(pow(x,2) + pow(y, 2) + pow(z, 2));
}

//Objective: get familiar with writing a function, and calling another function.
//
//Implement function titled vectorlength that calculates the length of the given 
//three-dimensional euclidean vector. The function gets three arguments that 
//represent the different components in the three-dimensional space. The function 
//should return the length of the vector. All numbers should be double-precision 
//floating point numbers.
//
//If you have forgotten about vector mathematics, you can find additional 
//information in the Wikipedia. You will need to calculate square root that is 
//not part of C's basic operators, but there is a sqrt function in that math 
//library that you can use. With pow function you can calculate power functions. 
//See the detailed function specifications from the linked manual pages.
//
//Implement your function in file source.c. The file already has reference to 
//math.h header that defines the math functions, but in this exercise you will 
//need to write everything else by yourself. Initially, the program will not 
//even compile, before you have implemented at least a placeholder for the 
//function.