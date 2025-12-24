#include "unity.h"
#include "translator.h"
#include "tokenizer.h"
#include <string.h>
#include <stdlib.h>

/* ----------- Helpers ----------- */

static char *translate(const char *query) {
  Token *tokens = tokenize(query);
  QueryNode *q = translate_uql_to_pubmed(tokens);
  char *result = query_to_string(q);

  free_query(q);
  free_tokens(tokens);
  return result;
}

/* ----------- Tests ----------- */

void test_translate_single_term(void) {
  char *q = translate("cancer");

  TEST_ASSERT_NOT_NULL(q);
  TEST_ASSERT_EQUAL_STRING("cancer[tiab]", q);

  free(q);
}

void test_translate_title_prefix(void) {
  char *q = translate("tit:cancer");

  TEST_ASSERT_EQUAL_STRING("cancer[ti]", q);

  free(q);
}

void test_translate_abstract_prefix(void) {
  char *q = translate("abs:therapy");

  TEST_ASSERT_EQUAL_STRING("therapy[ab]", q);

  free(q);
}

void test_translate_year_prefix(void) {
  char *q = translate("year:2024");

  TEST_ASSERT_EQUAL_STRING("2024[dp]", q);

  free(q);
}

void test_translate_and_operator(void) {
  char *q = translate("cancer AND therapy");

  TEST_ASSERT_EQUAL_STRING("cancer[tiab] AND therapy[tiab]", q);

  free(q);
}

void test_translate_or_operator(void) {
  char *q = translate("cancer OR therapy");

  TEST_ASSERT_EQUAL_STRING("cancer[tiab] OR therapy[tiab]", q);

  free(q);
}

void test_translate_parentheses(void) {
  char *q = translate("( cancer AND therapy )");

  TEST_ASSERT_EQUAL_STRING("(cancer[tiab] AND therapy[tiab])", q);

  free(q);
}

void test_translate_complex_query(void) {
  char *q = translate("( tit:cancer AND abs:therapy ) OR year:2024");

  TEST_ASSERT_EQUAL_STRING(
    "(cancer[ti] AND therapy[ab]) OR 2024[dp]",
    q
  );

  free(q);
}
