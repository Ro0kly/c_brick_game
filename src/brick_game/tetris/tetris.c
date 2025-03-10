#include "tetris.h"
#include <stdio.h>
#include <stdlib.h>

static GameInfo_t game_info = {0};

void initGameInfo() {
  game_info.field = malloc(sizeof(int *) * HEIGHT);
  for (int i = 0; i < HEIGHT; i++) {
    game_info.field[i] = malloc(sizeof(int) * WIDTH);
  }
  game_info.current = (Tetromino){0};
  game_info.next = (Tetromino){0};
  game_info.next.type = rand() % 7;
  game_info.next.rotation = 0;
  game_info.pause = 1;
  game_info.over = 0;
  game_info.terminate = 0;
  game_info.level = 1;
  game_info.speed = 1;
}

void userInput(UserAction_t action, bool hold) {

  Tetromino temp = game_info.current;
  switch (action) {
  case Left:
    if (getPauseStatus()) {
      return;
    }
    temp.x--;
    if (!check_collision(temp)) {
      move_left();
    }
    break;
  case Right:
    if (getPauseStatus()) {
      return;
    }
    temp.x++;
    if (!check_collision(temp))
      move_right();
    break;
  case Down:
    if (getPauseStatus()) {
      return;
    }
    while (!check_collision(temp)) {
      temp.y++;
      move_bottom();
    }
    move_top();
    lock_tetromino();
    clear_lines();
    spawn_tetromino();
    if (check_collision(game_info.current)) {
      game_over();
      break;
    }
    break;
  case Action:
    if (getPauseStatus()) {
      return;
    }
    rotate_tetromino();
    break;
  case Terminate:
    setTerminateStatus(1);
    break;
  case Nothing:
    break;
  case Start:
    setPauseStatus(0);
    break;
  case Pause:
    setPauseStatus(1);
    break;
  }
}

void game_over() {
  if (game_info.score > game_info.high_score) {
    save_max_score();
  }
  setPauseStatus(1);
  setOverStatus(1);
}

GameInfo_t updateCurrentState() { return game_info; }

void spawn_tetromino() {
  game_info.current.type = game_info.next.type;
  game_info.current.rotation = game_info.next.rotation;
  game_info.current.x = WIDTH / 2 - 2;
  game_info.current.y = 0;

  game_info.next.type = rand() % 7;
  game_info.next.rotation = rand() % 4;
}

void shift() {
  if (getPauseStatus()) {
    return;
  }
  Tetromino temp = game_info.current;
  temp.y++;
  if (!check_collision(temp)) {
    move_bottom();
  } else {
    lock_tetromino();
    clear_lines();
    spawn_tetromino();
    if (check_collision(game_info.current)) {
      game_over();
    }
  }
}

void move_top() { game_info.current.y--; }

void move_bottom() { game_info.current.y++; }

void move_left() { game_info.current.x--; }

void move_right() { game_info.current.x++; }

int rotate_tetromino() {
  int flag = 0;
  Tetromino temp = game_info.current;
  temp.rotation = (temp.rotation + 1) % 4;
  if (!check_collision(temp)) {
    game_info.current.rotation = temp.rotation;
  } else {
    flag = 1;
  }
  return flag;
}

void change_tetromino_type(int type) { game_info.current.type = type; }

void change_tetromino_rotation(int rotation) {
  game_info.current.rotation = rotation;
}

void change_position_of_current_to(int y, int x) {
  game_info.current.y = y;
  game_info.current.x = x;
}

int getPauseStatus() { return game_info.pause; }

int getTerminateStatus() { return game_info.terminate; }

int getOverStatus() { return game_info.over; }

long get_current_time() {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return ts.tv_sec * 1000000000L + ts.tv_nsec; // Convert to nanoseconds
}

char *get_speed_name() {
  switch (game_info.speed) {
  case 1:
    return "Snail";
  case 2:
    return "Turtle";
  case 3:
    return "Sloth";
  case 4:
    return "Panda";
  case 5:
    return "Kangaroo";
  case 6:
    return "Cheetah";
  case 7:
    return "Falcon";
  case 8:
    return "Rocket";
  case 9:
    return "Lightning";
  case 10:
    return "Sonic";
  default:
    return "Unknown";
  }
}

void setPauseStatus(int status) { game_info.pause = status; }

void setOverStatus(int status) { game_info.over = status; }

void setTerminateStatus(int status) {
  if (game_info.score > game_info.high_score) {
    save_max_score();
  }
  game_info.terminate = status;
}

void setSpeed(int value) { game_info.speed = value; }

int load_max_score() {
  int flag = 1;
  FILE *file = fopen("src/data/max_score.txt", "r");
  if (file) {
    fscanf(file, "%d", &game_info.high_score);
    fclose(file);
  } else {
    flag = 0;
  }
  return flag;
}

void save_max_score() {
  FILE *file = fopen("data/max_score.txt", "w");
  if (file) {
    fprintf(file, "%d", game_info.score);
    fclose(file);
  }
}

int check_collision(Tetromino t) {
  for (int y = 0; y < TETROMINO_SIZE; y++) {
    for (int x = 0; x < TETROMINO_SIZE; x++) {
      if (tetrominoes[t.type][t.rotation][y][x]) {
        int new_y = t.y + y;
        int new_x = t.x + x;
        if (new_x < 0 || new_x >= WIDTH || new_y >= HEIGHT ||
            game_info.field[new_y][new_x]) {
          return 1;
        }
      }
    }
  }
  return 0;
}

void clear_lines() {
  int lineCount = 0;
  for (int y = HEIGHT - 1; y >= 0; y--) {
    int full = 1;
    for (int x = 0; x < WIDTH; x++) {
      if (!game_info.field[y][x]) {
        full = 0;
        break;
      }
    }
    if (full) {
      lineCount++;
      for (int yy = y; yy > 0; yy--) {
        for (int x = 0; x < WIDTH; x++) {
          game_info.field[yy][x] = game_info.field[yy - 1][x];
        }
      }
      y++;
    }
  }
  if (lineCount != 0) {
    updateScore(lineCount);
    updateLevel();
  }
}

void updateLevel() {
  if (game_info.level * 600 <= game_info.score && game_info.level != 10) {
    game_info.level += 1;
    game_info.speed += 1;
  }
}

void updateScore(int lineCount) {
  switch (lineCount) {
  case 1:
    game_info.score += 100;
    break;
  case 2:
    game_info.score += 300;
    break;
  case 3:
    game_info.score += 700;
    break;
  case 4:
    game_info.score += 1500;
    break;
  default:
    game_info.score += 0;
  }
  if (game_info.score > game_info.high_score) {
    game_info.high_score = game_info.score;
    save_max_score();
  }
}

void lock_tetromino() {
  for (int y = 0; y < TETROMINO_SIZE; y++) {
    for (int x = 0; x < TETROMINO_SIZE; x++) {
      if (tetrominoes[game_info.current.type][game_info.current.rotation][y]
                     [x]) {
        int new_x = game_info.current.x + x;
        int new_y = game_info.current.y + y;
        if (new_y >= 0 && new_y < HEIGHT && new_x >= 0 && new_x < WIDTH) {
          game_info.field[new_y][new_x] = 1;
        }
      }
    }
  }
}
