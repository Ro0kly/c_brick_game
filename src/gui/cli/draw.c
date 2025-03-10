#include "draw.h"
#include <ncurses.h>

void initNcurses() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  curs_set(0);
}

void draw_welcome_title() {
  const char *welcome[] = {" __      __   _                          ",
                           " \\ \\    / /__| | ___ ___  _ __ ___   ___ ",
                           "  \\ \\/\\/ / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\",
                           "   \\  /\\  /  __/ | (_| (_) | | | | | |  __/",
                           "    \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|"};
  int num_lines = sizeof(welcome) / sizeof(welcome[0]);
  for (int i = 0; i < num_lines; i++) {
    mvprintw(i, 0, "%s", welcome[i]);
  }
}

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

void draw_field(int **field) {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      mvprintw(y + 8, x * 2 + 2, field[y][x] ? "[]" : " .");
    }
  }
}

void draw_info_panel(int score, int max_score, int level, char *speed) {
  mvprintw(HEIGHT / 2 + 4, 30, "SCORE: %d", score);
  mvprintw(HEIGHT / 2 + 5, 30, "MAX SCORE: %d", max_score);
  mvprintw(HEIGHT / 2 + 6, 30, "LEVEL: %d / 10", level);
  mvprintw(HEIGHT / 2 + 7, 30, "SPEED: %s", speed);
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

void draw_game_over() {
  clear();
  mvprintw(HEIGHT / 2, WIDTH, "GAME OVER!");
  refresh();
  sleep(3);
}
