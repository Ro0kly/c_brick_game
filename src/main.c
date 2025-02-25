#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define WIDTH 10
#define HEIGHT 20
#define TETROMINO_SIZE 4

int field[HEIGHT][WIDTH] = {0}; // Playing field
int score = 0;                  // Player's score
int elapsed_time = 0;           // Elapsed time in seconds

// Tetromino shapes (7 types, 4 rotations each)
const int tetrominoes[7][4][4][4] = {
    {{{1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}},
     {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}},
     {{1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}},
     {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}}},
    // O
    {{{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}},
    // T
    {{{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{0, 1, 0, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
     {{0, 0, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
     {{0, 1, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}},
    // S
    {{{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}},
     {{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}}},
    // Z
    {{{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
     {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}},
    // J
    {{{1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{0, 1, 1, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
     {{0, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}},
     {{0, 1, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}}},
    // L
    {{{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
     {{0, 0, 0, 0}, {1, 1, 1, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}},
     {{1, 1, 0, 0},
      {0, 1, 0, 0},
      {0, 1, 0, 0},
      {0, 0, 0, 0}}} // I, O, T, S, Z, J, L shapes (same as before)
};

typedef struct {
  int x, y;     // Position of the tetromino
  int type;     // Type of tetromino (0-6)
  int rotation; // Current rotation (0-3)
} Tetromino;

Tetromino current; // Current falling tetromino

// Function prototypes
void draw_field();
void draw_tetromino(Tetromino t, int erase);
int check_collision(Tetromino t);
void rotate_tetromino();
void clear_lines();
void spawn_tetromino();
void update_timer();
void game_over();
void lock_tetromino();

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
    // Calculate elapsed time
    elapsed_time = (int)(time(NULL) - start_time);

    // Draw the field and tetromino
    clear();
    draw_field();
    draw_tetromino(current, 0);

    // Display score and timer
    mvprintw(0, WIDTH * 2 + 5, "Score: %d", score);
    mvprintw(1, WIDTH * 2 + 5, "Time: %02d:%02d", elapsed_time / 60,
             elapsed_time % 60);
    refresh();

    // Handle user input
    int ch = getch();
    if (ch != ERR) {
      Tetromino temp = current;
      switch (ch) {
      case KEY_LEFT:
        temp.x--;
        if (!check_collision(temp))
          current.x--;
        break;
      case KEY_RIGHT:
        temp.x++;
        if (!check_collision(temp))
          current.x++;
        break;
      case KEY_DOWN:
        temp.y++;
        if (!check_collision(temp))
          current.y++;
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
      Tetromino temp = current;
      temp.y++;
      if (!check_collision(temp)) {
        current.y++;
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

    usleep(10000); // Small delay to prevent CPU overuse
  }

  endwin(); // End ncurses mode
  return 0;
}

// Draw the playing field
void draw_field() {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      mvprintw(y + 2, x * 2 + 2, field[y][x] ? "[]" : " .");
    }
  }
}

// Draw or erase a tetromino
void draw_tetromino(Tetromino t, int erase) {
  for (int y = 0; y < TETROMINO_SIZE; y++) {
    for (int x = 0; x < TETROMINO_SIZE; x++) {
      if (tetrominoes[t.type][t.rotation][y][x]) {
        mvprintw(t.y + y + 2, (t.x + x) * 2 + 2, erase ? " ." : "[]");
      }
    }
  }
}

// Check for collision with the field or boundaries
int check_collision(Tetromino t) {
  for (int y = 0; y < TETROMINO_SIZE; y++) {
    for (int x = 0; x < TETROMINO_SIZE; x++) {
      if (tetrominoes[t.type][t.rotation][y][x]) {
        int new_x = t.x + x;
        int new_y = t.y + y;
        if (new_x < 0 || new_x >= WIDTH || new_y >= HEIGHT ||
            field[new_y][new_x]) {
          return 1;
        }
      }
    }
  }
  return 0;
}

// Rotate the current tetromino
void rotate_tetromino() {
  Tetromino temp = current;
  temp.rotation = (temp.rotation + 1) % 4;
  if (!check_collision(temp)) {
    current.rotation = temp.rotation;
  }
}

// Clear completed lines and update the score
void clear_lines() {
  for (int y = HEIGHT - 1; y >= 0; y--) {
    int full = 1;
    for (int x = 0; x < WIDTH; x++) {
      if (!field[y][x]) {
        full = 0;
        break;
      }
    }
    if (full) {
      // Shift all lines above down
      for (int yy = y; yy > 0; yy--) {
        for (int x = 0; x < WIDTH; x++) {
          field[yy][x] = field[yy - 1][x];
        }
      }
      // Clear the top line
      for (int x = 0; x < WIDTH; x++) {
        field[0][x] = 0;
      }
      score += 100; // Increase score
      y++;          // Recheck the same line
    }
  }
}

// Spawn a new tetromino
void spawn_tetromino() {
  current.type = rand() % 7;
  current.rotation = 0;
  current.x = WIDTH / 2 - 2;
  current.y = 0;
}

// Lock the current tetromino into the field
void lock_tetromino() {
  for (int y = 0; y < TETROMINO_SIZE; y++) {
    for (int x = 0; x < TETROMINO_SIZE; x++) {
      if (tetrominoes[current.type][current.rotation][y][x]) {
        int new_x = current.x + x;
        int new_y = current.y + y;
        if (new_y >= 0 && new_y < HEIGHT && new_x >= 0 && new_x < WIDTH) {
          field[new_y][new_x] = 1;
        }
      }
    }
  }
}

// Display game over message
void game_over() {
  mvprintw(HEIGHT / 2, WIDTH, "GAME OVER!");
  mvprintw(HEIGHT / 2 + 1, WIDTH, "Final Score: %d", score);
  refresh();
  sleep(3); // Wait for 3 seconds before exiting
}
