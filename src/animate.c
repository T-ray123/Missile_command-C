#include <sys/time.h>
#include <stdlib.h>
#include <math.h>
#include "animate.h"


/*
 * Find the coordinate location of where the sprite should be
 * at the current point in time.
*/
void lerp(Vector* vec) {
    double dist = distance(&vec->beg, &vec->end);
    double total_time = dist / vec->speed; // How long the journey is going to take.
    double elapsed = (double) (get_time() - vec->start_time) / SECOND;
    double mult = elapsed / total_time;

    if (mult < 1) {
        Coord next = {
            .y = vec->beg.y + (vec->end.y - vec->beg.y) * mult,
            .x = vec->beg.x + (vec->end.x - vec->beg.x) * mult
        };
        vec->current = next;
    } else
        vec->current = vec->end;
}


/*
 * Return true if coordinates are equal, otherwise false.
*/
bool cmpcoord(Coord* c1, Coord* c2) {
    return (c1->y == c2->y && c1->x == c2->x);
}


double distance(Coord* c1, Coord* c2) {
    double dy = abs(c2->y - c1->y);
    double dx = abs(c2->x - c1->x);

    return hypot(dx, dy);
}

double slope(Coord* c1, Coord* c2) {
    double dx = (double) c2->x - c1->x;
    double dy = (double) c2->y - c1->y;

    return (dx) ? dy / dx : NAN;
}


/*
 * Convenience method.
 *
 * Set all the necessary fields for the sprite to be updated
 * by the primary animation loop.
*/
void set_animation(Sprite* sprite, Coord* start, Coord* end, int speed) {
    sprite->path.current = *start;
    sprite->path.beg = *start;
    sprite->path.end = *end;
    sprite->path.speed = speed;
    sprite->alive = true;
    sprite->path.start_time = get_time();
}


/*
 * Draw the character to the buffer, update position.
 * Delete sprites that are done with their animation, and have expired
 * past their `.keep_alive` time.
*/
void update_animation(Canvas* canvas, Sprite* sprite) {
    draw_sprite(canvas, sprite);

    if (!is_animation_done(sprite)) {
        lerp(&sprite->path);

    } else {
        long travel_time = (long int) distance(&sprite->path.beg, &sprite->path.end) / sprite->path.speed;
        long elapsed = get_time() - sprite->path.start_time;
        if (sprite->keep_alive < elapsed - travel_time) {
            sprite->alive = false;
            clear_sprite(canvas, sprite);
        }
    }
}

/*
 * Convenience method.
 * Check if the sprite is at its destination.
*/
bool is_animation_done(Sprite* sprite) {
    return (cmpcoord(&sprite->path.current, &sprite->path.end));
}

/*
 * Cross-platform solution for tracking time in milliseconds.
 *
 * Windows is more coarse than *nix, about 50ms.
*/
#if defined(_WIN32) || defined(WIN32) || defined(__CYGWIN32__)
#include <windows.h>
unsigned long get_time() {
    static LARGE_INTEGER freq, start;
    LARGE_INTEGER count;
    if (!QueryPerformanceCounter(&count))
        FatalError("QueryPerformanceCounter");
    if (!freq.QuadPart) { // one time initialization
        if (!QueryPerformanceFrequency(&freq))
            FatalError("QueryPerformanceFrequency");
        start = count;
    }
    double seconds = (double)(count.QuadPart - start.QuadPart) / freq.QuadPart;
    return seconds * SECOND;
}
#else
unsigned long get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (unsigned long) tv.tv_sec * SECOND + tv.tv_usec;
}
#endif
