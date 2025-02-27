#include "tetris.h"
#include <stdlib.h>
// static int field[HEIGHT][WIDTH] = {0}; // Playing field
static int score = 0;        // Player's score
static int elapsed_time = 0; // Elapsed time in seconds

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
}

GameInfo_t updateCurrentState() { return game_info; }
void move_top() { game_info.current.y--; }
void move_bottom() { game_info.current.y++; }
void move_left() { game_info.current.x--; }
void move_right() { game_info.current.x++; }

void shift() {
  Tetromino temp = game_info.current;
  temp.y++;
  if (!check_collision(temp)) {
    move_bottom();
  } else {
    lock_tetromino();
    clear_lines();
    spawn_tetromino();
    // if (check_collision(getCurrent())) {
    //   game_over();
    //   break;
    // }
  }
}
void userInput(UserAction_t action, bool hold) {
  Tetromino temp = game_info.current;
  switch (action) {
  case Left:
    temp.x--;
    if (!check_collision(temp))
      move_left();
    break;
  case Right:
    temp.x++;
    if (!check_collision(temp))
      move_right();
    break;
  case Down:
    while (!check_collision(temp)) {
      temp.y++;
      move_bottom();
    }
    move_top();
    lock_tetromino();
    clear_lines();
    spawn_tetromino();
    if (check_collision(game_info.current)) {
      // game_over();
      break;
    }
    break;
  case Action:
    rotate_tetromino();
    break;
  case Terminate:
    break;
  case Nothing:
    break;
  }
}
// Rotate the current tetromino
void rotate_tetromino() {
  Tetromino temp = game_info.current;
  temp.rotation = (temp.rotation + 1) % 4;
  if (!check_collision(temp)) {
    game_info.current.rotation = temp.rotation;
  }
}
// Spawn a new tetromino
void spawn_tetromino() {
  game_info.current.type = game_info.next.type;
  game_info.current.rotation = game_info.next.rotation;
  game_info.current.x = WIDTH / 2 - 2;
  game_info.current.y = 0;

  game_info.next.type = rand() % 7;
  game_info.next.rotation = rand() % 4;
}
// // Display game over message

// Check for collision with the field or boundaries
int check_collision(Tetromino t) {
  for (int y = 0; y < TETROMINO_SIZE; y++) {
    for (int x = 0; x < TETROMINO_SIZE; x++) {
      if (tetrominoes[t.type][t.rotation][y][x]) {
        int new_x = t.x + x;
        int new_y = t.y + y;
        if (new_x < 0 || new_x >= WIDTH || new_y >= HEIGHT ||
            game_info.field[new_y][new_x]) {
          return 1;
        }
      }
    }
  }
  return 0;
}

// Clear completed lines and update the score
void clear_lines() {
  for (int y = HEIGHT - 1; y >= 0; y--) {
    int full = 1;
    for (int x = 0; x < WIDTH; x++) {
      if (!game_info.field[y][x]) {
        full = 0;
        break;
      }
    }
    if (full) {
      // Shift all lines above down
      for (int yy = y; yy > 0; yy--) {
        for (int x = 0; x < WIDTH; x++) {
          game_info.field[yy][x] = game_info.field[yy - 1][x];
        }
      }
      // Clear the top line
      // for (int x = 0; x < WIDTH; x++) {
      //   field[0][x] = 0;
      // }
      // score += 100; // Increase score
      // y++;          // Recheck the same line
    }
  }
}

// Lock the current tetromino into the field
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
