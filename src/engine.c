#include "engine.h"
void fillField(int **field) {
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      field[i][j] = 0;
    }
  }
}
