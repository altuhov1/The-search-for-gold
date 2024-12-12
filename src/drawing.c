#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "global.h"



int delta_time(void);
/*console_work.c*/

void cleaning(int rows, int cols)
{
	for (int y=0; y<= rows-1; y++)
	{
		for (int x=0; x<= cols-1; x++)
		{
			mvprintw(y, x, " ");
		}
	}
}

void waiting_tab(int rows, int cols)
{
	/*Блок вывода вейтинга*/
	cleaning(rows, cols);
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
		mvprintw(countery+((rows/9)*3), ((cols/11)*3), "%c", waiting[counterx]);
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
	mvprintw(countery+((rows/9)*3) + 2, ((cols/9)*3) + 12,"Press something to continue...");
}

void drawing(int rows, int cols, char (*map)[cols])
/*Отрисовка всех текстурок*/
{
	init_pair(1, 244, 244); // стены #
	init_pair(2, 234, 234); // стены бедрок - X
	init_pair(3, 173, 0); // телепорт - [^]
	init_pair(4, 152, 0); // иконка игрока - @
	init_pair(5, 237, 244); // камни - .
	init_pair(6, 47, 242); // руда - e (эмиральды)
	init_pair(7, 178, 242); // руда - g
	init_pair(8, 34, 0); // руда - G (гоблины)
	init_pair(9, 0, 236); // темнота проходы 
	init_pair(10, 0, 238); // темнота стены

	cleaning(rows, cols);

   	for (int y =  0;y <=(rows-1); y++)
    {
        for (int x =  0;x <=(cols-1); x++)
        {
			if ((px - x)*(px - x)/5
			 +(py - y)*(py - y) < 49) //<-------------------радиус
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
				else if (map[y][x] == ' ')
					mvaddch(y, x, ' ');
				else
				{
					attron(COLOR_PAIR(1));      // #
					mvaddch(y, x, ' ');
					attroff(COLOR_PAIR(1));
				}
			}
			else if (((map[y][x] == ' ') || (map[y][x] == 'G')||(map[y][x] == '[') ||(map[y][x] == '^') || (map[y][x] == ']')))
			{
				attron(COLOR_PAIR(9));
				mvaddch(y, x, ' ');
				attroff(COLOR_PAIR(9));
			}
			else
			{
				attron(COLOR_PAIR(10));
				mvaddch(y, x, ' ');
				attroff(COLOR_PAIR(10));				
			}
			if (y > rows -3) //отступ !!!! <-------------------
				mvaddch(y, x, ' ');
			else if (map[y][x] == 'X')
			{
				attron(COLOR_PAIR(2));
				mvaddch(y, x, ' ');
				attroff(COLOR_PAIR(2));
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

void start_menu(int rows, int cols)
{
	init_pair(1, 196, 238); // буквы хело плеер
	init_pair(2, 52, 52); // обрамление, цвет
	init_pair(3, 238, 238); // фон база
    char hello_player[] =
    {
    "  . .       . .       .         .         . .          . .       .         . .       .   .    . .       . .\n\
.+'| |`+. .+'|=|`+. .+'|      .+'|      .+'|=|`+.    .+'|=|`+. .+'|      .+'|=|`+. .+'|.+'| .+'|=|`+. .+'|=|`+.\n\
|  | |  | |  | `+.| |  |      |  |      |  | |  |    |  | |  | |  |      |  | |  | |  ||  | |  | `+.| |  | |  | \n\
|  |=|  | |  |=|`.  |  |      |  |      |  | |  |    |  |=`++' |  |      |  |=|  | `+.`'.+' |  |=|`.  |  |'. '. \n\
|  | |  | |  | `.|  |  |      |  |      |  | |  |    |  |      |  |      |  | |  |   |  |   |  | `.|  |  | |  | \n\
|  | |  | |  |    . |  |    . |  |    . |  | |  |    |  |      |  |    . |  | |  |   |  |   |  |    . |  | |  | \n\
|  | |  | |  | .+'| |  | .+'| |  | .+'| |  | |  |    |  |      |  | .+'| |  | |  |   |  |   |  | .+'| |  | |  | \n\
`+.| |..| `+.|=|.+' `+.|=|.+' `+.|=|.+' `+.|=|.+'    `+.|      `+.|=|.+' `+.| |..|   |.+'   `+.|=|.+' `+.| |.+' \n"
    };
	for ( int i = 0;i< rows; i++)
	{
		for (int j = 0;j < cols; j++)
		{
			if ((i == 0) || (j == 0) ||( i == rows - 1) || (j == cols - 1))
			{
				attron(COLOR_PAIR(2));
				mvaddch(i, j, ' ');
				attroff(COLOR_PAIR(2));
			}
			else
			{
				attron(COLOR_PAIR(3));
				mvaddch(i, j, ' ');
				attroff(COLOR_PAIR(3));
			}
		}
	}

    int counterx = 0, countery = 0;
	attron(COLOR_PAIR(1));
	while (countery<8)
	{
		mvprintw(countery+ 1, 5, "%c", hello_player[counterx]);
		counterx++;

		while (hello_player[counterx] !='\n')
		{
			printw("%c", hello_player[counterx]);
			counterx++;
		}
		if (hello_player[counterx] == '\n')
		{
			counterx++;
			countery++;
		}
	}
    attroff(COLOR_PAIR(1));


    getch();
}