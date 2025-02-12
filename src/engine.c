#include "engine.h"
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
