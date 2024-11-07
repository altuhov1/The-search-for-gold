#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "global.h"
// \\ddfdfsfsffd
void waiting_tab(int rows, int cols);
	/*Drawing.c; Блок вывода вейтинга*/

void battle(int rows, int cols, char (*map)[cols], int dir_y, int dir_x);
	/*Game_mechanics.c; Маханика битвы с мобом */

void respawn(int rows, int cols, char (*map)[cols]);
	/*Space_creation.c;  Механика спвана мобов */

void location_creation (int rows, int cols, char (*map)[cols]);
	/*Space_creation.c; заполняем локацию материей, создеает жесткие стены*/

void room_creation(int rows, int cols, char (*map)[cols]);
	/*Space_creation.c; Создаем комнаты*/

void stairs(int rows, int cols, char (*map)[cols]);
	/*Space_creation.c; создаем телепорт*/

void drawing(int rows, int cols, char (*map)[cols]);
/*Drawing.c; Отрисовка всех текстурок*/

void move_person(int rows, int cols, char (*map)[cols]);
/*Console_work.c; Чтение ходов*/

void indicators(int rows, int cols, char (*map)[cols]);
/*Drawing.c; Отрисовка всех временных индикаторов*/

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
		respawn(rows, cols, map); //спавн перса и мобов
	}


	move_person(rows, cols, map); // чтение хода

	indicators(rows, cols, map);
}



int main(void)
{
	time_table[0].start_time = time(NULL);
    int cols, rows;
    initscr();

    noecho(); // не отображает сиволы, которые мы вводим
    curs_set(0); // отсутствие мигающей хрени для ввода
    keypad(stdscr, 1); // можно воодить фки и стрелки
    getmaxyx(stdscr, rows, cols);
    char map[rows][cols]; 



    do
    {
        dungeon(rows, cols, map); 

    }
    while ((c = getch()) != 27);

    getch();
    endwin();

    return 0;
}