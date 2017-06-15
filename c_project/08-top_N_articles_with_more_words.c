#include "08-top_N_articles_with_more_words.h"
#include <assert.h>


/**\ Conta as palavras e o tamanho de um texto
 *@param buf    Texto
 *@param valor  Array onde vai ser guardado o resultado. Na primeira posição o numero de palavras e na segunda o tamanho do texto
 *@return    Array com o tamanho e palavras do texto
 */
void count (char *buf,long *valor)
{
    long i=0,w=0;
    for (i=0; buf[i]; ++i) {
        if ((buf[i]!=' ' && buf[i]!='\t' && buf[i]!='\n') && (buf[i+1]==' ' || buf[i+1]=='\0' || buf[i+1]=='\t' ||  buf[i+1]=='\n'))
            ++w;
    }
    valor[0] = w;
    valor[1] = i;
}


/**\ Insere na Heap o id do artigo e o numero de palavas e tamanho desse artigo
 *@param key  		Chave da arvore dos artigos
 *@param artigo1 	Valor da arvore dos artigos
 *@param qs  		Estrutura global
 *@return  	   		False se conseguir inserir
 */

gboolean insere_Heap(ART key ,ART artigo1, TAD_istruct qs)
{
    long word[2];
    long maiorWord[2]= {-1};
    int nIndex;
    RevList node;
    RevList lista = key->revisao;

    for (nIndex = 0; (node = g_slist_nth (lista, nIndex)); nIndex++) {
        count(((REVISION) node->data)->content,word);
        if(word[0]>maiorWord[0])
            maiorWord[0]=word[0];
        if(word[1]>maiorWord[1])
            maiorWord[1]=word[1];
    }
    insertHeap((qs->TopN),maiorWord[0],artigo1->id);
    insertHeap((qs->Top20),maiorWord[1],artigo1->id);

    return FALSE;
}

/**\ Percorre a arvore dos artigos para inserir cada um na heap com o respetivo valor de interesse
 *@param key   Arvore de artigos
 *@param qs    Estrutura global
 *@return  	   False
 */


gboolean percorre_arv(ArtTree key, TAD_istruct qs)
{
    g_tree_foreach(key,(GTraverseFunc) insere_Heap,qs);
    return FALSE;
}

/**\ n artigos que pussuem textos de maior palavras
 *@param n   Número de artigos a devolver
 *@param qs  Estrutura global
 *@return  	 Array com  os identificadores(id's) dos n artigos com mais palavras
 */

long* top_N_articles_with_more_words(int n, TAD_istruct qs)
{
    if(qs->AtopN != NULL) {
        free(qs->AtopN);
        qs->AtopN = NULL;
    }
    qs->AtopN = malloc(n*sizeof(long));
    newArray(qs->AtopN,n);
    long aux[n];
    if(qs->Atop20[0]==-1) {
        (qs->TopN)=initHeap(qs->numeroArtigos);
        (qs->Top20)=initHeap(qs->numeroArtigos);
        g_ptr_array_foreach(qs->treeTable,(GFunc) percorre_arv,qs);
        for(int i=0; i<20; i++) {
            qs->Atop20[i]=extractMax(qs->Top20);
        }
    }
    for(int j=0; j<n; j++) {
        qs->AtopN[j]=extractMaxWords(qs->TopN,&aux[j]);
    }

    for(int j=0; j<n; j++) {
        const int n1 = snprintf(NULL, 0, "%lu",qs->AtopN[j]);
        char buf[n1+1];
        char* id=LtoS(qs->AtopN[j], buf,n1);
        insertHeap((qs->TopN),aux[j],id);
    }

    return(qs->AtopN);
}
