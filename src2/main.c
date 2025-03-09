#include "brick_game/tetris/tetris.h"
#include "gui/cli/action.h"
#include "gui/cli/draw.h"
#include <ncurses.h>
// Function prototypes

// Tetromino shapes (7 types, 4 rotations each)

int main() {
  if (!load_max_score()) {
    printf("Error: CAN NOT READ MAX SCORE FROM FILE");
    return 0;
  }
  initNcurses();
  initGameInfo();
  spawn_tetromino(); // Spawn the first tetromino

  srand(time(NULL)); // Seed random number generator
  time_t start_time = get_current_time();
  while (!getTerminateStatus()) {
    if (getOverStatus()) {
      draw_game_over();
      setTerminateStatus(1);
    } else {
      clear();
      GameInfo_t game_info = updateCurrentState();
      draw_welcome_title();
      draw_field(game_info.field);
      draw_tetromino(game_info.current);
      draw_next_tetromino(game_info.next);
      draw_info_panel(game_info.score, game_info.high_score, game_info.level,
                      get_speed_name());
      draw_instruction();
      refresh();
      UserAction_t action = getUserAction();
      userInput(action, 0);

      time_t current_time = get_current_time();
      if (current_time - start_time >=
          1000000000L - (80000000L * game_info.speed)) {
        shift();
        start_time = current_time;
      }
    }
  }

  endwin(); // End ncurses mode
  return 0;
}
