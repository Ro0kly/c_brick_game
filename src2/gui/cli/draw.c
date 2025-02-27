#include "draw.h"
#include <ncurses.h>

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
void draw_next_tetromino(Tetromino tetro) {
  for (int y = 0; y < TETROMINO_SIZE; y++) {
    for (int x = 0; x < TETROMINO_SIZE; x++) {
      if (tetrominoes[tetro.type][tetro.rotation][y][x]) {
        mvprintw(y, x * 2 + 30, "[]");
      }
    }
  }
}
// Display game over message
void draw_game_over() {
  clear();
  mvprintw(HEIGHT / 2, WIDTH, "GAME OVER!");
  // mvprintw(HEIGHT / 2 + 1, WIDTH, "Final Score: %d", score);
  refresh();
  sleep(3); // Wait for 3 seconds before exiting
}
// Draw the playing field
void draw_field(int **field) {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      mvprintw(y + 2, x * 2 + 2, field[y][x] ? "[]" : " .");
    }
  }
}
void initNcurses() {
  initscr();             // Initialize ncurses
  cbreak();              // Disable line buffering
  noecho();              // Don't echo input
  keypad(stdscr, TRUE);  // Enable special keys
  nodelay(stdscr, TRUE); // Make getch() non-blocking
  curs_set(0);           // Hide cursor
}
