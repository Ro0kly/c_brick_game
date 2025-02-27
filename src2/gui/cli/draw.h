#include "../../data/tetrominos.h"
#include <ncurses.h>
#include <unistd.h>
void draw_tetromino(Tetromino tetro);
void draw_next_tetromino(Tetromino tetro);
void draw_field(int **field);
void game_over();
void initNcurses();
