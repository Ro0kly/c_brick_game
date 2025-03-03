#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20
typedef enum {
  Left,
  Right,
} UserAction_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef enum { red, orange, yellow, pink, green, blue, purple } PieceKind_t;

void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();

void print_field(int **field);
void fillFieldByDefault(int **field);
void addNewPieceOnField(int **field, PieceKind_t kind, int y, int x);
void move_down(int **field);
void move_left(int **field);
void move_right(int **field);
void rotate(int **field);
