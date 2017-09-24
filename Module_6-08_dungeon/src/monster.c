/* monster.c -- Implementation of monster actions
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "dungeon.h"

// for defining some monster types below that can be used in the game
typedef struct {
    char name[20];  // Name of monster
    char sign;  // character to show it on map
    unsigned int hplow;  // lowest possible initial maxhp
    unsigned int hphigh;  // highest possible initial maxhp
} MonstType;

// Specifying three monster types to start with.
// Feel free to add more, or change the below
// Note that it is up to you to decide whether to use this array from createMonsters
// you may or may not use it
const MonstType types[] = {
    { "Goblin", 'G', 6, 10},
    { "Rat", 'R', 3, 5},
    { "Dragon", 'D', 15, 20}
};


/* One kind of attack done by monster.
 * The attack function pointer can refer to this.
 * 
 * Parameters:
 * game: the game state
 * monst: The monster performing attack
 */
void attackPunch(Game *game, Creature *monst) {
    printf("%s punches you! ", monst->name);
    int hitprob = 50;
    int maxdam = 4;
    if (rand() % 100 < hitprob) {
        printf("Hit! ");
        int dam = rand() % maxdam + 1;
        printf("Damage: %d ", dam);
        game->hp = game->hp - dam;
        if (game->hp <= 0)
            printf("You died!");
        printf("\n");
    } else {
        printf("Miss!\n");
    }
}

int is_player(Game *game, int x, int y)
{
	if (game->position.x == x && game->position.y == y)
		return 1;
	return 0;
}

int is_monster_movable(Game *game, int x, int y)
{
	if (isBlocked(game, x, y) || is_player(game, x, y))
		return 0;
	return 1;
}

double distance(int x1, int x2,int y1,int y2)
{
	return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}
/* Exercise (c)
 *
 * Move monster 'monst' towards the player character.
 * See exercise description for more detailed rules.
 */
void moveTowards(Game *game, Creature *monst) {
	
    //Get monster's position
    //Get player's position
    
    
    //If possible, the distance between monster and the character must reduce as a result of this call

    //The monster must not move more than one step on the map at a time

    //The monster must not move over wall

    //The monster must not move to same location with another monster

    //The monster must not move to same location with the character
    
    int x = monst->pos.x, y = monst->pos.y;
	int px = game->position.x, py = game->position.y;
	double potential_dists[5] = {
		distance(x,px,y,py),
		distance(x-1,px,y,py),
		distance(x+1,px,y,py),
		distance(x,px,y-1,py),
		distance(x,px,y+1,py)
	};
	int min = -1;
	for (unsigned i = 0; i < 5; i++)
	{
		if (min == -1 || potential_dists[min] >= potential_dists[i])
		{
			switch (i)
			{
				case 0:
					if (!is_monster_movable(game, x, y))
						continue;
					break;
				case 1:
					if (!is_monster_movable(game, x-1, y))
						continue;
					break;
				case 2:
					if (!is_monster_movable(game, x+1, y))
						continue;
					break;
				case 3:
					if (!is_monster_movable(game, x, y-1))
						continue;
					break;
				case 4:
					if (!is_monster_movable(game, x, y+1))
						continue;
					break;
			}
			min = i;

		}
	}
	switch (min)
	{
		case 0:
			break;
		case 1:
			monst->pos.x-=1;
			break;
		case 2:
			monst->pos.x+=1;
			break;
		case 3:
			monst->pos.y-=1;
			break;
		case 4:
			monst->pos.y+=1;
			break;
	}
}

/* Exercise (d)
 *
 * Move monster 'monst' away from the player character.
 * See exercise description for more detailed rules.
 */
void moveAway(Game *game, Creature *monst) {
	
    //If possible, the distance between monster and the character must increase as a result of this call

    //The monster must not move more than one step on the map at a time

    //The monster must not move over wall

    //The monster must not move to same location with another monster

    //The monster must not move to same location with the character
    
    int x = monst->pos.x, y = monst->pos.y;
	int px = game->position.x, py = game->position.y;
	double potential_dists[5] = {
            distance(x,px,y,py),
            distance(x-1,px,y,py),
            distance(x+1,px,y,py),
            distance(x,px,y-1,py),
            distance(x,px,y+1,py)
	};
	int max = -1;
	for (unsigned i = 0; i < 5; i++) {
            if (max == -1 || potential_dists[max] < potential_dists[i]) {
                switch (i)
                {
                        case 0:
                                if (!is_monster_movable(game, x, y))
                                        continue;
                                break;
                        case 1:
                                if (!is_monster_movable(game, x-1, y))
                                        continue;
                                break;
                        case 2:
                                if (!is_monster_movable(game, x+1, y))
                                        continue;
                                break;
                        case 3:
                                if (!is_monster_movable(game, x, y-1))
                                        continue;
                                break;
                        case 4:
                                if (!is_monster_movable(game, x, y+1))
                                        continue;
                                break;
            }
            max = i;
            }
	}
	switch (max) {
            case 0:
                    break;
            case 1:
                    monst->pos.x-=1;
                    break;
            case 2:
                    monst->pos.x+=1;
                    break;
            case 3:
                    monst->pos.y-=1;
                    break;
            case 4:
                    monst->pos.y+=1;
                    break;
	}
}


/* Exercise (e)
 *
 * Take action on each monster (that is alive) in 'monsters' array.
 * Each monster either attacks or moves (or does nothing if no action is specified)
 */
void monsterAction(Game *game) {
    for (unsigned i = 0; i < game->numMonsters; i++) {
        int x = game->monsters[i].pos.x, y = game->monsters[i].pos.y;
        if (is_player(game, x+1, y) || is_player(game, x-1, y) || is_player(game, x, y+1) || is_player(game, x, y-1)) {
            game->monsters[i].attack(game, &game->monsters[i]);
        }     
        else {
            game->monsters[i].move(game, &game->monsters[i]);
        }     
    }
}


/* Exercise (b)
 *
 * Create opts.numMonsters monsters and position them on valid position
 * in the the game map. The monster data (hitpoints, name, map sign) should be
 * set appropriately (see exercise instructions) 
 */
void createMonsters(Game *game) {
	
    const Options *opt = &game->opts;
    
    for (unsigned int i = 0; i < opt->numMonsters; i++) {
        unsigned int r = rand() % 3;
        game->monsters = realloc(game->monsters, sizeof(Creature) * (game->numMonsters + 1));
        Creature* monst = &game->monsters[i];
        strcpy(monst->name, types[r].name);
        monst->sign = types[r].sign;
        monst->hp = types[r].hphigh;
        monst->maxhp = types[r].hphigh;
        Point monst_pos;
        do {
            monst_pos.x = rand() % opt->mapWidth;
            monst_pos.y = rand() % opt->mapHeight;
        } while (isBlocked(game, monst_pos.x, monst_pos.y));
        monst->pos = monst_pos;
        monst->attack = attackPunch;
        monst->move = moveTowards;
        game->numMonsters++;
    }
}

/* Determine whether monster moves towards or away from player character.
 */
void checkIntent(Game *game)
{
    for (unsigned int i = 0; i < game->numMonsters; i++) {
        Creature *m = &game->monsters[i];
        if (m->hp <= 2) {
            m->move = moveAway;
        } else {
            m->move = moveTowards;
        }
        if (m->hp < m->maxhp)
            m->hp = m->hp + 0.1;  // heals a bit every turn
    }
}
