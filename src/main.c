#include "engine.h"
// #include <ncurses.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  printf("Welcome to NVIM!\n");
  GameInfo_t game_info = {0};
  game_info.field = malloc(FIELD_HEIGHT * sizeof(int *));

  for (int i = 0; i < FIELD_HEIGHT; i++) {
    game_info.field[i] = malloc(FIELD_WIDTH * sizeof(int));
  }
  fillFieldByDefault(game_info.field);
  // print_field(game_info.field);
  addNewPieceOnField(game_info.field, red);
  int ch;
  initscr();
  // int row, col;
  // getmaxyx(stdscr, row, col);
  curs_set(0);
  keypad(stdscr, true);

  while ((ch = getch()) != KEY_ENTER) {
    clear();
    if (ch == KEY_DOWN) {
      for (int i = FIELD_HEIGHT - 1; i >= 0; i--) {
        // printw("iiiii\n");
        for (int j = 0; j < FIELD_WIDTH; j++) {
          // printw("jjjjj\n");
          if (game_info.field[i][j] == 1 && i != FIELD_HEIGHT - 1) {
            game_info.field[i][j] = 0;
            game_info.field[i + 1][j] = 1;
          }
        }
      }
      printw("DOWN!");
      print_field(game_info.field);
    }
  }
  endwin();
  return 0;
}
