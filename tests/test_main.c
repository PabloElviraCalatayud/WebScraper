#include "unity.h"

/* Declaración de todos los tests */
void test_single_term(void);
void test_and_operator(void);

void test_parse_pubmed_lowercase(void);
void test_parse_pubmed_uppercase(void);
void test_parse_unknown_repo(void);
void test_repo_name(void);

void test_translate_single_term(void);
void test_translate_title_prefix(void);
void test_translate_abstract_prefix(void);
void test_translate_year_prefix(void);
void test_translate_and_operator(void);
void test_translate_or_operator(void);
void test_translate_parentheses(void) ;
void test_translate_complex_query(void);

void test_pubmed_build_search_url_basic(void);
void test_pubmed_build_search_url_second_page(void);
void test_pubmed_build_efetch_url_single_pmid(void);
void test_pubmed_build_efetch_url_multiple_pmids(void);

void test_pubmed_parse_idlist_basic(void);
void test_pubmed_parse_idlist_empty(void);
void test_pubmed_parse_idlist_missing_idlist(void);


/* Hooks globales */
void setUp(void) {}
void tearDown(void) {}

int main(void) {
  UNITY_BEGIN();

  printf("\n-----------------TOKENIZER TEST-----------------\n");
  RUN_TEST(test_single_term);
  RUN_TEST(test_and_operator);

  printf("\n-----------------REPOSITORY PARSER TEST-----------------\n");
  RUN_TEST(test_parse_pubmed_lowercase);
  RUN_TEST(test_parse_pubmed_uppercase);
  RUN_TEST(test_parse_unknown_repo);
  RUN_TEST(test_repo_name);

  printf("\n-----------------UQL TRANSLATOR TEST-----------------\n");
  RUN_TEST(test_translate_single_term);
  RUN_TEST(test_translate_title_prefix);
  RUN_TEST(test_translate_abstract_prefix);
  RUN_TEST(test_translate_year_prefix);
  RUN_TEST(test_translate_and_operator);
  RUN_TEST(test_translate_or_operator);
  RUN_TEST(test_translate_parentheses);
  RUN_TEST(test_translate_complex_query);

  printf("\n-----------------PUBMED URL TEST-----------------\n");
  RUN_TEST(test_pubmed_build_search_url_basic);
  RUN_TEST(test_pubmed_build_search_url_second_page);
  RUN_TEST(test_pubmed_build_efetch_url_single_pmid);
  RUN_TEST(test_pubmed_build_efetch_url_multiple_pmids);

  printf("\n-----------------PUBMED FETCH TEST-----------------\n");
  RUN_TEST(test_pubmed_parse_idlist_basic);
  RUN_TEST(test_pubmed_parse_idlist_empty);
  RUN_TEST(test_pubmed_parse_idlist_missing_idlist);



  return UNITY_END();
}
