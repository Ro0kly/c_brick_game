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
void shift();
void move_top();
void move_bottom();
void move_left();
void move_right();

GameInfo_t updateCurrentState();
int check_collision(Tetromino t);
int rotate_tetromino();
void clear_lines();
void spawn_tetromino();
void lock_tetromino();
int getPauseStatus();
void setPauseStatus(int status);
int getTerminateStatus();
void setTerminateStatus(int status);
int getOverStatus();
void setOverStatus(int status);
void change_position_of_current_to(int y, int x);
void change_tetromino_type(int type);
void change_tetromino_rotation(int rotation);
int load_max_score();
void save_max_score();
void updateScore(int lineCount);
void updateLevel();
long get_current_time();
char *get_speed_name();
