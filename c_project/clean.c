#include "clean.h"
#include "assert.h"

/**\ Liberta uma revisão.
 * @param r Revisão.
 * @return Revisão libertada.
 */
gboolean freeRev(REVISION r)
{
    if(r != NULL)
        free(r);
    return FALSE;
}

/**\ Liberta um contribuidor.
 * @param r1   Contribuidor.
 * @param r2   Contribuidor.
 * @param null Variável sempre null para ter compatibilidade com a glib.
 * @return     Contribuidor libertado.
 */
gboolean freeCont(CONT r1, CONT r2, void* null)
{
    if(r1 != NULL)
        assert(null == NULL);
    free(r2);
    return FALSE;
}

/**\ Liberta um artigo.
 * @param r1   Artigo.
 * @param r2   Artigo.
 * @param null Variável sempre null para ter compatibilidade com a glib.
 * @return     Artigo libertado.
 */
gboolean freeArt(ART r1, ART r2, void* null)
{
    if(r1 != NULL && r2 != NULL) {
        assert(null == NULL);
        g_slist_free_full(r2->revisao, (GDestroyNotify) freeRev);
        free(r2);
    }
    return FALSE;
}

/**\ Liberta uma árvore de artigos.
 * @param r Árvore de artigos.
 * @param null Variável sempre null para ter compatibilidade com a glib.
 * @return Árvore de artigos libertada.
 */
ArtTree freeArtTree(ArtTree r, void*null)
{
    if(r != NULL) {
        assert(null == NULL);
        g_tree_foreach(r, (GTraverseFunc) freeArt, NULL);
        g_tree_destroy(r);
    }
    return r;
}

/**\ Liberta um array de ArtTree.
 * @param r Array de ArtTree.
 * @return Array de ArtTree libertado.
 */
TreeHash freeTreeHash(TreeHash r)
{
    if (r != NULL) {
        g_ptr_array_free(r, TRUE);
    }
    return r;
}

/**\ Liberta um array de árvores da libxml.
 * @param r Array de árvores da libxml.
 * @return Array de árvores da libxml libertado.
 */
xmlArray freeXmlArray(xmlArray r)
{
    if (r != NULL) {
        g_ptr_array_free(r, TRUE);
    }
    return r;
}

/**\ Liberta o conteúdo da heap.
 * @param r Conteúdo da heap.
 * @param N Numero de elementos da heap
 * @return Conteúdo da heap.
 */
elem *freeElemArray(elem *r, int N)
{
    if(r != NULL) {
        for(int i = 0 ; i < N ; i++)
            if(r[i].id != NULL)
                free(r[i].id);
        free(r);
    }
    return r;
}

/**\ Liberta uma heap.
 * @param r Heap.
 * @return Heap.
 */
Heap freeHeap(Heap r)
{
    if(r != NULL) {
        r->array = freeElemArray(r->array, r->used);
        free(r);
    }
    return r;
}

/**\ Liberta um o array de strings da query dos prefixos.
 * @param r Array de strings.
 * @return Array de strings libertado.
 */
char ** freePref(char **r)
{
    for(int i = 0 ; r[i] != NULL ; i++)
        g_free(r[i]);
    g_free(r);
    return r;
}

CTree freeCTree(CTree r)
{
    if(r != NULL) {
        g_tree_foreach(r, (GTraverseFunc) freeCont, NULL);
        g_tree_destroy(r);
    }
    return r;
}

TAD_istruct clean(TAD_istruct qs)
{
    if(qs != NULL) {
        qs->treeTable = freeTreeHash(qs->treeTable);
        qs->xmlInfo = freeXmlArray(qs->xmlInfo);
        qs->ContriTree = freeCTree(qs->ContriTree);
        qs->TopN = freeHeap(qs->TopN);
        qs->Top20 = freeHeap(qs->Top20);
        g_free(qs->AtopN);
        g_free(qs->pref);

        free(qs);
    }
    return qs;
}
