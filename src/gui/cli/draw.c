#include "draw.h"
#include <ncurses.h>

void draw_welcome_title() {
  const char *welcome_art[] = {
      " __      __   _                          ",
      " \\ \\    / /__| | ___ ___  _ __ ___   ___ ",
      "  \\ \\/\\/ / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\",
      "   \\  /\\  /  __/ | (_| (_) | | | | | |  __/",
      "    \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|"};
  // Calculate the number of lines in the ASCII art
  int num_lines = sizeof(welcome_art) / sizeof(welcome_art[0]);
  for (int i = 0; i < num_lines; i++) {
    mvprintw(i, 0, "%s", welcome_art[i]);
  }
}
void draw_instruction() {
  mvprintw(HEIGHT / 2 + 9, 30, "<- | Move left");
  mvprintw(HEIGHT / 2 + 10, 30, "-> | Move right");
  mvprintw(HEIGHT / 2 + 11, 30, "v  | Move down");
  mvprintw(HEIGHT / 2 + 12, 30, "^  | Rotate");
  mvprintw(HEIGHT / 2 + 14, 30, "s  | Start the game");
  mvprintw(HEIGHT / 2 + 15, 30, "p  | Pause the game");
  mvprintw(HEIGHT / 2 + 16, 30, "q  | Quit the game");
}
void draw_field(int **field) {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      mvprintw(y + 8, x * 2 + 2, field[y][x] ? "[]" : " .");
    }
  }
}
// Draw or erase a tetromino
void draw_tetromino(Tetromino tetro) {
  for (int y = 0; y < TETROMINO_SIZE; y++) {
    for (int x = 0; x < TETROMINO_SIZE; x++) {
      if (tetrominoes[tetro.type][tetro.rotation][y][x]) {
        mvprintw(tetro.y + y + 8, (tetro.x + x) * 2 + 2, "[]");
      }
    }
  }
}
void draw_next_tetromino(Tetromino tetro) {
  mvprintw(7, 30, "NEXT TETRAMINO");
  for (int y = 0; y < TETROMINO_SIZE; y++) {
    for (int x = 0; x < TETROMINO_SIZE; x++) {
      if (tetrominoes[tetro.type][tetro.rotation][y][x]) {
        mvprintw(y + 8, x * 2 + 32, "[]");
      } else {
        mvprintw(y + 8, x * 2 + 32, " .");
      }
    }
  }
}
void draw_info_panel(int score, int max_score, int level, char *speed) {
  mvprintw(HEIGHT / 2 + 4, 30, "SCORE: %d", score);
  mvprintw(HEIGHT / 2 + 5, 30, "MAX SCORE: %d", max_score);
  mvprintw(HEIGHT / 2 + 6, 30, "LEVEL: %d / 10", level);
  mvprintw(HEIGHT / 2 + 7, 30, "SPEED: %s", speed);
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

void initNcurses() {
  initscr();             // Initialize ncurses
  cbreak();              // Disable line buffering
  noecho();              // Don't echo input
  keypad(stdscr, TRUE);  // Enable special keys
  nodelay(stdscr, TRUE); // Make getch() non-blocking
  curs_set(0);           // Hide cursor
}
