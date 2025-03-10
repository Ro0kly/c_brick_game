#include "action.h"

UserAction_t getUserAction() {
  int ch = getch();

  UserAction_t action;
  switch (ch) {
  case KEY_LEFT:
    action = Left;
    break;
  case KEY_RIGHT:
    action = Right;
    break;
  case KEY_DOWN:
    action = Down;
    break;
  case KEY_UP:
    action = Action;
    break;
  case 'q':
    action = Terminate;
    break;
  case 's':
    action = Start;
    break;
  case 'p':
    action = Pause;
    break;
  case ERR:
    action = Nothing;
    break;
  }
  return action;
}
