#include "brick_game/tetris/tetris.h"
#include "gui/cli/action.h"
#include "gui/cli/draw.h"
// Function prototypes

// Tetromino shapes (7 types, 4 rotations each)

int main() {
  initscr();             // Initialize ncurses
  cbreak();              // Disable line buffering
  noecho();              // Don't echo input
  keypad(stdscr, TRUE);  // Enable special keys
  nodelay(stdscr, TRUE); // Make getch() non-blocking
  curs_set(0);           // Hide cursor

  srand(time(NULL)); // Seed random number generator
  spawn_tetromino(); // Spawn the first tetromino

  time_t start_time = time(NULL);
  time_t last_fall_time = start_time;
  while (1) {
    clear();
    draw_field(getField());
    draw_tetromino(getCurrent());

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
