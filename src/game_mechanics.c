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
				time_table[0].temp_time = time(NULL);
				map[dir_y][dir_x] = ' ';
				temp_gold = rand()% 10 + 1;
				p_gold+= temp_gold;
			}
			else
				monster[m].hp -=1;
			break;
		}
	}

}

