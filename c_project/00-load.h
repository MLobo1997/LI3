#ifndef LOAD_H_
#define LOAD_H_

#include "program.h"
#include "parse.h"
#include "00-init.h"
#include <assert.h>

TAD_istruct load (TAD_istruct qs, int nsnaps, char * snaps_paths[]);

void carregaArvores(TAD_istruct qs,int nsnaps);

void addArvore(TAD_istruct qs, xmlNodePtr t);

ART carregaArtigo(xmlNodePtr t,CONT *cont);

REVISION carregaRevisao(xmlNodePtr t,CONT *cont);

void insereRevisao(TAD_istruct qs, ART art,CONT cont);

ART procuraArtigo(TreeHash t, ART art);

void insereArtigo(TAD_istruct qs, ART art);

void insereArtArv(ArtTree t, ART art);

ART procuraArtArv(ArtTree a, ART art);

xmlNodePtr xmlGetHead(xmlDocPtr t);

int isContent(xmlNodePtr n);

int isContributor(xmlNodePtr n);

int isTimestamp(xmlNodePtr n);

int isRevision(xmlNodePtr n);

int isTitle(xmlNodePtr n);

int isID(xmlNodePtr n);

int isPage(xmlNodePtr n);

int isTree(xmlNodePtr n);

int artigoHash(ART a);

xmlNodePtr xmlNextSibling(xmlNodePtr p);

gint revIDcmp(REVISION rev1, REVISION rev2);

char *getNodeContent(xmlNodePtr cur);

void insereCont(TAD_istruct qs, CONT cont);

CONT carregaCont(xmlNodePtr t);

#endif
