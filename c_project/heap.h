#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <string.h>
#include "program.h"

#define PARENT(i) (i-1)/2               /* Determina o índice do Pai de um determinado Nodo. */
#define LEFT(i) 2*i + 1                 /* Determina o Nodo à esquerda de um determinado Nodo. */   
#define RIGHT(i) 2*i + 2                /* Determina o Nodo à direita de um determinado Nodo. */

Heap initHeap(int size);

int insertHeap(Heap h,int count , char* id );

long extractMax(Heap h);

long extractMaxWords(Heap h,long *posicao);

void bubbleDown(Heap h, int N);

void swap(Heap h, int a, int b);

void bubbleUp(Heap h, int N);


#endif
