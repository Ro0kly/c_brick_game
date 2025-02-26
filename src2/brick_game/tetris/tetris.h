#include "../../data/tetrominos.h"
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;
Tetromino getCurrent();
Tetromino makeTemp();
void userInput(UserAction_t action, bool hold);

// void draw_tetromino(int erase);
void move_top();
void move_bottom();
void move_left();
void move_right();

GameInfo_t updateCurrentState();
// void draw_field();
int check_collision(Tetromino t);
void rotate_tetromino();
void clear_lines();
void spawn_tetromino();
// void game_over();
void lock_tetromino();
int (*getField())[10];
