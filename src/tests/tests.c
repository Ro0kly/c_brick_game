// #include "tetris.h" // Include your Tetris program header
#include "../brick_game/tetris/tetris.h"
#include "../gui/cli/action.h"
#include "../model/tetrominos.h"
#include <check.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

START_TEST(test_shift) {
  initGameInfo();
  spawn_tetromino();
  userInput(Start, false);
  GameInfo_t game_info = updateCurrentState();
  int y0 = game_info.current.y;
  shift();
  game_info = updateCurrentState();
  int y1 = game_info.current.y;
  ck_assert_int_eq(y0 + 1, y1);
}
START_TEST(test_shift_lock) {
  initGameInfo();
  spawn_tetromino();
  userInput(Start, false);
  change_position_of_current_to(19, 0);
  GameInfo_t game_info = updateCurrentState();
  shift();
  game_info = updateCurrentState();
  int y = game_info.current.y;
  ck_assert_int_eq(y, 0);
}
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
  GameInfo_t game_info = updateCurrentState();
  game_info.current.type = 0;
  game_info.current.rotation = 0;
  game_info.current.x = WIDTH / 2 - 2;
  game_info.current.y = 0;
  userInput(Start, false);
  game_info = updateCurrentState();
  Tetromino temp = game_info.current;
  temp.y = 17;
  ck_assert_int_eq(check_collision(temp), 1);
}
END_TEST

START_TEST(test_collision_with_tetromino_left) {
  initGameInfo();
  userInput(Start, false);
  GameInfo_t game_info = updateCurrentState();
  game_info.current.type = 0;
  game_info.current.rotation = 0;
  game_info.current.x = WIDTH / 2 - 2;
  game_info.current.y = 0;

  game_info.field[0][0] = 1;
  game_info.field[1][0] = 1;
  game_info.field[2][0] = 1;
  for (int i = 0; i < 3; i++) {
    game_info.current.x--;
  }
  ck_assert_int_eq(check_collision(game_info.current), 1);
}
END_TEST

START_TEST(test_collision_with_tetromino_right) {
  initGameInfo();
  userInput(Start, false);
  GameInfo_t game_info = updateCurrentState();
  game_info.current.type = 0;
  game_info.current.rotation = 0;
  game_info.current.x = WIDTH / 2 - 2;
  game_info.current.y = 0;

  game_info.field[0][WIDTH - 1] = 1;
  game_info.field[1][WIDTH - 1] = 1;
  game_info.field[2][WIDTH - 1] = 1;
  for (int i = 0; i <= 5; i++) {
    game_info.current.x++;
  }
  ck_assert_int_eq(check_collision(game_info.current), 1);
}
END_TEST

START_TEST(test_collision_with_tetromino_down) {
  initGameInfo();
  userInput(Start, false);
  GameInfo_t game_info = updateCurrentState();
  game_info.current.type = 0;
  game_info.current.rotation = 0;
  game_info.current.x = WIDTH / 2 - 2;
  game_info.current.y = 0;

  game_info.field[5][WIDTH / 2 - 2] = 1;
  game_info.field[5][WIDTH / 2 - 2] = 1;
  game_info.field[5][WIDTH / 2 - 2] = 1;
  for (int i = 0; i <= 1; i++) {
    game_info.current.y++;
  }
  ck_assert_int_eq(check_collision(game_info.current), 1);
}
END_TEST

START_TEST(test_rotation_tetromino_left_wall) {
  initGameInfo();
  spawn_tetromino();
  GameInfo_t game_info = updateCurrentState();
  int rot0 = game_info.current.rotation;
  userInput(Start, false);
  userInput(Left, false);
  userInput(Left, false);
  userInput(Left, false);
  userInput(Action, false);
  game_info = updateCurrentState();
  int rot1 = game_info.current.rotation;
  ck_assert_int_eq(rot1, 1);
  ck_assert_int_eq(rot0 != rot1, 1);
}

