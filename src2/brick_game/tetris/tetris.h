#include "../../data/tetrominos.h"
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
typedef struct {
  int **field;
  Tetromino current;
  Tetromino next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;
void initGameInfo();
void userInput(UserAction_t action, bool hold);
void shift();
void move_top();
void move_bottom();
void move_left();
void move_right();

GameInfo_t updateCurrentState();
int check_collision(Tetromino t);
void rotate_tetromino();
void clear_lines();
void spawn_tetromino();
void lock_tetromino();
