#ifndef CANVAS_H
#define CANVAS_H

#include <ncurses.h>
#include <time.h>

typedef struct 
{
	int x;
	int y;
} Coord;


typedef struct 
{
	Coord beg;
	Coord current;
	Coord end;
	double speed;
	long start_time;
} Vector; //using vector to store different parts of the struct

typedef struct 
{
    chtype view;
    Vector path;
    long keep_alive; // time before garbage collector gets to it
	bool alive;
} Sprite;


typedef struct {
    WINDOW* window;
    Sprite sprites[120];
} Canvas;


void clear_sprite(Canvas*, Sprite*);
void draw_sprite(Canvas*, Sprite*);
void update_sprite(Canvas*, Sprite*);
bool has_object(Canvas*, Coord*);

#endif
