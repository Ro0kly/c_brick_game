#include "engine.h"
#include "pieces.h"
#include <ncurses.h>
GameInfo_t updateCurrentState() {
  GameInfo_t game_info = {0};
  // game_info.field = malloc(FIELD_HEIGHT * sizeof(int *));
  //
  // for (int i = 0; i < FIELD_HEIGHT; i++) {
  //   game_info.field[i] = malloc(FIELD_WIDTH * sizeof(int));
  // }
  // fillFieldByDefault(game_info.field);
  // addNewPieceOnField(game_info.field, red);
  return game_info;
}
int rotate_index = 0;
void fillFieldByDefault(int **field) {
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      field[i][j] = 0;
    }
  }
}

void addNewPieceOnField(int **field, PieceKind_t kind, int y, int x) {
  for (int i = y; i < y + 3; i++) {
    for (int j = x; j < x + 3; j++) {
      field[i][j] = blue_piece[rotate_index][i][j];
    }
  }
  // for (int i = 0; i < FIELD_HEIGHT; i++) {
  //   for (int j = 0; j < FIELD_WIDTH; j++) {
  //     if (i == y && j == x) {
  //       for (int k = y; )
  //       break;
  //     }
  //   }
  // }
}

void print_field(int **field) {
  printw("\n");
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      if (field[i][j] == 2) {
        printw("+");
      } else {
        printw("%d", field[i][j]);
      }
    }
    printw("\n");
  }
}
void rotate(int **field) {
  int y = 0, x = 0;
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      if (field[i][j] == 1 || field[i][j] == 2) {
        y = i;
        x = j;
        break;
      }
    }
  }
  fillFieldByDefault(field);
  if (rotate_index == 3) {
    rotate_index = 1;
  } else {
    rotate_index += 1;
  }
  addNewPieceOnField(field, red, y, x);
}
void move_down(int **field) {
  for (int i = FIELD_HEIGHT - 1; i >= 0; i--) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      if (field[i][j] == 1 && i != FIELD_HEIGHT - 1) {
        field[i][j] = 0;
        field[i + 1][j] = 1;
      }
      if (field[i][j] == 2 && i != FIELD_HEIGHT - 1) {
        field[i][j] = 0;
        field[i + 1][j] = 2;
      }
    }
  }
}
void move_right(int **field) {
  for (int i = FIELD_HEIGHT - 1; i >= 0; i--) {
    for (int j = FIELD_WIDTH - 1; j >= 0; j--) {

      if (field[i][j] == 1 || field[i][j] == 2) {
        if (j == FIELD_WIDTH - 1) {
          break;
        }
        if (field[i][j] == 1) {
          field[i][j + 1] = 1;

        } else if (field[i][j] == 2) {
          field[i][j + 1] = 2;
        }
        field[i][j] = 0;
      }
    }
  }
}
void move_left(int **field) {
  for (int i = FIELD_HEIGHT - 1; i >= 0; i--) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      if (field[i][j] == 1 || field[i][j] == 2) {
        if (j == 0) {
          break;
        }
        if (field[i][j] == 1) {
          field[i][j - 1] = 1;

        } else if (field[i][j] == 2) {
          field[i][j - 1] = 2;
        }
        field[i][j] = 0;
      }
    }
  }
}
