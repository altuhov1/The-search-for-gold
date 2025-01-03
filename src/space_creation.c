#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "global.h"

void file_writing(void);
/* test.c; вывод переменной в файл*/


void respawn(int rows, int cols, char **map)
{	/* Механика спвана мобов */
	if (!t_placed)
	{
		int my, mx;
		for (int m = 0; m<10;  m++)
		{
			do
			{
				my = rand() % (rows-3);
				mx = rand() % (cols-1);
			} 
			while (map[my][mx] != ' ');
			monster[m].y = my;
			monster[m].x = mx;
			monster[m].hp = 2;
			map[monster[m].y][monster[m].x] = 'G';
		}
		t_placed = 1;
	}
	/* Механика спвана перса */
	if (!p_placed)
	{
		do
		{
			py = rand() % (rows-1);
			px = rand() % (cols-1);
		} 
		while (map[py][px] != ' ');
		p_placed = 1;
	}
}
void location_creation (int rows, int cols, char **map)
{
	/*заполняем локацию материей, создеает жесткие стены*/
	/*Тут же и создается декор, который внутри стен*/
	for (int y =  0;y <=(rows-1); y++)
	{				
		for (int x =  0;x <=(cols-1); x++)
		{
			if (y ==0 || x == 0 || x == cols -1 ||( y >= rows -3 && y <= rows ) )
				map[y][x] = 'X';      // стены
			else
			{
				if (rand() % 10 == 0) // булыга
				{
					map[y][x] ='.';
				}
				
				else if ((rand() % 140 == 0)&& (x !=0) && (map[y][x-1] == '#')) // руда
				{
					map[y][x] ='e';
					map[y][x-1] ='e';
				}
				else if ((rand() % 130 == 0)&& (x !=0) && (map[y][x-1] == '#')) // руда
				{
					map[y][x] ='g';
					map[y][x-1] ='g';
				}
				else
				{
					map[y][x] = '#';       // окружение, на которое нельзя заходить
				} 
			}

		}   
	}
}


void room_creation(int rows, int cols, char **map)
	/*Создаем комнаты*/
{
	int ry, rx;
	int r_size_y, r_size_x;
	int room_num = rand() % ((rows * cols) / 600) + 6;  // скок будет комнат rand() % 5 + 5
	int old_r_centr_y,old_r_centr_x;
	int r_centr_y, r_centr_x;
	bool collizion = 0;
	int fuse = 0; // предохренитель на случай плохой генеации 
	while(r_placed < room_num)
	{
		do
		{
		    collizion = 0;
			do         						// генерируем параметры комнат
			{
				fuse++;
				if (fuse > 500)
				{
					p_placed = 0;
					r_placed = 0;
					t_placed = 0;
					location_creation(rows, cols, map); //создание локации
					room_creation(rows, cols, map); // создание комнат
					return;
				}
				ry = rand() % (rows - 3);
				rx = rand() % (cols - 3);

				r_size_y = rand() % 3 + 3;  // размеры комнат
				r_size_x = rand() % 11 + 8;

			} 
			while ((ry + r_size_y > rows - 2) || (rx + r_size_x > cols - 2));
		
			if ((ry> 1) && (rx > 1))
			{
				for (int y =  ry ;y <= ry + r_size_y; y++)
				{
					for (int x =  rx;x <=rx + r_size_x; x++)         //Проверка на то, что рядом нет комнат
					{
						if (map[y][x] == ' ' || map[y+1][x] == ' ' || map[y-1][x] == ' '||
							map[y][x+1] == ' ' || map[y][x-1] == ' ')
							collizion = 1;
							
					}
				}
			}
			else collizion = 1;


		}
		while(collizion == 1);
		for (int y =  ry ;y <= ry + r_size_y; y++)
		{
			for (int x =  rx;x <=rx + r_size_x; x++)  //рисовка пустот
			{
				if (map[y][x] != 'X')
				{

				map[y][x] = ' ';
				
				}
					
			}

		}
		r_placed++;


		if (r_placed > 1) //коридоры 
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
				if ((y>0) && (y < rows) && (old_r_centr_x >0) && (old_r_centr_x < cols))
				{
					map[y][old_r_centr_x] = ' ';
					if (old_r_centr_y < r_centr_y)
						y++;
					else if (old_r_centr_y > r_centr_y)
						y--;
				}
			}

			for (int x = old_r_centr_x; x !=r_centr_x; )
			{
				if ((y>0) && (y < rows) && (x >0) && (x < cols))
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

} 
void stairs(int rows, int cols, char **map)
{	/*создаем телепорт*/
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
	return;
}
