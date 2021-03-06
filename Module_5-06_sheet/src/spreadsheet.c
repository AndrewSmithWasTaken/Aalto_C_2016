#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "spreadsheet.h"

const struct {
    char *name;
    double (*fptr)(Sheet *,Point, Point);
} functions[] = {
    { "sum", sumfunc },
    { "max", maxfunc },
    { "count", countfunc },
    { NULL, NULL }
};


/* Creates a new spreadsheet with given dimensions.
 * Returns pointer to the allocated Sheet structure.
 */
Sheet *create_sheet(unsigned int xsize, unsigned int ysize)
{
    Sheet *s = malloc(sizeof(struct sheet));
    if (!s) {
        return 0;
    }
    s->xsize = xsize;
    s->ysize = ysize;
    s->cells = malloc(ysize * sizeof(struct Cell*));
    if (!s->cells) {
        return 0;
    }
    unsigned int y, x;
    for (y = 0; y < ysize; y++) {
        s->cells[y] = malloc(xsize * sizeof(Cell));
        if (!s->cells) {
            return 0;
        }
    }
    for (y = 0; y < ysize; y++) {
            for (x = 0; x < xsize; x++) {
                s->cells[y][x].type = UNSPEC;
            }
    }
    return s;
}

/* Releases the memory allocated for sheet.
 */
void free_sheet(Sheet *sheet)
{
    for(unsigned int i = 0; i < sheet->ysize; i++) {
        free(sheet->cells[i]);
    }	
    free(sheet->cells);
    free(sheet);
}
int oob(Sheet *sheet, Point p) {
    if (p.x >= sheet->xsize || p.y >= sheet->ysize) {
        return 1;
    }
    else return 0;
}


/* Returns pointer to the Cell structure at given location <p>
 * in spreadsheet <sheet>.
 */
Cell *get_cell(Sheet *sheet, Point p)
{
    if (oob(sheet, p)) {
        return NULL;
    }
    return &sheet->cells[p.y][p.x];
}

/* Convert two-letter user input into coordinates of type Point.
 */
Point get_point(char xc, char yc)
{
    Point p;
    p.x = toupper(xc) - 'A';
    p.y = toupper(yc) - 'A';
    return p;
}

/* Parses user input in <command> and applies it in spreadsheet <sheet>.
 * Returns 1 if input was valid, or 0 if it was not.
 */
int parse_command(Sheet *sheet, const char *command)
{
    double val;
    Point p;
    char xc, yc;
    int ret = sscanf(command, "%c%c %lf", &xc, &yc, &val);
    if (ret == 3) {
        p = get_point(xc, yc);
        set_value(sheet, p, val);
        return 1;
    }
    
    char func[10];
    Point ul, dr;
    char xc1, yc1, xc2, yc2;
    
    ret = sscanf(command, "%c%c %9s %c%c %c%c", &xc, &yc, func, &xc1, &yc1, &xc2, &yc2);
    if (ret == 7) {
        p = get_point(xc, yc);
        ul = get_point(xc1, yc1);
        dr = get_point(xc2, yc2);
        int i = 0;
        while (functions[i].name) {
            if (!strcmp(functions[i].name, func)) {
                set_func(sheet, p, functions[i].fptr, ul, dr);
                return 1;
            }
            i++;
        }
    }
    return 0;
}

/* Prints the content of given spreadsheet.
 */
void print_sheet(Sheet *sheet)
{
    printf("%-8c", ' ');
    for (unsigned int x = 0; x < sheet->xsize; x++) {
        printf("%-8c", 'A' + x);
    }
    fputs("\n", stdout);
    
    for (unsigned int y = 0; y < sheet->ysize; y++) {
        printf("%-8c", 'A' + y);
        for (unsigned int x = 0; x < sheet->xsize; x++) {
            Point p;
            p.x = x;
            p.y = y;
            Cell *c = get_cell(sheet, p);
            switch(c->type) {
                case VALUE:
                case FUNC:
                    printf("%-8.1f", eval_cell(sheet, p));
                    break;
                    
                default:
                    printf("%-8c", '*');
                    break;                    
            }
        }
        fputs("\n", stdout);
    }
}

/* Set the content of location <p> in spreadsheet to constant <value>
 */
void set_value(Sheet *sheet, Point p, double value)
{
    if (!oob(sheet, p)) {
        sheet->cells[p.y][p.x].type = VALUE;
        sheet->cells[p.y][p.x].un.value = value;
    }
}

/* Set the content of location <p> in spreadsheet to given function.
 * <func> is pointer to the function. <ul> is the upper left corner and 
 * <dr> is the lower right corner of the area over which the function
 * is applied.
 */
void set_func(Sheet *sheet, Point p,
        double (*func)(Sheet *, Point, Point),
        Point ul, Point dr)
{
    if (!oob(sheet, p)) {
        sheet->cells[p.y][p.x].type = FUNC;
        sheet->cells[p.y][p.x].un.func.fptr = func;
        sheet->cells[p.y][p.x].un.func.downright = dr;
        sheet->cells[p.y][p.x].un.func.upleft = ul;
    }
}

/* Evaluate the content of cell at location <p>.
 * If cell is constant value, that is returned.
 * If cell contains function, the function is evaluated and its result returned.
 * If cell is unspecified or location out of bounds, NAN is returned.
 */
double eval_cell(Sheet *sheet, Point p)
{
    if (oob(sheet, p)) {
        return NAN;
    }
    if (sheet->cells[p.y][p.x].type == VALUE) {
        return sheet->cells[p.y][p.x].un.value;
    }
    else if (sheet->cells[p.y][p.x].type == FUNC) {
        return sheet->cells[p.y][p.x].un.func.fptr(sheet, sheet->cells[p.y][p.x].un.func.upleft, sheet->cells[p.y][p.x].un.func.downright);
    }
    else return NAN;
}

/* Calculate the maximum value within area with upper left corner <ul>
 * and lower right corner <dl>, and return it.
 */
double maxfunc(Sheet *sheet, Point ul, Point dr)
{
    double largest = 0;
    for (unsigned int y = ul.y; y <= dr.y; y++) {
        for (unsigned int x = ul.x; x <= dr.x; x++) {
            Point p;
            p.x = x;
            p.y = y;
            double tmp = 0;
            if (!isnan(tmp = eval_cell(sheet, p))) {
                if (tmp >= largest) {
                    largest = tmp;
                }
            }
        }
    }
    return largest;  
}

/* Calculate the sum of values within upper left corner <ul> and
 * lower right corner <dr>, and return the result.
 */
double sumfunc(Sheet *sheet, Point ul, Point dr)
{
    double sum = 0;
    for (unsigned int y = ul.y; y <= dr.y; y++) {
        for (unsigned int x = ul.x; x <= dr.x; x++) {
            Point p;
            p.x = x;
            p.y = y;
            double tmp = 0;
            if (!isnan(tmp = eval_cell(sheet, p))) {
                sum = sum + tmp;
            }
        }
    }
    return sum;  
}

/* Count the number of specified cells inside the area with upper left
 * corner <ul> and lower right corner <dr>.
 */
double countfunc(Sheet *sheet, Point ul, Point dr)
{   
    double count = 0;
    for (unsigned int y = ul.y; y <= dr.y; y++) {
        for (unsigned int x = ul.x; x <= dr.x; x++) {
            Point p;
            p.x = x;
            p.y = y;
            if (!isnan(eval_cell(sheet, p))) {
                count++;
            }
        }
    }
    return count;
}
