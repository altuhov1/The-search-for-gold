#include <ncurses.h>
#include <stdlib.h>
#include "global.h"

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

   	for (int y =  0;y <=(rows-1); y++)
    {
        for (int x =  0;x <=(cols-1); x++)
        {
			if (y == rows -1)
				mvaddch(y, x, ' ');
			else if (map[y][x] == '^')
				mvaddch(y, x, '^');
			else if (map[y][x] == '[')
				mvaddch(y, x, '[');
			else if (map[y][x] == ']')
				mvaddch(y, x, ']');
			else if (map[y][x] == 'G')
				mvaddch(y, x, 'G');
			else if (map[y][x] == 'X')
				mvaddch(y, x, 'X');
			else if (map[y][x] == ' ')
				mvaddch(y, x, ' ');
			else
				mvaddch(y, x, '#');

        }   
    }
	mvaddch(py, px, '@');
}

void indicators(int rows, int cols, char (*map)[cols])
{
	mvprintw(rows-1, 0,"Gold: %d ", p_gold); 
}