#include "engine.h"

GameInfo_t updateCurrentState() {
  GameInfo_t game_info = {0};
  game_info.field = malloc(FIELD_HEIGHT * sizeof(int *));

  for (int i = 0; i < FIELD_HEIGHT; i++) {
    game_info.field[i] = malloc(FIELD_WIDTH * sizeof(int));
  }
  fillFieldByDefault(game_info.field);
  addNewPieceOnField(game_info.field, red);
  return game_info;
}
const int red_piece[2][4] = {{0, 0, 0, 0}, {1, 1, 1, 1}};
void fillFieldByDefault(int **field) {
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      field[i][j] = 0;
    }
  }
}

void addNewPieceOnField(int **field, PieceKind_t kind) {
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      if (i <= 1 && j <= 3) {
        field[i][j] = red_piece[i][j];
      }
    }
  }
}

void print_field(int **field) {
  printw("\n");
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      printw("%d", field[i][j]);
    }
    printw("\n");
  }
}

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
