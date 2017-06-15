#ifndef INIT_H_
#define INIT_H_
#include "program.h"

REVISION newRevision(char *id, char *timestamp, char *content);

CONT newContributor(char *id, int contN, char *nome);

RevList newRevList(REVISION rev);

void insereArtArv(ArtTree t, ART art);

ART newArticle(char * id, char *titulo, REVISION revisao);

gint IDcmp(ART art1, ART art2);

gint revIDcmp(REVISION rev1, REVISION rev2);

ArtTree newArtTree();

CTree newCTree();

void newArray(long *array,int n);

char **newStringArray(char *r);

TreeHash newTreeHash(void);

xmlArray newXmlArray(void );

TAD_istruct init();

#endif
