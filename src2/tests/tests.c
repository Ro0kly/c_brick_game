#include "tetris.h" // Include your Tetris program header
#include <check.h>
#include <stdlib.h>

// Test case for collision with the bottom
START_TEST(test_collision_with_bottom) {
  // Initialize the field (empty)
  int field[HEIGHT][WIDTH] = {0};

  // Create a tetromino at the bottom of the field
  Tetromino t;
  t.type = 0; // I-shaped tetromino
  t.rotation = 0;
  t.x = 0;
  t.y = HEIGHT - TETROMINO_SIZE; // Position it just above the bottom

  // Check that there is no collision initially
  ck_assert_int_eq(check_collision(t), 0);

  // Move the tetromino down by 1 (should collide with the bottom)
  t.y++;
  ck_assert_int_eq(check_collision(t), 1);
}
END_TEST

// Test suite
Suite *collision_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Collision");

  // Core test case
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_collision_with_bottom);
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
