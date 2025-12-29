| Elemento UQL    | Significado en UQL      | Sintaxis en PubMed | Ejemplo UQL                   | Ejemplo PubMed                      |
| --------------- | ----------------------- | ------------------ | ----------------------------- | ----------------------------------- |
| `tit:`          | Búsqueda en el título   | `[Title]`          | `tit:robot`                   | `robot[Title]`                      |
| `abs:`          | Búsqueda en el abstract | `[Abstract]`       | `abs:vision`                  | `vision[Abstract]`                  |
| *(sin prefijo)* | Búsqueda global         | `[Title/Abstract]` | `navigation`                  | `navigation[Title/Abstract]`        |
| `AND`           | Operador lógico AND     | `AND`              | `robot AND vision`            | `robot AND vision`                  |
| `OR`            | Operador lógico OR      | `OR`               | `robot OR automata`           | `robot OR automata`                 |
| `(` `)`         | Agrupación              | `(` `)`            | `(tit:robot OR tit:automata)` | `(robot[Title] OR automata[Title])` |

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
