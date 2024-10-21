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

void respawn(int rows, int cols, char (*map)[cols])
{	/* Механика спвана мобов */
	if (!t_placed)
	{
		int my, mx;
		for (int m = 0; m<10;  m++)
		{
			do
			{
				my = rand() % rows;
				mx = rand() % cols;
			} 
			while (map[my][mx] != ' ');
			monster[m].y = my;
			monster[m].x = mx;
			monster[m].hp = 2;
			map[monster[m].y][monster[m].x] = 'G';
		}
		t_placed = 1;
	}

	if (!p_placed)
	{
		do
		{
			py = rand() % rows;
			px = rand() % cols;
		} 
		while (map[py][px] == '#'|| map[py][px] == 'X');
		p_placed = 1;
	}
}