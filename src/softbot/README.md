## Traducción del UQL a PubMed

| Elemento UQL | Traducción PubMed |
| ------------ | ----------------- |
| `tit:term`   | `term[ti]`        |
| `abs:term`   | `term[ab]`        |
| `term`       | `term[tiab]`      |
| `year:2024`  | `2024[dp]`        |
| `AND`, `OR`  | `AND`, `OR`       |
| `(` `)`      | `(` `)`           |

## Campos de PubMed utilizados en la práctica

| Propósito en la práctica | Campo PubMed       | Tag      | Uso principal |
| ------------------------ | ------------------ | -------- | ------------- |
| Título del artículo      | Title              | `[ti]`   | Traducción de `tit:` y extracción del título |
| Abstract                 | Abstract           | `[ab]`   | Traducción de `abs:` y extracción del resumen |
| Título o abstract        | Title/Abstract     | `[tiab]` | Búsqueda general sin prefijo |
| Autores                  | Author             | `[au]`   | Extracción de la lista de autores |
| DOI / identificador      | Article Identifier | `[aid]`  | Extracción del DOI |
| Identificador PubMed     | PMID               | `[pmid]` | Identificador único |
| Año de publicación       | Publication Date   | `[dp]`   | Traducción de `year:` |
| Revista                  | Journal            | `[ta]`   | Información contextual |
| Tipo de publicación      | Publication Type   | `[pt]`   | Filtrado opcional |
| Idioma                   | Language           | `[la]`   | Filtrado opcional |
| Afiliación               | Affiliation        | `[ad]`   | Metadato adicional |

## Referencia completa de Search Field Tags de PubMed

| Campo                          | Tag                | Descripción                                 |
| ------------------------------ | ------------------ | ------------------------------------------- |
| Affiliation                    | `[ad]`             | Afiliación institucional de los autores     |
| All Fields                     | `[all]`            | Busca en todos los campos                   |
| Article Identifier             | `[aid]`            | Identificador del artículo (DOI, PII, etc.) |
| Author                         | `[au]`             | Apellido e iniciales del autor              |
| Author Identifier              | `[auid]`           | Identificador del autor (ORCID, etc.)       |
| Book                           | `[book]`           | Título del libro                            |
| Comment / Correction Type      | —                  | Tipo de comentario o corrección             |
| Completion Date                | `[dcom]`           | Fecha de finalización del registro          |
| Conflict of Interest Statement | `[cois]`           | Declaración de conflicto de intereses       |
| Corporate Author               | `[cn]`             | Autor corporativo                           |
| Create Date                    | `[crdt]`           | Fecha de creación del registro              |
| EC/RN Number                   | `[rn]`             | Número EC o Registry Number                 |
| Editor                         | `[ed]`             | Editor del artículo                         |
| Entry Date                     | `[edat]`           | Fecha de entrada en PubMed                  |
| Filter                         | `[filter]`, `[sb]` | Filtros predefinidos                        |
| First Author Name              | `[1au]`            | Nombre del primer autor                     |
| Full Author Name               | `[fau]`            | Nombre completo del autor                   |
| Full Investigator Name         | `[fir]`            | Nombre completo del investigador            |
| Grants and Funding             | `[gr]`             | Información de financiación                 |
| Investigator                   | `[ir]`             | Investigador                                |
| ISBN                           | `[isbn]`           | ISBN                                        |
| Issue                          | `[ip]`             | Número de la revista                        |
| Journal                        | `[ta]`             | Nombre de la revista                        |
| Language                       | `[la]`             | Idioma                                      |
| Last Author Name               | `[lastau]`         | Último autor                                |
| Location ID                    | `[lid]`            | Identificador de localización               |
| MeSH Date                      | `[mhda]`           | Fecha de asignación MeSH                    |
| MeSH Major Topic               | `[majr]`           | Tema MeSH principal                         |
| MeSH Subheadings               | `[sh]`             | Subencabezados MeSH                         |
| MeSH Terms                     | `[mh]`             | Términos MeSH                               |
| Modification Date              | `[lr]`             | Última modificación                         |
| NLM Unique ID                  | `[jid]`            | Identificador único NLM                     |
| Other Term                     | `[ot]`             | Otros términos                              |
| Owner                          | —                  | Propietario del registro                    |
| Pagination                     | `[pg]`             | Páginas                                     |
| Personal Name as Subject       | `[ps]`             | Persona como sujeto                         |
| Pharmacological Action         | `[pa]`             | Acción farmacológica                        |
| Place of Publication           | `[pl]`             | Lugar de publicación                        |
| PMCID and MID                  | —                  | Identificadores PMC                         |
| PMID                           | `[pmid]`           | PubMed ID                                   |
| Publication Date               | `[dp]`             | Fecha de publicación                        |
| Publication Type               | `[pt]`             | Tipo de publicación                         |
| Publisher                      | `[pubn]`           | Editorial                                   |
| Secondary Source ID            | `[si]`             | Identificador de fuente secundaria          |
| Subset                         | `[sb]`             | Subconjunto                                 |
| Supplementary Concept          | `[nm]`             | Conceptos suplementarios                    |
| Text Words                     | `[tw]`             | Texto libre                                 |
| Title                          | `[ti]`             | Título                                      |
| Title/Abstract                 | `[tiab]`           | Título o abstract                           |
| Transliterated Title           | `[tt]`             | Título transliterado                        |
| Volume                         | `[vi]`             | Volumen                                     |

