#include "pubmed_xml_parser.h"
#include "pubmed_types.h"

#include <libxml/parser.h>
#include <libxml/tree.h>

#include <string.h>
#include <stdlib.h>

static char *str_dup(const char *s) {
  if (!s) {
    return NULL;
  }

  size_t len = strlen(s);
  char *out = malloc(len + 1);
  if (!out) {
    return NULL;
  }

  memcpy(out, s, len);
  out[len] = '\0';
  return out;
}

static char *node_text(xmlNode *node) {
  if (!node) {
    return NULL;
  }

  xmlChar *content = xmlNodeGetContent(node);
  if (!content) {
    return NULL;
  }

  char *out = str_dup((const char *)content);
  xmlFree(content);
  return out;
}

static char *extract_title(xmlNode *article) {
  for (xmlNode *n = article->children; n; n = n->next) {
    if (n->type == XML_ELEMENT_NODE &&
        strcmp((char *)n->name, "MedlineCitation") == 0) {

      for (xmlNode *a = n->children; a; a = a->next) {
        if (a->type == XML_ELEMENT_NODE &&
            strcmp((char *)a->name, "Article") == 0) {

          for (xmlNode *t = a->children; t; t = t->next) {
            if (t->type == XML_ELEMENT_NODE &&
                strcmp((char *)t->name, "ArticleTitle") == 0) {
              return node_text(t);
            }
          }
        }
      }
    }
  }

  return NULL;
}

static char *extract_abstract(xmlNode *article) {
  for (xmlNode *n = article->children; n; n = n->next) {
    if (n->type == XML_ELEMENT_NODE &&
        strcmp((char *)n->name, "MedlineCitation") == 0) {

      for (xmlNode *a = n->children; a; a = a->next) {
        if (a->type == XML_ELEMENT_NODE &&
            strcmp((char *)a->name, "Article") == 0) {

          for (xmlNode *ab = a->children; ab; ab = ab->next) {
            if (ab->type == XML_ELEMENT_NODE &&
                strcmp((char *)ab->name, "Abstract") == 0) {

              char *result = NULL;
              size_t size = 0;

              for (xmlNode *t = ab->children; t; t = t->next) {
                if (t->type == XML_ELEMENT_NODE &&
                    strcmp((char *)t->name, "AbstractText") == 0) {

                  char *part = node_text(t);
                  if (!part) {
                    continue;
                  }

                  size_t len = strlen(part);
                  char *tmp = realloc(result, size + len + 2);
                  if (!tmp) {
                    free(part);
                    free(result);
                    return NULL;
                  }

                  result = tmp;
                  memcpy(result + size, part, len);
                  size += len;
                  result[size++] = ' ';
                  result[size] = '\0';

                  free(part);
                }
              }

              return result;
            }
          }
        }
      }
    }
  }

  return NULL;
}

static char *extract_authors(xmlNode *article) {
  char *result = NULL;
  size_t size = 0;

  for (xmlNode *n = article->children; n; n = n->next) {
    if (n->type == XML_ELEMENT_NODE &&
        strcmp((char *)n->name, "MedlineCitation") == 0) {

      for (xmlNode *a = n->children; a; a = a->next) {
        if (a->type == XML_ELEMENT_NODE &&
            strcmp((char *)a->name, "Article") == 0) {

          for (xmlNode *al = a->children; al; al = al->next) {
            if (al->type == XML_ELEMENT_NODE &&
                strcmp((char *)al->name, "AuthorList") == 0) {

              for (xmlNode *au = al->children; au; au = au->next) {
                if (au->type != XML_ELEMENT_NODE ||
                    strcmp((char *)au->name, "Author") != 0) {
                  continue;
                }

                char *first = NULL;
                char *last = NULL;

                for (xmlNode *c = au->children; c; c = c->next) {
                  if (c->type != XML_ELEMENT_NODE) {
                    continue;
                  }

                  if (strcmp((char *)c->name, "ForeName") == 0) {
                    first = node_text(c);
                  } else if (strcmp((char *)c->name, "LastName") == 0) {
                    last = node_text(c);
                  }
                }

                if (first && last) {
                  size_t add = strlen(first) + strlen(last) + 3;
                  char *tmp = realloc(result, size + add + 1);
                  if (!tmp) {
                    free(first);
                    free(last);
                    free(result);
                    return NULL;
                  }

                  result = tmp;

                  if (size > 0) {
                    memcpy(result + size, "; ", 2);
                    size += 2;
                  }

                  memcpy(result + size, first, strlen(first));
                  size += strlen(first);
                  result[size++] = ' ';
                  memcpy(result + size, last, strlen(last));
                  size += strlen(last);
                  result[size] = '\0';
                }

                free(first);
                free(last);
              }
            }
          }
        }
      }
    }
  }

  return result;
}

static char *extract_article_id(xmlNode *article, const char *type) {
  for (xmlNode *n = article->children; n; n = n->next) {
    if (n->type == XML_ELEMENT_NODE &&
        strcmp((char *)n->name, "PubmedData") == 0) {

      for (xmlNode *l = n->children; l; l = l->next) {
        if (l->type == XML_ELEMENT_NODE &&
            strcmp((char *)l->name, "ArticleIdList") == 0) {

          for (xmlNode *id = l->children; id; id = id->next) {
            if (id->type != XML_ELEMENT_NODE ||
                strcmp((char *)id->name, "ArticleId") != 0) {
              continue;
            }

            xmlChar *attr = xmlGetProp(id, (xmlChar *)"IdType");
            if (attr && strcmp((char *)attr, type) == 0) {
              xmlFree(attr);
              return node_text(id);
            }

            xmlFree(attr);
          }
        }
      }
    }
  }

  return NULL;
}

static char *extract_pmid(xmlNode *article) {
  for (xmlNode *n = article->children; n; n = n->next) {
    if (n->type == XML_ELEMENT_NODE &&
        strcmp((char *)n->name, "MedlineCitation") == 0) {

      for (xmlNode *c = n->children; c; c = c->next) {
        if (c->type == XML_ELEMENT_NODE &&
            strcmp((char *)c->name, "PMID") == 0) {
          return node_text(c);
        }
      }
    }
  }

  return NULL;
}

int pubmed_parse_efetch_xml(const char *xml,
                            PubMedArticle **out_articles,
                            int *out_count) {
  static int xml_initialized = 0;
  if (!xml_initialized) {
    xmlInitParser();
    xml_initialized = 1;
  }

  xmlDoc *doc = xmlReadMemory(
    xml,
    strlen(xml),
    NULL,
    NULL,
    XML_PARSE_NOERROR | XML_PARSE_NOWARNING
  );

  if (!doc) {
    return -1;
  }

  xmlNode *root = xmlDocGetRootElement(doc);
  PubMedArticle *articles = NULL;
  int count = 0;

  for (xmlNode *n = root->children; n; n = n->next) {
    if (n->type != XML_ELEMENT_NODE ||
        strcmp((char *)n->name, "PubmedArticle") != 0) {
      continue;
    }

    PubMedArticle art = {0};

    art.title = extract_title(n);
    art.abstract = extract_abstract(n);
    art.authors = extract_authors(n);
    art.doi = extract_article_id(n, "doi");
    art.pmcid = extract_article_id(n, "pmc");
    art.pmid = extract_pmid(n);

    PubMedArticle *tmp =
      realloc(articles, sizeof(PubMedArticle) * (count + 1));
    if (!tmp) {
      break;
    }

    articles = tmp;
    articles[count++] = art;
  }

  xmlFreeDoc(doc);

  *out_articles = articles;
  *out_count = count;
  return 0;
}
