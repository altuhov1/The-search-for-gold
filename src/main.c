#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <pthread.h>
#include "global.h"
// 
void waiting_tab(int rows, int cols);
	/*Drawing.c; Блок вывода вейтинга*/

void battle(int rows, int cols, char **map, int dir_y, int dir_x);
	/*Game_mechanics.c; Маханика битвы с мобом */

void respawn(int rows, int cols, char **map);
	/*Space_creation.c;  Механика спвана мобов */

void location_creation (int rows, int cols, char **map);
	/*Space_creation.c; заполняем локацию материей, создеает жесткие стены*/

void room_creation(int rows, int cols, char **map);
	/*Space_creation.c; Создаем комнаты*/

void stairs(int rows, int cols, char**map);
	/*Space_creation.c; создаем телепорт*/

void drawing(int rows, int cols, char **map);
/*Drawing.c; Отрисовка всех текстурок*/

void move_person(int rows, int cols, char **map);
/*Console_work.c; Чтение ходов*/

void indicators(int rows, int cols, char **map);
/*Drawing.c; Отрисовка всех временных индикаторов*/

void mode_select(int rows, int cols);
/*Mode_select.c; работа с выбором режима для игры*/

int basic_update_check(void);
/*console_work.c; автоматическое обновление слайдов*/

void rand_move_mod(int rows, int cols, char **map);
 /* game_mechanics.c; Маханика двжижения мобов */

void file_writing(void);
/* test.c; вывод переменной в файл*/


void dungeon(int rows, int cols, char **map)
/*Создаем дальше и дальше реализовывем главные механики*/
{ 
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
	time_table.start_time = time(NULL);
	time_table.basic_automatic_time = time(NULL) - time_table.start_time;

    int cols, rows;
    initscr();
	start_color();

    noecho(); // не отображает сиволы, которые мы вводим
    curs_set(0); // отсутствие мигающей хрени для ввода
    keypad(stdscr, 1); // можно воодить фки и стрелки
    getmaxyx(stdscr, rows, cols);
    // Динамически выделяем память под карту
    char **map = (char **)malloc(rows * sizeof(char *));
    if (map == NULL) {
        fprintf(stderr, "Ошибка выделения памяти для указателей на строки.\n");
        exit(EXIT_FAILURE);
    }

    // Выделение памяти для каждой строки
    for (int i = 0; i < rows; i++) {
        map[i] = (char *)malloc(cols * sizeof(char));
        if (map[i] == NULL) {
            fprintf(stderr, "Ошибка выделения памяти для строки %d.\n", i);
            exit(EXIT_FAILURE);
        }
    }


	mode_select(rows, cols);
    do
    {
        dungeon(rows, cols, map); 

    }
    while (((c = getch()) != 27)); //(basic_update_check() == 1)||

    for (int i = 0; i < rows; ++i) {
        free(map[i]);
    }
	free(map);

    endwin();
	file_writing();
    return 0;
}