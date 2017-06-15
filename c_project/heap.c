#include "heap.h"
#include <assert.h>

/**\ Aloca a heap com um determinado tamanho
  @param size    Tamanho da heap;
  @return        Heap
  */
Heap initHeap(int size)
{
    Heap h = malloc(sizeof(struct heap));
    if(h != NULL) {
        h->size = size;
        h->used = 0;
        h->array=malloc(size*sizeof(struct elemento));
    }
    return h;
}

/**\ Insire um elemento(id e count) na Heap mantendo o invariante que o pai é sempre maior que os filhos
 *@param h        heap onde queremos inserir o elemento
 *@param count    paramentro que queremos inserir
 *@param id       id relacionado com o count que queremos inserir
 */

int insertHeap(Heap h,int count , char *id )
{
    if (h->used == h->size) {
        h->array= realloc(h->array, 2*(h->size)*sizeof(struct elemento));
        h->size *= 2;
    }
    assert( h!= NULL);
    h->array[h->used].count= count;
    h->array[h->used].id= g_strdup(id);
    (h->used)++;
    bubbleUp(h, h->used-1);
    return 1;
}


/**\ Remover a cabeça da heap(o maior elemento) mantendo o invariante que o pai é sempre maior que os filhos.
Esta função é utilizada pela top-N_articles_with_more_words. É guardado o count(neste caso, número de palavras) de cada id para se conseguir repor a Heap depois de remover os elementos;
 *@param h       heap
 *@param buff    Endereço onde vamos guarda o campo count
 *@return        O id do maior elemento da heap
 */
long extractMaxWords(Heap h,long *buff)
{
    if (h->used > 0) {
        elem novo=h->array[0];
        long maior =atoi(novo.id);
        *buff=novo.count;
        free(novo.id);
        h->array[0] = h->array[h->used-1];
        (h->used)--;
        bubbleDown(h, h->used);
        return maior;
    } else return -1;
}

/**\ Remover a cabeça da heap(o maior elemento) mantendo o invariante que o pai é sempre maior que os filhos.
 *@param h       heap
 *@return        O id do maior elemento da heap
 */
long extractMax(Heap h)
{
    if (h->used > 0) {
        elem novo= h->array[0];
        long res=atoi(novo.id);
        free(novo.id);
        h->array[0] = h->array[h->used-1];
        (h->used)--;
        bubbleDown(h, h->used);
        return res;
    } else return -1;
}

/**\ Faz o swap de dois elementos da heap
 *@param h       heap
 *@param a       Elemento para trocar de posição com b
 *@param b       Elemento para trocar de posição com a
*/
void swap(Heap h, int a, int b)
{
    elem t = h->array[a];
    h->array[a] = h->array[b];
    h->array[b] = t;
}

/**\ Função que após inserção de um elemento na Heap,coloca esse elemento na posição correta
 *@param h       heap
 *@param i       Quantos elementos existem na heap
*/
void bubbleUp(Heap h, int i)
{
    while (i!=0 && h->array[i].count > h->array[PARENT(i)].count) {
        swap(h, i, PARENT(i));
        i = PARENT(i);
    }
}

/**\ Função que após remoção de um elemento na Heap, mantém o invariante que os pai é sempre maior que os filhos, fazendo os swaps necessarios para tal
 *@param h       heap
 *@param N       Quantos elementos existem na heap
*/
void bubbleDown(Heap h, int N)
{
    int i = 0, max ;
    while (RIGHT(i) < N && h->array[max = h->array[LEFT(i)].count > h->array[RIGHT(i)].count ? LEFT(i) : RIGHT(i)].count > h->array[i].count) {
        swap(h, i, max);
        i = max;
    }
    if (LEFT(i) < N && h->array[LEFT(i)].count > h->array[i].count)
        swap(h, i, LEFT(i));
}
