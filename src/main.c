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
UserAction_t get_action() {
  int ch = getch();
  switch (ch) {
  case 'a':
    return Left;
  case 'd':
    return Right;
  default:
    return Left;
  }
}
void handle_delay(struct timespec sp_start, struct timespec sp_end,
                  int game_speed) {
  clock_gettime(CLOCK_MONOTONIC, &sp_end);
  struct timespec ts1, ts2 = {0, 0};
  if (sp_end.tv_sec - sp_start.tv_sec <= 0 &&
      (ts2.tv_nsec = (20000000 - game_speed * 1500000) -
                     (sp_end.tv_nsec - sp_start.tv_nsec)) > 0) {
    nanosleep(&ts2, &ts1);
  }
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
  struct timespec sp_start, sp_end = {0, 0};
  int secondsLeft = 100;
  int ch;
  initscr();
  curs_set(0);
  keypad(stdscr, true);
  nodelay(stdscr, true);
  cbreak();
  noecho();
  time_t start = time(NULL);
  time_t current;
  while (true) {
    time(&current);
    ch = getch();
    if (ch == KEY_RIGHT) {
      move_right(game_info.field);
      erase();
      print_field(game_info.field);
    } else if (ch == KEY_LEFT) {
      move_left(game_info.field);
      erase();
      print_field(game_info.field);
    }
    if (difftime(current, start) > 1) {
      erase();
      time(&start);
      printw("hello");
      move_down(game_info.field);
      print_field(game_info.field);
      // refresh();
    }
  }
  endwin();
  return 0;
}
