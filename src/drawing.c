#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "global.h"


int delta_time(void);
/*console_work.c*/
void waiting_tab(int rows, int cols)
{
	/*Блок вывода вейтинга*/
	for (int y=0; y<= rows-1; y++)
	{
		for (int x=0; x<= cols-1; x++)
		{
			mvprintw(y, x, " ");
		}
	}
	char waiting[]=
	{
		"    _  _ #       # _ #       # _ #       #       #\n\
(_)(_)(_)#       #(_)#   _   #(_)#       #       #\n\
 _  _  _ # _____ # _ # _| |_ # _ # ____  #  ____ #\n\
| || || |#(____ |#| |#(_   _)#| |#|  _ \\ # / _  |#\n\
| || || |#/ ___ |#| |#  | |_ #| |#| | | |#( (_| |#\n\
 \\_____/ #\\_____|#|_|#   \\__)#|_|#|_| |_|# \\___ |#\n\
    ##       ##   ##       ##   ##       ##(_____|##\n"
	};
	int counterx = 0, countery = 0;
	while (countery<7)
	{
		mvprintw(countery+((rows/10)*3), ((cols/12)*3), "%c", waiting[counterx]);
		counterx++;

		while (waiting[counterx] !='\n')
		{
			printw("%c", waiting[counterx]);
			counterx++;
		}
		if (waiting[counterx] == '\n')
		{
			counterx++;
			countery++;
		}
	}
	mvprintw(countery+((rows/10)*3) + 2, ((cols/12)*3)+12,"Press something to continue");
}

void drawing(int rows, int cols, char (*map)[cols])
/*Отрисовка всех текстурок*/
{
	init_pair(1, 244, 244); // стены - #
	init_pair(2, 234, 234); // стены бедрок - X
	init_pair(3, 173, 0); // телепорт - [^]
	init_pair(4, 152, 0); // иконка игрока - @
	init_pair(5, 30, 244); // камни - .
	init_pair(6, 47, 242); // руда - e (эмиральды)
	init_pair(7, 178, 242); // руда - g
	init_pair(8, 34, 0); // руда - G (гоблины)
   	for (int y =  0;y <=(rows-1); y++)
    {
        for (int x =  0;x <=(cols-1); x++)
        {
			if (y > rows -3) //отступ !!!! <-------------------
				mvaddch(y, x, ' ');
			else if (map[y][x] == '^')
			{
				attron(COLOR_PAIR(3));
				mvaddch(y, x, '^');
				attroff(COLOR_PAIR(3));
				
			}
			else if (map[y][x] == '[')
			{
				attron(COLOR_PAIR(3));
				mvaddch(y, x, '[');
				attroff(COLOR_PAIR(3));
			}
			else if (map[y][x] == '.')
			{
				attron(COLOR_PAIR(5));
				mvaddch(y, x, '.');
				attroff(COLOR_PAIR(5));
			}
			else if (map[y][x] == 'e')
			{
				attron(COLOR_PAIR(6));
				mvaddch(y, x, ':');
				attroff(COLOR_PAIR(6));
			}
			else if (map[y][x] == 'g')
			{
				attron(COLOR_PAIR(7));
				mvaddch(y, x, ':');
				attroff(COLOR_PAIR(7));
			}
			else if (map[y][x] == ']')
			{
				attron(COLOR_PAIR(3));
				mvaddch(y, x, ']');
				attroff(COLOR_PAIR(3));
			}
			else if (map[y][x] == 'G')
			{
				attron(COLOR_PAIR(8));
				mvaddch(y, x, 'G');
				attroff(COLOR_PAIR(8));
			}
			else if (map[y][x] == 'X')
			{
				attron(COLOR_PAIR(2));
				mvaddch(y, x, ' ');
				attroff(COLOR_PAIR(2));
			}
			else if (map[y][x] == ' ')
				mvaddch(y, x, ' ');
			else
			{
				attron(COLOR_PAIR(1));      // #
				mvaddch(y, x, ' ');
				attroff(COLOR_PAIR(1));
			}

        }   
    }
	attron(COLOR_PAIR(4));
	mvaddch(py, px, '@');
	attroff(COLOR_PAIR(4));
}

void indicators(int rows, int cols, char (*map)[cols])
/*Ссылается на main.c. Занимается отрисовкой разных знаяений (по типу золота и тд)*/
{
	if (delta_time() == 1)
	{
		mvprintw(rows-1, 0,"Gold: %d, you got %d gold for killing a goblin.", p_gold, temp_gold); 
	}
	mvprintw(rows-1, 0,"Gold: %d ", p_gold); 
}