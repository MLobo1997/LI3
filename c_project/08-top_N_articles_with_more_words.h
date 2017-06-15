#ifndef TOP_N_ARTICLES_WITH_MORE_WORDS
#define TOP_N_ARTICLES_WITH_MORE_WORDS
#include "program.h"
#include "contributors.h"
#include "00-init.h"
#include "heap.h"

gboolean insere_Heap(ART artigo,ART artigo1, TAD_istruct qs);
gboolean percorre_arv(ArtTree key, TAD_istruct qs);
long* top_N_articles_with_more_words(int n, TAD_istruct qs);
#endif
