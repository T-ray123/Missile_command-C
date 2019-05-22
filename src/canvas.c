/**
 * Layer used mainly for the sprites of the rockets,cleaning them and drawing.
 */

#include <stdlib.h>
#include "canvas.h"
#include "main.h"
#include "animate.h"

#include "collision_layer.h"
#include "alien_layer.h"
#include "input_layer.h"
#include "defense_layer.h"


static void draw(Canvas*, Coord*, chtype);


/*
 * Because animation is time-based, there is no guarentee
 * the garbage collector sprite will retrace the path exactly.
 * To compensate, it will also delete all the neighboring locations
 * as it travels.
*/
void clear_sprite(Canvas* canvas, Sprite* sprite) {
    if (sprite->view == ' ')
        return;

    Coord box[8];
    // Deleting a sprite causes all sorts of positioning issues
    // with active animations. Instead we replace them with an
    // invisible character.
    Sprite gc = { .view = ' ' };
    set_animation(&gc, &sprite->path.beg, &sprite->path.current, 1000);

    // Increment the endpoint one further.
    int dx = gc.path.end.x - gc.path.beg.x;
    int dy = gc.path.end.y - gc.path.beg.y;
    gc.path.end.x += (dx) ? dx / abs(dx) : 0;
    gc.path.end.y += (dy) ? dy / abs(dy) : 0;

    while (!is_animation_done(&gc)) {
        get_box(&gc.path.current, 1, box);
        for (int b = 0; b < 8; b++) {
            mvwaddch(canvas->window, box[b].y, box[b].x, gc.view);
        }

        update_animation(canvas, &gc);
        wrefresh(canvas->window);
    }
}


void draw_sprite(Canvas* canvas, Sprite* sprite) {
    draw(canvas, &sprite->path.current, sprite->view);
}

/*
 * Check if a canvas has a character at `coord`
*/
bool has_object(Canvas* canvas, Coord* coord) {
    char c = mvwinch(canvas->window, coord->y, coord->x);
    return (c != ERR && c != ' ');
}


static void draw(Canvas* canvas, Coord* point, chtype c) {
    mvwaddch(canvas->window, point->y, point->x, c);
}