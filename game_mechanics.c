#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "global.h"

void battle(int rows, int cols, char (*map)[cols], int dir_y, int dir_x)
{    /* Маханика битвы с мобом */
	for (int m = 0; m<10; m++)
	{
		if (dir_y == monster[m].y && dir_x == monster[m].x)
		{
			if (monster[m].hp<= 0)
			{
				map[dir_y][dir_x] = ' ';
				p_gold+= rand()% 10 + 1;
			}
			else
				monster[m].hp -=1;
			break;
		}
	}

}

