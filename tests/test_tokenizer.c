#include "unity.h"
#include "tokenizer.h"

void setUp(void) {}
void tearDown(void) {}

void test_single_term(void) {
  Token *t = tokenize("robot");

  TEST_ASSERT_NOT_NULL(t);
  TEST_ASSERT_EQUAL(TOKEN_TERM, t->type);
  TEST_ASSERT_NOT_NULL(t->value);
  TEST_ASSERT_EQUAL_STRING("robot", t->value);
  TEST_ASSERT_NULL(t->next);

  free_tokens(t);
}

void test_and_operator(void) {
  Token *t = tokenize("robot AND vision");

  TEST_ASSERT_NOT_NULL(t);
  TEST_ASSERT_EQUAL(TOKEN_TERM, t->type);
  TEST_ASSERT_EQUAL_STRING("robot", t->value);

  TEST_ASSERT_NOT_NULL(t->next);
  TEST_ASSERT_EQUAL(TOKEN_AND, t->next->type);
  TEST_ASSERT_NULL(t->next->value);

  TEST_ASSERT_NOT_NULL(t->next->next);
  TEST_ASSERT_EQUAL(TOKEN_TERM, t->next->next->type);
  TEST_ASSERT_EQUAL_STRING("vision", t->next->next->value);

  TEST_ASSERT_NULL(t->next->next->next);

  free_tokens(t);
}

void test_parentheses_and_or(void) {
  Token *t = tokenize("(robot OR vision)");

  TEST_ASSERT_NOT_NULL(t);
  TEST_ASSERT_EQUAL(TOKEN_LEFT_PAREN, t->type);

  TEST_ASSERT_NOT_NULL(t->next);
  TEST_ASSERT_EQUAL(TOKEN_TERM, t->next->type);
  TEST_ASSERT_EQUAL_STRING("robot", t->next->value);

  TEST_ASSERT_NOT_NULL(t->next->next);
  TEST_ASSERT_EQUAL(TOKEN_OR, t->next->next->type);

  TEST_ASSERT_NOT_NULL(t->next->next->next);
  TEST_ASSERT_EQUAL(TOKEN_TERM, t->next->next->next->type);
  TEST_ASSERT_EQUAL_STRING("vision", t->next->next->next->value);

  TEST_ASSERT_NOT_NULL(t->next->next->next->next);
  TEST_ASSERT_EQUAL(TOKEN_RIGHT_PAREN, t->next->next->next->next->type);

  TEST_ASSERT_NULL(t->next->next->next->next->next);

  free_tokens(t);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_single_term);
  RUN_TEST(test_and_operator);
  RUN_TEST(test_parentheses_and_or);
  return UNITY_END();
}
