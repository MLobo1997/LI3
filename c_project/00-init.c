#include "00-init.h"
#include <libxml2/libxml/tree.h>
#include <assert.h>
#include "clean.h"
/**\ Aloca a struct de uma revisão.
  @param id           Apontador para o Id da revisão.
  @param timestamp    Apontador para timestamp da revisão.
  @param content      Apontador para o texto do artigo.
  @return             Endereço da revisão.
  */
REVISION newRevision(char *id, char *timestamp, char *content)
{
    REVISION r = (REVISION) malloc(sizeof(struct revisao));

    if(r != NULL) {
        r->id = id;
        r->timestamp = timestamp;
        r->content = content;
    }
    return r;
}

/**\ Aloca a struct de um contribuidor
  @param id           Id de um contribuidor.
  @param contN        Número de contribuidores.
  @param nome         Apontador para nome do contribuidor.
  @return             Endereço da contribuidor.
  */

CONT newContributor(char *id, int contN, char *nome)
{
    CONT r = (CONT) malloc(sizeof(struct contribuidor));
    if(r != NULL) {
        r->id = id;
        r->contN = contN;
        r->nome = nome;
    }
    return r;
}

/**\ Aloca a lista de revisões.
  @param rev  Revisão
  @return     Endereço da lista.
  */
RevList newRevList(REVISION rev)
{
    RevList r = NULL;
    r = g_slist_prepend(r,rev);
    return r;
}

/**\ Aloca um artigo.
  @param id   	  Id do artigo.
  @param titulo   Apontador para o título do artigo.
  @param revisao  Lista de todas as revisões associadas ao artigo.
  @return     	  Endereço do artigo.
  */
ART newArticle(char *id, char *titulo, REVISION revisao)
{
    ART r = (ART) malloc(sizeof(struct artigo));
    if(r != NULL) {
        r->id = id;
        r->titulo = titulo;
        r->revisao = newRevList(revisao);
    }
    return r;
}

/**\ Função de comparação entre artigos para a inserção em árvores binárias, em função dos ID's
  @param art1  Artigo a ser inserido.
  @param art2  Artigo ao qual art1 está a ser comparado.
  @return      Valor de comparação <, =, ou > que 0.
  */
gint IDcmp(ART art1, ART art2)
{
    return strcmp(art1->id,art2->id);
}

/**\ Função de comparação entre revisões para a inserção na lista ligada, em função dos ID's
  @param rev1  Revisão a ser inserida.
  @param rev2  Revisão ao qual rev1 está a ser comparado.
  @return      Valor de comparação <, =, ou > que 0.
  */
gint revIDcmp(REVISION rev1, REVISION rev2)
{
    return g_strcmp0(rev1->id,rev2->id);
}

/**\ Alocação de uma árvore de procura balanceada de artigos.
  @return       Árvore de procura balanceada de artigos.
  */
ArtTree newArtTree(void)
{
    ArtTree r;
    r = g_tree_new((GCompareFunc) IDcmp);
    assert(r!=NULL);
    return r;
}

/**\ Função de comparação entre contribuidores para a inserção em árvores binárias, em função dos ID's
  @param cont1  Contribuidor a ser inserido.
  @param cont2  Contribuidor ao qual art1 está a ser comparado.
  @return      Valor de comparação <, =, ou > que 0.
  */

gint ID_contri_cmp(CONT cont1, CONT cont2)
{
    return strcmp(cont1->id,cont2->id);
}

/**\ Alocação de uma árvore de procura balanceada de contribuidores.
  @return       Árvore de procura balanceada de contribuidores.
  */

CTree newCTree()
{
    CTree r=NULL;
    r=g_tree_new((GCompareFunc) ID_contri_cmp);
    assert(r!=NULL);
    return r;
}

/**\ Alocação de de um array de tamanho n com todas as posições a -1.
 *@param array   Array
 *@param n       Tamanho do array
 */
void newArray(long *array,int n)
{
    memset(array,-1,n);
}

/**\ Alocação de uma Hash Table de árvores de procura balanceadas de artigos
  @return       Uma Hash Table de árvores de procura balanceadas de artigos.
  */

TreeHash newTreeHash(void )
{
    TreeHash r =NULL;
    r=g_ptr_array_sized_new(HASHSIZE);
    g_ptr_array_set_size(r,HASHSIZE);
    g_ptr_array_set_free_func(r, (GDestroyNotify) freeArtTree);
    return r;
}

/**\ Alocação de um array que carrega as árvores criadas pela libxml.
 * @return Array.
 */
xmlArray newXmlArray(void )
{

    xmlArray r = (xmlArray) g_ptr_array_new();
    if(r != NULL)
        g_ptr_array_set_free_func(r, (GDestroyNotify) xmlFreeDoc);

    return r;
}

/**\ Aloca um array de strings.
 * @param r String a ser alocada como 1o elemento.
 * @return Array de strings.
 */
char **newStringArray(char *r)
{
    char **s;
    s = (char**) malloc(sizeof(char*));
    if(s!=NULL)
        s[0] = r;

    return s;
}
/**\ Alocação de todas as estruturas necessárias
  @return     TAD_istruct
  */
TAD_istruct init()
{
    TAD_istruct r;
    r=(TAD_istruct) malloc (sizeof(struct TCD_istruct));

    if(r!=NULL) {
        r->treeTable = newTreeHash();
        r->xmlInfo = newXmlArray();
        r->ContriTree=newCTree();
        r->TopN = NULL;
        r->Top20 =NULL;
        newArray(r->topCont,10);
        newArray(r->Atop20,20);
        r->AtopN =NULL;
        r->pref = newStringArray(NULL);
        r->numeroArtigos=0;
        r->numeroRevisoes=0;
        r->numeroTotal=0;
        r->numeroContributor=0;
    }
    return r;
}
