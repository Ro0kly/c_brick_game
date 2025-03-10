#include "../../model/tetrominos.h"
#include <ncurses.h>
#include <unistd.h>
void draw_welcome_title();
void draw_tetromino(Tetromino tetro);
void draw_next_tetromino(Tetromino tetro);
void draw_field(int **field);
void draw_info_panel(int score, int max_score, int level, char *speed);
void draw_instruction();
void draw_game_over();
void initNcurses();
