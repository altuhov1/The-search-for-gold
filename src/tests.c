#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "global.h"

void file_writing(void)
{
    // файл чтения
    char * filename = "./data/data.txt";
    // буфер для считавания данных из файла
  
    FILE *fp = fopen(filename, "w");
    if(fp)
    {
        char *strTest = malloc(sizeof(char) * 5); // Выделение памяти для строки
        fprintf(fp, "%d\n", test);           // Вывод строки
        free(strTest); 
        fclose(fp);
    }
}