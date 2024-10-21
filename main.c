#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "global.h"


void waiting_tab(int rows, int cols);

void battle(int rows, int cols, char (*map)[cols], int dir_y, int dir_x);

void respawn(int rows, int cols, char (*map)[cols]);

void location_creation (int rows, int cols, char (*map)[cols])
{
	/*заполняем локацию материей, создеает жесткие стены*/
	for (int y =  0;y <=(rows-1); y++)
	{				
		for (int x =  0;x <=(cols-1); x++)
		{
			if (y ==0 || y == rows -2 || x == 0 || x == cols -1 || y == rows -1 )
				map[y][x] = 'X';      // стены
			else
				map[y][x] = '#';       // окружение, на которое нельзя заходить

		}   
	}
}
void room_creation(int rows, int cols, char (*map)[cols])
	/*Создаем комнаты*/
{
	int ry, rx;
	int r_size_y, r_size_x;
	int room_num = rand() % 5 + 5;  // скок будет комнат rand() % 5 + 5
	int old_r_centr_y,old_r_centr_x;
	int r_centr_y, r_centr_x;
	bool collizion = 0;
	while(r_placed < room_num)
	{
		do
		{
		    collizion = 0;
			do         						// генерируем параметры комнат
			{
				ry = rand() % (rows - 3);
				rx = rand() % (cols - 3);
				r_size_y = rand() % 4 + 3;  // размеры комнат
				r_size_x = rand() % 13 + 7;

			} 
			while ((ry + r_size_y > rows - 2) || (rx + r_size_x > cols - 1));

			for (int y =  ry ;y <= ry + r_size_y; y++)
			{
				for (int x =  rx;x <=rx + r_size_x; x++)         //Проверка на то, что рядом нет комнат
				{
					if (map[y][x] == ' ' || map[y+1][x] == ' ' || map[y-2][x] == ' '||
					    map[y][x+2] == ' ' || map[y][x-2] == ' ')
						collizion = 1;
						
				}
			}
		}
		while(collizion == 1);
		for (int y =  ry ;y <= ry + r_size_y; y++)
		{
			for (int x =  rx;x <=rx + r_size_x; x++)  //Отрисовка пустот
			{
				if (map[y][x] != 'X')
				{
				map[y][x] = ' ';
				}
					
			}

		}
		r_placed++;


		if (r_placed > 1)
		{
			old_r_centr_y = r_centr_y;
			old_r_centr_x = r_centr_x;
		}
		r_centr_y = ry + (r_size_y / 2);
		r_centr_x = rx + (r_size_x / 2);

		if (r_placed > 1)
		{
			int y;
			for (y = old_r_centr_y; y !=r_centr_y; )
			{
				map[y][old_r_centr_x] = ' ';
				if (old_r_centr_y < r_centr_y)
					y++;
				else if (old_r_centr_y > r_centr_y)
					y--;
			}

			for (int x = old_r_centr_x; x !=r_centr_x; )
			{
				map[y][x] = ' ';
				if (old_r_centr_x < r_centr_x)
					x++;
				else if (old_r_centr_x > r_centr_x)
					x--;
			}
		}
	}

} 
void stairs(int rows, int cols, char (*map)[cols])
{
	int st_y, st_x;
	do 
	{
		st_y = rand() % (rows - 3);
		st_x = rand() % (cols - 3);

		if (map[st_y][st_x]==' ' && map[st_y+1][st_x]==' ' && map[st_y-1][st_x]==' '
		&& map[st_y][st_x-1]==' ' && map[st_y][st_x+1]==' ')
		{
			map[st_y][st_x]= '^';
			map[st_y][st_x+1]= ']';
			map[st_y][st_x-1]= '[';
			stairs_place = 1;	
		}


	}
	while(stairs_place == 0);
}
void drawing(int rows, int cols, char (*map)[cols]);

bool Reading_a_move(int rows, int cols, char (*map)[cols])
/*Чтение ходов*/
{
	int dir_y = py, dir_x = px;
	bool move_p = 0;

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
		return 1;
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
	return 0;
}

void dungeon(int rows, int cols, char (*map)[cols])
/*Создаем данжен*/
{ 
	bool check_teleport =0;
	srand(time(NULL));
	if (r_placed == 0)
	{
		location_creation(rows, cols, map); //создание локации
		room_creation(rows, cols, map); // создание комнат
		stairs(rows, cols, map); // создание телепорта
	}

	respawn(rows, cols, map); //спавн перса и мобов

	if (c != 0)
	{
		check_teleport = Reading_a_move(rows, cols, map); // чтение хода
	}
	if (check_teleport ==0)
		drawing(rows, cols, map); // отрисовка 
	

    mvaddch(py, px, '@');

	mvprintw(rows-1, 0,"Gold: %d ", p_gold); // Пираты платят золотом!!!
}



int main(void)
{
    int cols, rows;
    initscr();

    noecho(); // не отображает сиволы, которые мы вводим
    curs_set(0); // отсутствие мигающей хрени для ввода
    keypad(stdscr, 1); // можно воодить фки и стрелки
    getmaxyx(stdscr, rows, cols);
    char map[rows][cols];  //  rows - 11 - y, cols - 110 - x



    do
    {
        dungeon(rows, cols, map); 

    }
    while ((c = getch()) != 27);

    getch();
    endwin();

    return 0;
}