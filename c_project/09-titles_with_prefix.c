#include "09-titles_with_prefix.h"
#include "00-init.h"
#include "clean.h"

/**\ Estrutura criada para existir compatibilidade com a glib.
 */
typedef struct data {
    char ***r; // Apontador para estrutura de array de Strings que transporta os títulos que têm o prefixo.
    int used;  // Número de título em r.
    int size; // Espaço alocado para títulos.
    char *prefix;  //Prefixo a ser encontrado.
}*Data;

/**\ Cria uma estrutura do tipo Data.
 * @param r Apontador para estrutura de array de Strings que transporta os títulos que têm o prefixo.
 * @param used Número de título em r.
 * @param size Espaço alocado para títulos.
 * @param prefix Prefixo a ser encontrado.
 */
Data newData(char ***r, int used, int size, char *prefix)
{
    Data n = (Data) malloc(sizeof(struct data));
    if(n != NULL) {
        n->r = r;
        n->used = used;
        n->size = size;
        n->prefix = prefix;
    }
    return n;
}

/**\ Liberta uma estrutura do tipo Data.
 *@param d  Estrutura criada para transportar o prefixo e depositar os títulos.
 */
void freeData(Data d)
{
    for(int i = 0 ; i < d->used ; i++)
        g_free((d->r)[i]);

    free(d);
}

/**\ Função de inserção ordenada de uma string num array de strings.
 * @param r Array de strings.
 * @param N Número de elementos no array de strings.
 * @param str String a ser inserida.
 */
void insertString(char **r, int N, char *str)
{
    int i = N/2;

    if(N > 0) {
        if(g_strcmp0(str,r[i]) < 0)
            while(i > 0 && g_strcmp0(str,r[i - 1]) < 0)
                i--;
        else
            while(i < N && g_strcmp0(str,r[i]) > 0)
                i++;
    }

    for(int i2 = N ; i < i2; i2--)
        r[i2] = r[i2-1];

    r[i] = str;

}

/**\ Adiciona uma string à estrutura de transporte.
 *@param str    String a ser adicionada.
 *@param d      Estrutura criada para transportar o prefixo e depositar os títulos.
 */
void addToArray(char *str, Data d)
{
    if(*(d->r) != NULL) {
        if(d->used >= d->size - 1) {
            d->size *= 2;
            *(d->r) = (char **) realloc(*(d->r), sizeof(char*) * (d->size));
        }
        (*(d->r))[d->used - 1] = str;
        (*(d->r))[d->used] = NULL;
        (d->used)++;
    }
}

/**\ Função aplicada em foreach às ArtTree's que verifica se o título tem o prefixo e nesse caso guarda-o.
 *@param key    Artigo a ser tratado.
 *@param value  Artigo a ser tratado.
 *@param d      Estrutura criada para transportar o prefixo e depositar os títulos.
 *@return       Sempre 0, para o foreach processar sobre toda a árvore.
 */
int prefix_titles_Art(ART key, ART value, Data d)
{
    if(key != NULL) {
        if(g_str_has_prefix(value->titulo, d->prefix)) {
            addToArray(value->titulo, d);
        }
    }
    return 0;
}

/**\ Função aplicada em foreach à TreeHash que recolhe todos os títulos com um determinado prefixo de uma ArtTree.
 *@param t Árvore de artigos.
 *@param d Estrutura criada para transportar o prefixo e depositar os títulos.
 */
void prefix_titles_TreeHash(ArtTree t, Data d)
{
    g_tree_foreach(t, (GTraverseFunc) prefix_titles_Art, d);
}

/**\ Função de comparação entre dois elementos de uma estrutura do tipo char**.
 * @param a   Endereço a apontar para uma string.
 * @param b   Endereço a apontar para uma string.
 * @return    True or False, pelo mesmo critério de strcmp.
 */
int cmpfunc (const void * a, const void * b)
{

    const char **ia = (const char **)a;
    const char **ib = (const char **)b;

    return(g_strcmp0(*ia, *ib));
}

/**\ Query pedida no enunciado, devolve todos os títulos de artigos que têm um determinado prefixo.
 * @param prefix    Prefixo a ser encontrado.
 * @param qs        Estrutura onde se encontra toda a informação.
 * @return          Array de strings com todos os títulos correspondentes e ordenados alfabeticamente.
 */

char** titles_with_prefix(char* prefix, TAD_istruct qs)
{
    if(*(qs->pref) != NULL) {
        free(qs->pref);
        qs->pref =newStringArray(NULL);
    }

    Data d = newData(&(qs->pref), 1, 1, prefix);

    g_ptr_array_foreach(qs->treeTable, (GFunc) prefix_titles_TreeHash, d);

    qsort(qs->pref, d->used - 1, sizeof(char*), cmpfunc);
    free(d);
    return qs->pref;
}
