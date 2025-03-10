#include "../../model/tetrominos.h"
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
  int terminate;
  int over;
} GameInfo_t;

void initGameInfo();
void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();
void game_over();

void spawn_tetromino();
void shift();
void move_top();
void move_bottom();
void move_left();
void move_right();
int rotate_tetromino();
void change_position_of_current_to(int y, int x);
void change_tetromino_type(int type);
void change_tetromino_rotation(int rotation);

int getPauseStatus();
int getTerminateStatus();
int getOverStatus();
long get_current_time();
char *get_speed_name();

void setPauseStatus(int status);
void setTerminateStatus(int status);
void setOverStatus(int status);
void setSpeed(int value);

int check_collision(Tetromino t);
void lock_tetromino();
void clear_lines();
int load_max_score();
void save_max_score();
void updateScore(int lineCount);
void updateLevel();
