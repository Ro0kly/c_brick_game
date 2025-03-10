#define WIDTH 10
#define HEIGHT 20
#define TETROMINO_SIZE 4

#ifndef TETROMINOS_H
#define TETROMINOS_H

typedef struct {
  int x, y;
  int type;
  int rotation;
} Tetromino;

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Down,
  Action,
  Nothing
} UserAction_t;

#endif
extern int tetrominoes[7][4][4][4];
