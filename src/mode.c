#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "global.h"

void start_menu(int rows, int cols);

void mode_select(int rows, int cols)
{
    start_menu(rows, cols);
    return;
}