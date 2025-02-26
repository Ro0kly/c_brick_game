#include "draw.h"

// Draw or erase a tetromino
void draw_tetromino(Tetromino tetro) {
  for (int y = 0; y < TETROMINO_SIZE; y++) {
    for (int x = 0; x < TETROMINO_SIZE; x++) {
      if (tetrominoes[tetro.type][tetro.rotation][y][x]) {
        mvprintw(tetro.y + y + 2, (tetro.x + x) * 2 + 2, "[]");
      }
    }
  }
}
// Display game over message
void game_over() {
  clear();
  mvprintw(HEIGHT / 2, WIDTH, "GAME OVER!");
  // mvprintw(HEIGHT / 2 + 1, WIDTH, "Final Score: %d", score);
  refresh();
  sleep(3); // Wait for 3 seconds before exiting
}
// Draw the playing field
void draw_field(int (*field)[10]) {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      mvprintw(y + 2, x * 2 + 2, field[y][x] ? "[]" : " .");
    }
  }
}
