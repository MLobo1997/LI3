#include "contributors.h"
#include "clean.h"


/**\ Conversão entre o tipo long para string
 *@param c      o conteudo que vai ser convertido a String
 *@param buf    onde vai ser guadada a String da conversão
 *@param n      tamanho
 *@return       Tipo em String
 */

char* LtoS(long c,char* buf, int n)
{
    snprintf(buf, n+1, "%lu", c);
    return buf;
}

/**\ QUERY 05:Dado o id do autor devolve o seu nome
 *@param contributor_id  Id do autor
 *@param qs              Estrutura global
 *@return                Nome do autor do respetivo id
 */

char* contributor_name(long contributor_id, TAD_istruct qs)
{
    const int n = snprintf(NULL, 0, "%lu",contributor_id);
    char buf[n+1];
    char* s=LtoS(contributor_id, buf,n);

    CONT cont=newContributor(s,0,NULL);
    CONT res=g_tree_lookup(qs->ContriTree,cont);
    freeCont(cont,cont,NULL);
    if(res==NULL)
        return NULL;
    else
        return res->nome;
}

/**\ Insere na Heap um contribuidor
 *@param key   Chave da arvore dos contribuidores
 *@param value Valor da arvore dos contribuidores
 *@param h     Heap onde vão ser iseridos os contribuidores
 *@return  	   False se conseguir inserir
 */

gboolean insere_contri(CONT key,CONT value, Heap h)
{
    if(key!=NULL)
        insertHeap(h,value->contN,value->id);
    return FALSE;
}

/**\ QUERY 04: Id's dos 10 autores que contríbuiram para um maior número de versões de um artigo
 *@param qs  Estrutura global
 *@return  	 Array com  os identificadores(id's) dos 10 autores
 */

long* top_10_contributors(TAD_istruct qs)
{
    if(qs->topCont[0]==-1) {
        Heap h=initHeap(qs->numeroContributor);
        g_tree_foreach(qs->ContriTree,(GTraverseFunc) insere_contri,h);
        for(int i=0; i<10; i++) {
            qs->topCont[i]=extractMax(h);
        }
        freeHeap(h);
    }

    return qs->topCont;
}
