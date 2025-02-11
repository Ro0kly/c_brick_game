#include "engine.h"
void print_field(int **field) {
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      printf("%d", field[i][j]);
    }
    printf("\n");
  }
}
int main(void) {
  printf("Welcome to NVIM!\n");
  GameInfo_t game_info = {0};
  fillField(game_info.field);
  print_field(game_info.field);
  return 0;
}
