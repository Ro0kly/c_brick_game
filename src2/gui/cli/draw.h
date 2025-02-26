#include "../../data/tetrominos.h"
#include <ncurses.h>
#include <unistd.h>
void draw_tetromino(Tetromino tetro);
void draw_field(int (*field)[10]);
void game_over();