START_TEST(test_rotation_tetromino_right_wall) {
  initGameInfo();
  spawn_tetromino();
  userInput(Start, false);
  for (int i = 0; i <= 1; i++) {
    userInput(Right, false);
  }
  ck_assert_int_eq(rotate_tetromino(), 0);
}

START_TEST(test_rotation_tetromino_down_wall) {
  initGameInfo();
  spawn_tetromino();
  userInput(Start, false);
  rotate_tetromino();
  for (int i = 0; i <= 16; i++) {
    move_bottom();
  }
  ck_assert_int_eq(rotate_tetromino(), 1);
}
void print_field(int **field) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      printf(" %d ", field[i][j]);
    }
    printf("\n");
  }
}

START_TEST(test_rotation_near_tetromino_left) {
  initGameInfo();
  spawn_tetromino();
  change_position_of_current_to(0, 2);
  GameInfo_t game_info = updateCurrentState();
  userInput(Start, false);
  userInput(Down, false);
  change_tetromino_type(0);
  change_tetromino_rotation(0);
  for (int i = 0; i < WIDTH; i++) {
    userInput(Right, false);
  }
  for (int i = 0; i < 14; i++) {
    move_bottom();
  }
  for (int i = 0; i < 6; i++) {
    userInput(Left, false);
  }
  ck_assert_int_eq(rotate_tetromino(), 0);
}

START_TEST(test_rotation_near_tetromino_right) {
  initGameInfo();
  spawn_tetromino();
  change_position_of_current_to(0, 6);
  GameInfo_t game_info = updateCurrentState();
  userInput(Start, false);
  userInput(Down, false);
  change_tetromino_type(0);
  change_tetromino_rotation(0);

  for (int i = 0; i < 14; i++) {
    move_bottom();
  }
  for (int i = 0; i < 5; i++) {
    userInput(Right, false);
  }
  ck_assert_int_eq(rotate_tetromino(), 1);
}

START_TEST(test_rotation_near_tetromino_down) {
  initGameInfo();
  spawn_tetromino();
  GameInfo_t game_info = updateCurrentState();
  userInput(Start, false);
  userInput(Down, false);
  change_tetromino_type(0);
  change_tetromino_rotation(1);

  for (int i = 0; i < 14; i++) {
    move_bottom();
  }
  ck_assert_int_eq(rotate_tetromino(), 1);
}

START_TEST(test_line_clearing) {
  initGameInfo();
  GameInfo_t game_info = updateCurrentState();
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (i == HEIGHT - 1 && j != 3) {
        game_info.field[i][j] = 1;
      }
    }
  }
  ck_assert_int_eq(game_info.field[HEIGHT - 1][0], 1);
  ck_assert_int_eq(game_info.field[HEIGHT - 1][1], 1);
  ck_assert_int_eq(game_info.field[HEIGHT - 1][2], 1);
  spawn_tetromino();
  change_position_of_current_to(0, 3);
  userInput(Start, false);
  userInput(Down, false);
  game_info = updateCurrentState();
  ck_assert_int_eq(game_info.field[HEIGHT - 1][0], 0);
  ck_assert_int_eq(game_info.field[HEIGHT - 1][1], 0);
  ck_assert_int_eq(game_info.field[HEIGHT - 1][2], 0);

  ck_assert_int_eq(game_info.field[HEIGHT - 4][3], 0);
  ck_assert_int_eq(game_info.field[HEIGHT - 3][3], 1);
  ck_assert_int_eq(game_info.field[HEIGHT - 2][3], 1);
  ck_assert_int_eq(game_info.field[HEIGHT - 1][3], 1);
}

START_TEST(test_game_over) {
  initGameInfo();
  spawn_tetromino();
  userInput(Start, false);
  GameInfo_t game_info = updateCurrentState();
  ck_assert_int_eq(game_info.over, 0);
  ck_assert_int_eq(game_info.pause, 0);
  for (int i = 0; i < HEIGHT; i++) {
    userInput(Down, false);
  }
  game_info = updateCurrentState();
  ck_assert_int_eq(game_info.over, 1);
  ck_assert_int_eq(game_info.pause, 1);
}

