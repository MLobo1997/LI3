#include "program.h"
#include "00-init.h"
#include "heap.h"
#include "clean.h"
char* LtoS(long c,char* buf, int n);

char* contributor_name(long contributor_id, TAD_istruct qs);

long* top_10_contributors(TAD_istruct qs);

gboolean insere_contri(CONT key,CONT value, Heap h);
