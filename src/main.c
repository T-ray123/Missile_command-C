#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <menu.h>
#include <ncurses.h>
#include "main.h"
#include "main_menu.h"
#include "canvas.h"
#include "input_layer.h"
#include "alien_layer.h"
#include "defense_layer.h"
#include "collision_layer.h"
#include "ui_layer.h"

//Animation loop is running
bool running = true;
//Game is lost.
bool lost = false

/**
 * Canvases responsible for the drawing part
 */
static Canvas* layers[]
{
    &INPUT_CANVAS,
    &ALIEN_CANVAS,
    &DEFENSE_CANVAS,
    $COLLISION_CANVAS,
};

//static void because it is specific for this class as an instance
static void init();
static void start_round();
static void reset_round();
static void start_game();

int main()
{
    init();
	// main_menu returns false if `Exit` is selected.
    //while function for main menu is executed, start the game
	while (main_menu()) 
    {
		start_game();
	}
	endwin();
	return 0; //success
}

static void init()
{
    srand(time(NULL)) //srand for random seed
    initscr(); //init the screen/window
    noecho(); //Don't echo input
    start_color(); // Enable colored formatting.
	curs_set(0); // Invisible cursor

}


	// Run the setup required for all other layers.
	init_input();
	init_alien();
	init_defense();
	init_collision();
	init_display();
}


// Reset any previous game data, start the game animation loop.
static void start_game() 
{
	clear_game();

	lost = false;
	while (true) 
	{
		start_round();
		if (lost) break;

		reset_round();
	}
}


/*
 * The primary animation loop.
 *
 * Loops over each layer, passing the index `i` for
 * context. Each layer will update its sprite at location `i`,
 * then any animations that need to be updated are drawn.
 * Finally all the windows are refreshed, displaying the new
 * frame.
*/
void update() 
{
	for (int i = 0; i < 120; i++) 
	{
		update_display();
		update_input(i);
		update_alien(i);
		update_defense(i);

		for (int l = 0; l < 4; l++)
		 {
			Canvas* layer = layers[l];
			Sprite* sprite = &layer->sprites[i];

			if (sprite->alive) {
				update_animation(layer, sprite);
			}
		}
	}
     //refresh of window
	wrefresh(DISPLAY);
	wrefresh(COLLISION_CANVAS.window);
	wrefresh(INPUT_CANVAS.window);
	wrefresh(ALIEN_CANVAS.window);
	wrefresh(DEFENSE_CANVAS.window);
	refresh();

	// No more missiles to send.
	if (is_alien_done()) {
		running = false;
	}
}


static void start_round()
{
	running = true;
	while (running) 
	{
		update();
	}
}


static void reset_round()
 {
	increment_round();
	clear_game();
}

/*
 * Make sure all the sprites are disabled,
 * and clear all of the windows.
*/
void clear_game() 
{
	wclear(DISPLAY);
	for (int i = 0; i < 120; i++)
     {
		for (int l = 0; l < 4; l++) 
        {
			Canvas* layer = layers[l];
			layer->sprites[i].alive = false;
			wclear(layer->window);
		}
	}
	clear();
	refresh();

	reset_alien();
    reset_defense();
	reset_ui();
}
 //void function for end of the game

void lose_game()
 {
	lost = true;
	running = false;
}