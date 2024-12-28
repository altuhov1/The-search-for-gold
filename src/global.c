#include <stdbool.h>

int px; 
int py;
int c = 0;
int p_gold = 0;
int temp_gold = 0;
bool t_placed = 0;
bool p_placed = 0;
bool stairs_place = 0;
int r_placed = 0;
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

struct monsters monster[10];
struct time_table time_table;
