#include <stdio.h>
#include <stdlib.h>
#include "ships.h"

const unsigned int xsize = 10;
const unsigned int ysize = 10;
const unsigned int shiplen = 3;

/* implement these functions */

/* Task a: Place <num> ships on the game map.
 */
void set_ships(unsigned int num)
{
    (void) num;
    for (unsigned int i = 0; i < num; i++) {
        int xp = rand() % 10;
        int yp = rand() % 10;
        int dir = rand() % 2;
        int ret = place_ship(xp, yp, dir);
        if (ret != 1) {
            i--;
        }
    }
}


/* Task b: print the game field
 */
void print_field(void)
{
    for (unsigned int y = 0; y < ysize; y++) {
        for (unsigned int x = 0; x < ysize; x++) {
            int ret_1 = is_visible(x,y);
            if (ret_1 == 0) {
                printf("?");
            }
            else if (ret_1 == 1) {
                char s = is_ship(x,y);
                printf("%c", s);
            }
        }
        printf("\n");
    }
}

/* Task c: Ask coordinates (two integers) from user, and shoot the location.
 * Returns -1 if user gave invalid input or coordinates, 0 if there was no ship
 * at the given location; and 1 if there was a ship hit at the location.
 */
int shoot(void)
{
    printf("Enter two numbers");
    unsigned int x;
    unsigned int y;
    int ret_1 = scanf("%u %u", &x, &y);
    if (ret_1 != 2) {
        return -1;
    }
    if (x >= xsize || y >= ysize) {
        return -1;
    }
    char ret_2 = is_ship(x,y);
    if (ret_2 == '.') {
        checked(x,y);
        return 0;
    }
    else if (ret_2 == '+') {
        checked(x,y);
        hit_ship(x,y);
        return 1;
    }
    return 0;
}

/* Task d: Returns 1 if game is over (all ships are sunk), or 0 if there
 * still are locations that have not yet been hit. <num> is the number of
 * ships on the game map. It is assumed to be the same as in the call to
 * set_ships function.
 */
int game_over(unsigned int num)
{
    (void) num;
    int count = 0;
    int target = num * shiplen;
    for (unsigned int x = 0; x < xsize; x++) {
        for (unsigned int y = 0; y < ysize; y++) {
            char ret_1 = is_ship(x,y);
            if (ret_1 == '#') {
                count ++;
            }
        }
    }
    if (count == target) {
        return 1;
    }
    return 0;
}
