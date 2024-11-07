#ifndef GLOBAL_H
#define GLOBAL_H

    extern int px; 
    extern int py;
    extern int c;
    extern int p_gold;
    extern int temp_gold;
    extern bool t_placed;
    extern bool p_placed;
    extern bool stairs_place;
    extern int r_placed;
    struct monsters
    {
        int y;
        int x;
        int hp;
    };
    struct time_table
    {
	int start_time;
	int temp_time;
    };
    extern struct monsters monster[];
    extern struct time_table time_table[];

#endif