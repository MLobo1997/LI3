#include "program.h"
#include "00-init.h"
#include "00-load.h"
#include "contributors.h"
#include "clean.h"

long all_articles(TAD_istruct qs);

long unique_articles(TAD_istruct qs);

long all_revisions(TAD_istruct qs);

char* article_title(long article_id, TAD_istruct qs);

char* article_timestamp(long article_id, long revision_id, TAD_istruct qs);
