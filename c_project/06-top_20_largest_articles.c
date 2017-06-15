#include "06-top_20_largest_articles.h"

/**\ 20 artigos que pussuem textos de maior tamanho
 *@param qs  Estrutura global
 *@return  	 Array com  os identificadores(id's) dos 20 artigos
 */

long* top_20_largest_articles(TAD_istruct qs)
{
    if((qs->Atop20)[0]==-1) {
        (qs->TopN)=initHeap(qs->numeroArtigos);
        (qs->Top20)=initHeap(qs->numeroArtigos);
        g_ptr_array_foreach(qs->treeTable,(GFunc) percorre_arv,qs);
        for(int i=0; i<20; i++) {
            qs->Atop20[i]=extractMax(qs->Top20);
        }
    }
    return qs->Atop20;
}

