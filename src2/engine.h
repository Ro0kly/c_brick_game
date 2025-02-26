#include "pieces.h"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define WIDTH 10
#define HEIGHT 8
#define TETROMINO_SIZE 4

typedef struct {
  int x, y;     // Position of the tetromino
  int type;     // Type of tetromino (0-6)
  int rotation; // Current rotation (0-3)
} Tetromino;

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

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

void move_top();
void move_bottom();
void move_left();
void move_right();

GameInfo_t updateCurrentState();
void draw_field();
void draw_tetromino(int erase);
int check_collision(Tetromino t);
void rotate_tetromino();
void clear_lines();
void spawn_tetromino();
void game_over();
void lock_tetromino();
