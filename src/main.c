#include "engine.h"
// #include <ncurses.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
void move_down(int **field) {
  for (int i = FIELD_HEIGHT - 1; i >= 0; i--) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      if (field[i][j] == 1 && i != FIELD_HEIGHT - 1) {
        field[i][j] = 0;
        field[i + 1][j] = 1;
      }
    }
  }
}
void move_right(int **field) {
  for (int i = FIELD_HEIGHT - 1; i >= 0; i--) {
    for (int j = FIELD_WIDTH - 1; j >= 0; j--) {
      if (field[i][j] == 1) {
        if (j == FIELD_WIDTH - 1) {
          break;
        }
        field[i][j] = 0;
        field[i][j + 1] = 1;
      }
    }
  }
}
void move_left(int **field) {
  for (int i = FIELD_HEIGHT - 1; i >= 0; i--) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      if (field[i][j] == 1) {
        if (j == 0) {
          break;
        }
        field[i][j] = 0;
        field[i][j - 1] = 1;
      }
    }
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
  int secondsLeft = 100;

  printf("START!");
  int ch;
  int iterations = 0;
  int msec = 0, trigger = 10000; /* 10ms */
  clock_t before = clock();
  do {
    clock_t difference = clock() - before;
    msec = difference * 1000 / CLOCKS_PER_SEC;
    if (msec == 1000) {
      before = clock();
      printf("tick");
    }
    iterations++;

  } while (msec < trigger);

  printf("Time taken %d seconds %d milliseconds (%d iterations)\n", msec / 1000,
         msec % 1000, iterations);
  // initscr();
  // curs_set(0);
  // keypad(stdscr, true);
  // nodelay(stdscr, true);
  //
  // refresh();
  endwin();

  return 0;
}
// while ((ch = getch()) != KEY_ENTER) {
//   clear();
//   if (ch == KEY_DOWN) {
//     for (int i = FIELD_HEIGHT - 1; i >= 0; i--) {
//       // printw("iiiii\n");
//       for (int j = 0; j < FIELD_WIDTH; j++) {
//         // printw("jjjjj\n");
//         if (game_info.field[i][j] == 1 && i != FIELD_HEIGHT - 1) {
//           game_info.field[i][j] = 0;
//           game_info.field[i + 1][j] = 1;
//         }
//       }
//     }
//     printw("DOWN!");
//     print_field(game_info.field);
//   }
// }

//
// #include <ncurses.h>
//
// int main() {
//   int secondsLeft = 120;
//   initscr();
//   curs_set(0);
//   do {
//     printw("%i", secondsLeft);
//     // refresh();
//     // erase();
//     clear();
//     secondsLeft--;
//     napms(1000);
//   } while (secondsLeft > 0);
//   endwin();
//   return 0;
// }
