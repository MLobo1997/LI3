#ifndef PROGRAM_H_
#define PROGRAM_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "interface.h"

#define HASHSIZE 89

/*Estrutura alocada em cada posição da lista ligada das revisoes*/
typedef struct revisao {
    char *id;
    char *timestamp;
    char *content; /*texto de cada revisão*/
}*REVISION;

/*Estrutura alocada em cada nodo da árvore binária balanceada dos contribuidores*/
typedef struct contribuidor {
    char *id;
    int contN; /*Numero de contribuicoes*/
    char *nome;
}*CONT;

typedef GSList *RevList;

/*Estrutura alocada em cada nodo da árvore binária balanceada dos artigos*/
typedef struct artigo {
    char *id;
    char *titulo;
    RevList revisao; /*lista ligada que contém as revisões deste artigo*/
}*ART;

typedef GTree *ArtTree;
typedef GTree *CTree;

typedef GPtrArray *TreeHash;

typedef struct elemento{
    char *id;
    long count; /*número de palavras do texto ou tamanho do texto ou número de vezes que um contribuidor contribuiu, dependendo onde é criada a heap*/
}elem;

typedef struct heap{
    int   size; /* Tamanho alocado para a Heap.*/
    int   used; /* Número de elementos da Heap. */
    elem *array;
}*Heap;

typedef GPtrArray *xmlArray;

typedef struct TCD_istruct {
    TreeHash treeTable; /*Hash table em que cada posição tem uma Árvore Binária Balanceada de artigos*/
    xmlArray xmlInfo; /*Array para guardar as árvores resultantes do parsing*/
    CTree ContriTree; /*Árvore para as queries dos contribuidores*/
    Heap TopN; /*Heap da querie Top_N_articles_with_more_words, é guardada na estrutura principal caso haja uma segunda chamada à querie.*/
    Heap Top20; /*Heap da querie Top_20_largest_articles, é guardada na estrutura principal porque as duas queries de texto são resolvidas ao mesmo tempo porque a contagem  das palavras/tamanho é feita ao mesmo tempo.*/
    long topCont[10]; /*Array com o output da querie top_10_contributors, caso haja uma segunda chamada à querie*/
    long Atop20[20]; /*Array com o output da querie top_20_largest_articles, caso haja uma segunda chamada à querie*/
    long *AtopN; /*Apontador que terá o output da querie Top_N_articles_with_more_words*/
    char **pref; /*Apontador que terá o output da querie Title_with_pref*/
    long numeroArtigos; /*número de artigos únicos */
    long numeroRevisoes;/*número de revisões */
    long numeroTotal; /*numero total de artigos */
    long numeroContributor; /*numero total de contribuidores*/
}*TAD_istruct;

#endif
