#include <stdbool.h>

int px; // координаты персонажа по x 
int py; // координаты персонажа по y
int c = 0; // симвл,  который считывается с стандартного потока 
int p_gold = 0; // общее число золота у персонажа
int temp_gold = 0; // золото, которое было добыто за полседние 3 секнуды
bool t_placed = 0; // мобы
bool p_placed = 0; // персонаж
bool stairs_place = 0; // телепорт
int r_placed = 0; // комнаты
struct monsters
{
	int y;
	int x;
	int hp;
};
struct time_table
{
	int start_time;
	int temp_time_gold;
	double basic_automatic_time;
	double creep_delta;
};

struct monsters monster[10]; // все мобы
struct time_table time_table; // тип массива лоя работы с врменем и тд

int test = 0; // переменная для проверок