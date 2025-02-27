#include "brick_game/tetris/tetris.h"
#include "gui/cli/action.h"
#include "gui/cli/draw.h"
// Function prototypes

// Tetromino shapes (7 types, 4 rotations each)

int main() {
  initNcurses();
  initGameInfo();

  srand(time(NULL)); // Seed random number generator
  time_t start_time = time(NULL);
  time_t last_fall_time = start_time;
  setPauseStatus(1);
  spawn_tetromino(); // Spawn the first tetromino
  while (1) {
    clear();
    GameInfo_t game_info = updateCurrentState();
    draw_field(game_info.field);
    draw_tetromino(game_info.current);
    draw_next_tetromino(game_info.next);
    refresh();
    UserAction_t action = getUserAction();
    userInput(action, 0);

    time_t current_time = time(NULL);
    if (current_time - last_fall_time >= 1) {
      shift();
      last_fall_time = current_time;
    }
  }

  endwin(); // End ncurses mode
  return 0;
}