START_TEST(test_add_score_one_line) {
  initGameInfo();
  spawn_tetromino();
  change_position_of_current_to(0, 0);
  change_tetromino_type(0);
  change_tetromino_rotation(1);
  userInput(Start, false);
  userInput(Down, false);
  change_position_of_current_to(0, 6);
  change_tetromino_type(0);
  change_tetromino_rotation(1);
  userInput(Down, false);
  change_position_of_current_to(0, 4);
  change_tetromino_type(1);
  change_tetromino_rotation(0);
  userInput(Down, false);
  GameInfo_t game_info = updateCurrentState();
  ck_assert_int_eq(game_info.score, 100);
}

START_TEST(test_add_score_two_lines) {
  initGameInfo();
  spawn_tetromino();
  userInput(Start, false);
  change_position_of_current_to(0, 0);
  change_tetromino_type(0);
  change_tetromino_rotation(1);
  userInput(Down, false);
  change_position_of_current_to(0, 0);
  change_tetromino_type(0);
  change_tetromino_rotation(1);
  userInput(Down, false);
  change_position_of_current_to(0, 6);
  change_tetromino_type(0);
  change_tetromino_rotation(1);
  userInput(Down, false);
  change_position_of_current_to(0, 6);
  change_tetromino_type(0);
  change_tetromino_rotation(1);
  userInput(Down, false);

  change_position_of_current_to(0, 4);
  change_tetromino_type(1);
  change_tetromino_rotation(0);
  userInput(Down, false);
  GameInfo_t game_info = updateCurrentState();
  ck_assert_int_eq(game_info.score, 300);
}

START_TEST(test_add_score_three_lines) {
  initGameInfo();
  spawn_tetromino();
  userInput(Start, false);
  change_position_of_current_to(0, 0);
  change_tetromino_type(0);
  change_tetromino_rotation(1);
  userInput(Down, false);
  change_position_of_current_to(0, 0);
  change_tetromino_type(0);
  change_tetromino_rotation(1);
  userInput(Down, false);
  change_position_of_current_to(0, 0);
  change_tetromino_type(0);
  change_tetromino_rotation(1);
  userInput(Down, false);
  change_position_of_current_to(0, 6);
  change_tetromino_type(0);
  change_tetromino_rotation(1);
  userInput(Down, false);
  change_position_of_current_to(0, 6);
  change_tetromino_type(0);
  change_tetromino_rotation(1);
  userInput(Down, false);
  change_position_of_current_to(0, 6);
  change_tetromino_type(0);
  change_tetromino_rotation(1);
  userInput(Down, false);

  change_position_of_current_to(0, 4);
  change_tetromino_type(0);
  change_tetromino_rotation(0);
  userInput(Down, false);
  change_position_of_current_to(0, 5);
  change_tetromino_type(0);
  change_tetromino_rotation(0);
  userInput(Down, false);
  GameInfo_t game_info = updateCurrentState();
  ck_assert_int_eq(game_info.score, 700);
}

START_TEST(test_update_level_and_speed) {
  initGameInfo();
  spawn_tetromino();
  userInput(Start, false);
  change_position_of_current_to(0, 0);
  change_tetromino_type(0);
  change_tetromino_rotation(1);
  userInput(Down, false);
  change_position_of_current_to(0, 0);
  change_tetromino_type(0);
  change_tetromino_rotation(1);
  userInput(Down, false);
  change_position_of_current_to(0, 0);
  change_tetromino_type(0);
  change_tetromino_rotation(1);
  userInput(Down, false);
  change_position_of_current_to(0, 6);
  change_tetromino_type(0);
  change_tetromino_rotation(1);
  userInput(Down, false);
  change_position_of_current_to(0, 6);
  change_tetromino_type(0);
  change_tetromino_rotation(1);
  userInput(Down, false);
  change_position_of_current_to(0, 6);
  change_tetromino_type(0);
  change_tetromino_rotation(1);
  userInput(Down, false);

  change_position_of_current_to(0, 4);
  change_tetromino_type(0);
  change_tetromino_rotation(0);
  userInput(Down, false);
  change_position_of_current_to(0, 5);
  change_tetromino_type(0);
  change_tetromino_rotation(0);
  userInput(Down, false);
  GameInfo_t game_info = updateCurrentState();
  ck_assert_int_eq(game_info.level, 1);
  ck_assert_int_eq(game_info.speed, 1);
}

