#include <ncurses.h>
#include <stdbool.h>
#include <time.h>
#include "global.h"

void waiting_tab(int rows, int cols);
/*drawing.c*/
void battle(int rows, int cols, char (*map)[cols], int dir_y, int dir_x);
/*game_mechanics.c*/
void drawing(int rows, int cols, char (*map)[cols]);
/*drawing.c*/
void move_person(int rows, int cols, char (*map)[cols])
/*Чтение ходов*/
{
	int dir_y = py, dir_x = px;
	bool move_p = 0;
	bool check_teleport =0;

	if (c == KEY_UP) dir_y--;
	else if (c == KEY_DOWN) dir_y++;
	else if (c == KEY_LEFT) dir_x--;
	else if (c == KEY_RIGHT) dir_x++;
	else if ((c == '\n')&& (map[py][px] == '^')) move_p = 1; // ((c == '\n')&& (map[py][px] == '^'))

	if (move_p == 1)
	{
		p_placed = 0;
		stairs_place = 0;
		r_placed = 0;
		t_placed = 0;
		c = 0;
		waiting_tab(rows, cols);
		check_teleport = 1;
	}
	else if (map[dir_y][dir_x] == ' ')
	{
		py = dir_y;
		px = dir_x;
	}
	else if ((map[dir_y][dir_x] == '[') || (map[dir_y][dir_x] == ']')|| (map[dir_y][dir_x] == '^'))
	{
		py = dir_y;
		px = dir_x;
	}
	else 
	{
		battle(rows, cols, map, dir_y, dir_x);
	}
	if (!check_teleport) drawing(rows, cols, map);

}

int delta_time(void)
/*Проверка на то, сколько будет весеть по времени сообщение */
/*Пока в завсисмости с функцией индикаторы в drawing.c*/
{
    time_t mytime_1 = time_table[0].temp_time;
    time_t mytime_2 = time(NULL);
    int res = (int)mytime_2 - (int)mytime_1;
	if (res < 3)
	{
		return 1;
	}
    return 0;
}