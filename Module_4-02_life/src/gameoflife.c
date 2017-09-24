#include <stdlib.h>
#include "gameoflife.h"
#include <time.h>
#include <stdio.h>
#include <string.h>


/* Exercise a: Allocates needed memory for the field structure and
 * the actual game field. 'xsize' and 'ysize' indicate the horizontal and
 * vertical dimensions of the field.
 * 
 * Returns: pointer to the Field structure allocated by this function.
 */
Field *createField(unsigned int xsize, unsigned int ysize)
{
    Field *f = malloc(sizeof(Field));
    f->xsize = xsize;
    f->ysize = ysize;
    f->cells = malloc(ysize * sizeof(int *));
    if (!f->cells) {
        return 0;
    }
    unsigned int y, x;
    for (y = 0; y < ysize; y++) {
        f->cells[y] = malloc(xsize * sizeof(int));
        if (!f->cells) {
            return 0;
        }
    }
    for (y = 0; y < ysize; y++) {
            for (x = 0; x < xsize; x++) {
                f->cells[y][x] = DEAD;
            }
    }
    return f;
}

/* Free memory allocated for field <f>.
 */
void releaseField(Field *f)
{
    for(unsigned int i = 0; i < f->ysize; i++) {
        free(f->cells[i]);
    }	
    free(f->cells);
    free(f);
}

/* Exercise b: Initialize game field by setting exactly <n> cells into
 * ALIVE state in the game field <f>.
 */
void initField(Field *f, unsigned int n)
{
    unsigned int count = 0;
    time_t t;
    srand((unsigned) time(&t));
    unsigned int y, x;
    for (y = 0; y < f->ysize; y++) {
        for (x = 0; x < f->xsize; x++) {
            if (((rand() % 100) % 2 == 0) && count < n) {
                f->cells[y][x] = ALIVE;
                count++;
            }
        }
    }
}

/* Exercise c: Output the current state of field <f>.
 */
void printField(const Field *f)
{
    unsigned int y, x;
    for (y = 0; y < f->ysize; y++) {
        for (x = 0; x < f->xsize; x++) {
            if (f->cells[y][x] == DEAD) {
                f->cells[y][x] = '.';
                printf("%c", f->cells[y][x]);
            }
            else {
                f->cells[y][x] = '*';
                printf("%c", f->cells[y][x]);
            }
        }
        printf("\n");
    }
}


/* Exercise d: Advance field <f> by one generation.
 */
void tick(Field *f)
{
    Field *current = createField(f->xsize, f->ysize);
    unsigned int y,x;
    for (y = 0; y < f->ysize; y++) {
        for (x = 0; x < f->xsize; x++) {
            if (f->cells[y][x] == ALIVE) {
                current->cells[y][x] = ALIVE;
            }
        }
    }
    for (y = 0; y < current->ysize; y++) {
        for (x = 0; x < current->xsize; x++) {
            int neighbours = count_neighbours(current, y, x);
            if ((current->cells[y][x] == ALIVE) && (neighbours < 2)) {
                f->cells[y][x] = DEAD;
            }
            if ((current->cells[y][x] == ALIVE) && ((neighbours == 2) || (neighbours == 3))) {
                f->cells[y][x] = ALIVE;
            }
            if ((current->cells[y][x] == ALIVE) && (neighbours > 3)) {
                f->cells[y][x] = DEAD;
            }
            if ((current->cells[y][x] == DEAD) && (neighbours == 3)) {
                f->cells[y][x] = ALIVE;
            }
        }
    }
    releaseField(current);
}

int count_neighbours(Field *f, int yPos, int xPos)
{
    int i, j; 
    int neighbours = 0;
    for (i = -1; i <= 1; i++) {
        for (j = -1; j <= 1; j++) {
            if ((yPos+i < 0) || (yPos+i >= f->ysize)) {
                continue;
            }
            if ((xPos+j < 0) || (xPos+j >= f->xsize)) {
                continue;
            }
            if ((yPos+i == yPos) && (xPos+j == xPos)) {
                continue;
            }
            if (f->cells[yPos+i][xPos+j] == ALIVE) {
                neighbours++;
            }
        }
    }
    return neighbours;
}