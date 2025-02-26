#include "engine.h"

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
  Tetromino current = getCurrent();
  while (1) {
    // Calculate elapsed time
    // elapsed_time = (int)(time(NULL) - start_time);

    // Draw the field and tetromino
    clear();
    draw_field();
    draw_tetromino(0);

    // Display score and timer
    // mvprintw(0, WIDTH * 2 + 5, "Score: %d", score);
    // mvprintw(1, WIDTH * 2 + 5, "Time: %02d:%02d", elapsed_time / 60,
    //          elapsed_time % 60);
    refresh();

    // // Handle user input
    int ch = getch();
    if (ch != ERR) {
      Tetromino temp = makeTemp();
      switch (ch) {
      case KEY_LEFT:
        temp.x--;
        if (!check_collision(temp))
          move_left();
        break;
      case KEY_RIGHT:
        temp.x++;
        if (!check_collision(temp))
          move_right();
        break;
      case KEY_DOWN:
        while (!check_collision(temp)) {
          temp.y++;
          move_bottom();
        }
        move_top();
        lock_tetromino();
        clear_lines();
        spawn_tetromino();
        if (check_collision(current)) {
          game_over();
          break;
        }
        break;
      case KEY_UP:
        rotate_tetromino();
        break;
      case 'q': // Quit game
        endwin();
        return 0;
      }
    }

    // Move tetromino down automatically (every 1 second)
    time_t current_time = time(NULL);
    if (current_time - last_fall_time >= 1) {
      Tetromino temp = makeTemp();
      temp.y++;
      if (!check_collision(temp)) {
        // current.y++;
        move_bottom();
      } else {
        // Lock the tetromino in place
        lock_tetromino();
        clear_lines();
        spawn_tetromino();
        if (check_collision(current)) {
          game_over();
          break;
        }
      }
      last_fall_time = current_time;
    }

    // usleep(10000); // Small delay to prevent CPU overuse
  }

  endwin(); // End ncurses mode
  return 0;
}
