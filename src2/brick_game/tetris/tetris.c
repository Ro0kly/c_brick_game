#include "tetris.h"
static int field[HEIGHT][WIDTH] = {0}; // Playing field
static int score = 0;                  // Player's score
static int elapsed_time = 0;           // Elapsed time in seconds

static Tetromino current = {0}; // Current falling tetromino
Tetromino getCurrent() { return current; }

Tetromino makeTemp() {
  Tetromino temp = current;
  return temp;
}
int (*getField())[10] { return field; }
void move_top() { current.y--; }
void move_bottom() { current.y++; }
void move_left() { current.x--; }
void move_right() { current.x++; }

void shift() {
  Tetromino temp = current;
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
  Tetromino temp = current;
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
    if (check_collision(getCurrent())) {
      // game_over();
      break;
    }
    break;
  case Action:
    rotate_tetromino();
    break;
  case Terminate:
    break;
  }
}
// Rotate the current tetromino
void rotate_tetromino() {
  Tetromino temp = current;
  temp.rotation = (temp.rotation + 1) % 4;
  if (!check_collision(temp)) {
    current.rotation = temp.rotation;
  }
}
// Spawn a new tetromino
void spawn_tetromino() {
  // current.type = rand() % 7;
  current.type = 5;
  current.rotation = 0;
  current.x = WIDTH / 2 - 2;
  current.y = 0;
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
            field[new_y][new_x]) {
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
      if (!field[y][x]) {
        full = 0;
        break;
      }
    }
    if (full) {
      // Shift all lines above down
      for (int yy = y; yy > 0; yy--) {
        for (int x = 0; x < WIDTH; x++) {
          field[yy][x] = field[yy - 1][x];
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
      if (tetrominoes[current.type][current.rotation][y][x]) {
        int new_x = current.x + x;
        int new_y = current.y + y;
        if (new_y >= 0 && new_y < HEIGHT && new_x >= 0 && new_x < WIDTH) {
          field[new_y][new_x] = 1;
        }
      }
    }
  }
}
