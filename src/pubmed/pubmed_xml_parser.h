#ifndef PUBMED_XML_PARSER_H
#define PUBMED_XML_PARSER_H

#include "pubmed_types.h"

int pubmed_parse_efetch_xml(const char *xml, PubMedArticle **out_articles, int *out_count);

#endif
