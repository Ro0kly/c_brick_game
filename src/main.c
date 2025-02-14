#include "engine.h"
// #include <ncurses.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

void init_ncurses() {
  initscr();
  curs_set(0);
  keypad(stdscr, true);
  nodelay(stdscr, true);
}

void delay(double dly) {
  /* save start time */
  const time_t start = time(NULL);
  time_t current;
  do {
    /* get current time */
    time(&current);
    /* break loop when the requested number of seconds have elapsed */

  } while (difftime(current, start) < dly);
}
int main(int argc, char *argv[]) {
  printf("Welcome to NVIM!\n");
  GameInfo_t game_info = {0};
  game_info.field = malloc(FIELD_HEIGHT * sizeof(int *));

  for (int i = 0; i < FIELD_HEIGHT; i++) {
    game_info.field[i] = malloc(FIELD_WIDTH * sizeof(int));
  }
  fillFieldByDefault(game_info.field);
  addNewPieceOnField(game_info.field, red);
  int secondsLeft = 100;
  int ch;
  initscr();
  curs_set(0);
  keypad(stdscr, true);
  nodelay(stdscr, true);
  for (int i = 0; i < 25; i++) {
    clear();
    // printw("%d seconds have passed\n", i + 1);

    move_down(game_info.field);
    print_field(game_info.field);
    refresh();
    delay(1);
  }
  printw("dadadad");
  endwin();
  return 0;
}
