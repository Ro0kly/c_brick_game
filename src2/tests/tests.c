// #include "tetris.h" // Include your Tetris program header
#include "../brick_game/tetris/tetris.h"
#include "../data/tetrominos.h"
#include "../gui/cli/action.h"
#include <check.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

START_TEST(test_move_tetromino_left) {
  initGameInfo();
  spawn_tetromino();
  userInput(Start, false);
  GameInfo_t game_info = updateCurrentState();
  int x0 = game_info.current.x;
  userInput(Left, false);
  game_info = updateCurrentState();
  int x1 = game_info.current.x;
  ck_assert_int_eq(x0 - 1, x1);
}
END_TEST

START_TEST(test_move_tetromino_right) {
  initGameInfo();
  spawn_tetromino();
  userInput(Start, false);
  GameInfo_t game_info = updateCurrentState();
  int x0 = game_info.current.x;
  userInput(Right, false);
  game_info = updateCurrentState();
  int x1 = game_info.current.x;
  ck_assert_int_eq(x0 + 1, x1);
}
END_TEST

START_TEST(test_move_tetromino_down) {
  initGameInfo();
  spawn_tetromino();
  userInput(Start, false);
  GameInfo_t game_info = updateCurrentState();
  int y0 = game_info.current.y;
  userInput(Down, false);
  game_info = updateCurrentState();
  int y1 = game_info.current.y;
  ck_assert_int_eq(y0, y1);
  ck_assert_int_eq(game_info.field[16][WIDTH / 2 - 2], 1);
  ck_assert_int_eq(game_info.field[17][WIDTH / 2 - 2], 1);
  ck_assert_int_eq(game_info.field[18][WIDTH / 2 - 2], 1);
  ck_assert_int_eq(game_info.field[19][WIDTH / 2 - 2], 1);
}
END_TEST

START_TEST(test_collision_tetromino_left) {
  initGameInfo();
  spawn_tetromino();
  userInput(Start, false);
  GameInfo_t game_info = updateCurrentState();
  userInput(Left, false);
  userInput(Left, false);
  userInput(Left, false);
  game_info = updateCurrentState();
  Tetromino tmp = game_info.current;
  tmp.x--;
  ck_assert_int_eq(check_collision(game_info.current), 0);
  ck_assert_int_eq(check_collision(tmp), 1);
}

START_TEST(test_collision_tetromino_right) {
  initGameInfo();
  spawn_tetromino();
  userInput(Start, false);
  GameInfo_t game_info = updateCurrentState();
  userInput(Right, false);
  userInput(Right, false);
  userInput(Right, false);
  userInput(Right, false);
  userInput(Right, false);
  userInput(Right, false);
  game_info = updateCurrentState();
  Tetromino tmp = game_info.current;
  tmp.x++;
  ck_assert_int_eq(check_collision(game_info.current), 0);
  ck_assert_int_eq(check_collision(tmp), 1);
}

START_TEST(test_collision_tetromino_down) {
  initGameInfo();
  spawn_tetromino();
  userInput(Start, false);
  GameInfo_t game_info = updateCurrentState();
  Tetromino temp = game_info.current;
  temp.y = 17;
  ck_assert_int_eq(check_collision(temp), 1);
}
END_TEST

Suite *collision_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Collision");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_move_tetromino_left);
  tcase_add_test(tc_core, test_move_tetromino_right);
  tcase_add_test(tc_core, test_move_tetromino_down);
  tcase_add_test(tc_core, test_collision_tetromino_left);
  tcase_add_test(tc_core, test_collision_tetromino_right);
  tcase_add_test(tc_core, test_collision_tetromino_down);
  suite_add_tcase(s, tc_core);

  return s;
}

// Main function to run the tests
int main(void) {
  printf("lalalal");
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = collision_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
