#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "global.h"

void battle(int rows, int cols, char **map, int dir_y, int dir_x)
{    /* Маханика битвы с мобом */
	for (int m = 0; m<10; m++)
	{
		if (dir_y == monster[m].y && dir_x == monster[m].x)
		{
			if (monster[m].hp<= 0)
			{
				time_table.temp_time_gold = time(NULL) - time_table.start_time;  
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
void rand_move_mod(int rows, int cols, char **map)
{    /* Маханика двжижения мобов */
	for (int x = 0; x < cols; x++)
	{
		for (int y = 0; y < rows; y++)
		{
			if ((map[y][x] == 'G') && (map[y+1][x] == ' ') && (map[y-1][x] == ' ') && (map[y][x+1] == ' ') && (map[y][x-11] == ' '))
			{
				int temp_move = rand()% 10;
				switch(temp_move)
				{
					case(1):
					{
						map[y][x] = ' ';
						map[y + 1][x] = 'G';
						break;
					}
					case(2):
					{
						map[y][x] = ' ';
						map[y-1][x] = 'G';
						break;
					}
					case(3):
					{
						map[y][x] = ' ';
						map[y][x+1] = 'G';
						break;
					}
					case(4):
					{
						map[y][x] = ' ';
						map[y][x-1] = 'G';
						break;
					}
				}

			}
		}
	}

}
