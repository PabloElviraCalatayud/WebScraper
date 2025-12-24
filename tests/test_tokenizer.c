#include "unity.h"
#include "tokenizer.h"

void test_single_term(void) {
  Token *t = tokenize("robot");

  TEST_ASSERT_NOT_NULL(t);
  TEST_ASSERT_EQUAL(TOKEN_TERM, t->type);
  TEST_ASSERT_EQUAL_STRING("robot", t->value);
  TEST_ASSERT_NULL(t->next);

  free_tokens(t);
}

void test_and_operator(void) {
  Token *t = tokenize("robot AND vision");

  TEST_ASSERT_NOT_NULL(t);
  TEST_ASSERT_EQUAL(TOKEN_TERM, t->type);
  TEST_ASSERT_EQUAL(TOKEN_AND, t->next->type);
  TEST_ASSERT_EQUAL(TOKEN_TERM, t->next->next->type);

  free_tokens(t);
}
