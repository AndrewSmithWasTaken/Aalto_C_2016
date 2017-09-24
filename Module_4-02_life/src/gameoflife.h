#ifndef AALTO_MINESWEEPER_H
#define	AALTO_MINESWEEPER_H

typedef enum {
    DEAD,
    ALIVE
} State;

typedef struct {
    unsigned int xsize, ysize;
    State **cells;
} Field;

Field *createField(unsigned int xsize, unsigned int ysize);

void releaseField(Field *f);

void initField(Field *f, unsigned int n);

void printField(const Field *f);

void tick(Field *f);

int count_neighbours(Field *f, int yPos, int xPos);

#endif	/* AALTO_MINESWEEPER_H */

//Implement the function 'printField' that outputs the current state of the field 
//to the screen. Each dead cell is marked with '.' and each live cell is marked 
//with '*'. There are no spaces between the cells, and each row ends in a newline 
//('\n'), including the last line. The output should look similar, as in 
//the above examples in this task description.

