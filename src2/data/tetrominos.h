#define WIDTH 10
#define HEIGHT 8
#define TETROMINO_SIZE 4

#ifndef TETROMINOS_H
#define TETROMINOS_H

typedef struct {
  int x, y;     // Position of the tetromino
  int type;     // Type of tetromino (0-6)
  int rotation; // Current rotation (0-3)
} Tetromino;

typedef enum {
  // Start,
  // Pause,
  Terminate,
  Left,
  Right,
  // Up,
  Down,
  Action,
  Nothing
} UserAction_t;

#endif
extern int tetrominoes[7][4][4][4];