START_TEST(test_pause) {
  initGameInfo();
  spawn_tetromino();
  userInput(Start, false);
  userInput(Pause, false);
  GameInfo_t game_info = updateCurrentState();
  ck_assert_int_eq(game_info.pause, 1);
}

START_TEST(test_speed) {
  initGameInfo();
  spawn_tetromino();
  userInput(Start, false);
  setSpeed(1);
  char *str1 = get_speed_name();
  ck_assert_str_eq(str1, "Snail");
  setSpeed(2);
  char *str2 = get_speed_name();
  ck_assert_str_eq(str2, "Turtle");
  setSpeed(3);
  char *str3 = get_speed_name();
  ck_assert_str_eq(str3, "Sloth");
  setSpeed(4);
  char *str4 = get_speed_name();
  ck_assert_str_eq(str4, "Panda");
  setSpeed(5);
  char *str5 = get_speed_name();
  ck_assert_str_eq(str5, "Kangaroo");
  setSpeed(6);
  char *str6 = get_speed_name();
  ck_assert_str_eq(str6, "Cheetah");
  setSpeed(7);
  char *str7 = get_speed_name();
  ck_assert_str_eq(str7, "Falcon");
  setSpeed(8);
  char *str8 = get_speed_name();
  ck_assert_str_eq(str8, "Rocket");
  setSpeed(9);
  char *str9 = get_speed_name();
  ck_assert_str_eq(str9, "Lightning");
  setSpeed(10);
  char *str10 = get_speed_name();
  ck_assert_str_eq(str10, "Sonic");
}
Suite *collision_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Collision");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_shift);
  tcase_add_test(tc_core, test_shift_lock);
  tcase_add_test(tc_core, test_move_tetromino_left);
  tcase_add_test(tc_core, test_move_tetromino_right);
  tcase_add_test(tc_core, test_move_tetromino_down);
  tcase_add_test(tc_core, test_collision_tetromino_left);
  tcase_add_test(tc_core, test_collision_tetromino_right);
  tcase_add_test(tc_core, test_collision_tetromino_down);
  tcase_add_test(tc_core, test_collision_with_tetromino_left);
  tcase_add_test(tc_core, test_collision_with_tetromino_right);
  tcase_add_test(tc_core, test_collision_with_tetromino_down);
  tcase_add_test(tc_core, test_rotation_tetromino_left_wall);
  tcase_add_test(tc_core, test_rotation_tetromino_right_wall);
  tcase_add_test(tc_core, test_rotation_tetromino_down_wall);
  tcase_add_test(tc_core, test_rotation_near_tetromino_left);
  tcase_add_test(tc_core, test_rotation_near_tetromino_right);
  tcase_add_test(tc_core, test_rotation_near_tetromino_down);
  tcase_add_test(tc_core, test_line_clearing);
  tcase_add_test(tc_core, test_game_over);
  tcase_add_test(tc_core, test_add_score_one_line);
  tcase_add_test(tc_core, test_add_score_two_lines);
  tcase_add_test(tc_core, test_add_score_three_lines);
  tcase_add_test(tc_core, test_update_level_and_speed);
  tcase_add_test(tc_core, test_pause);
  tcase_add_test(tc_core, test_speed);
  suite_add_tcase(s, tc_core);

  return s;
}

// Main function to run the tests
int main(void) {
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
