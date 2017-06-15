#include "00-load.h"
#include "clean.h"

/**\ Devolve o apontador do irmão seguinte do nodo recebido.
 *@param p  Nodo.
 *@return Irmão.
 */
xmlNodePtr xmlNextSibling(xmlNodePtr p)
{
    return (p->next);
}
/**\ Hash do id de um determinado artigo
 *@param a  Artigo para o qual vai ser calculado a Hash
 *@return   Hash
 */
int artigoHash(ART a)
{
    assert((a->id)!= NULL);
    return(atoi(a->id) % HASHSIZE);
}

/**\ Avalia se um determinado nodo é mediawiki, ou seja a cabeça de uma árvore xml.
 *@param n  Node da estrutura de libxml
 *@return   Boleano da comparaçao
 */
int isTree(xmlNodePtr n)
{
    return strcmp("mediawiki", (char *) n->name);
}

/**\ Avalia se um determinado nodo é Page
 *@param n  Node da estrutura de libxml
 *@return   Boleano da comparaçao
 */
int isPage(xmlNodePtr n)
{
    return strcmp("page", (char *) n->name);
}

/**\ Avalia se um determinado nodo é IP
 *@param n  Node da estrutura de libxml
 *@return   Boleano da comparaçao
 */

int isIP(xmlNodePtr n)
{
    return strcmp("ip", (char*) n->name);
}
/**\ Avalia se um determinado nodo é username
 *@param n  Node da estrutura de libxml
 *@return   Boleano da comparaçao
 */
int isNome(xmlNodePtr n)
{
    return strcmp("username", (char*) n->name);
}

/**\ Avalia se um determinado nodo é ID
 *@param n  Node da estrutura de libxml
 *@return   Boleano da comparaçao
 */
int isID(xmlNodePtr n)
{
    return strcmp("id", (char *) n->name);
}

/**\ Avalia se um determinado nodo é Title
 *@param n  Node da estrutura de libxml
 *@return   Boleano da comparaçao
 */
int isTitle(xmlNodePtr n)
{
    return strcmp("title", (char *) n->name);
}

/**\ Avalia se um determinado nodo é Revision
 *@param n  Node da estrutura de libxml
 *@return   Boleano da comparaçao
 */
int isRevision(xmlNodePtr n)
{
    return strcmp("revision", (char *) n->name);
}

/**\ Avalia se um determinado nodo é Timestamp
 *@param n  Node da estrutura de libxml
 *@return   Boleano da comparaçao
 */
int isTimestamp(xmlNodePtr n)
{
    return strcmp("timestamp", (char *) n->name);
}

/**\ Avalia se um determinado nodo é Contribuitor
 *@param n  Node da estrutura de libxml
 *@return   Boleano da comparaçao
 */
int isContributor(xmlNodePtr n)
{
    return strcmp("contributor", (char *) n->name);
}

/**\ Avalia se um determinado nodo é Content
 *@param n  Node da estrutura de libxml
 *@return   Boleano da comparaçao
 */
int isContent(xmlNodePtr n)
{
    return strcmp("text", (char *) n->name);
}

/**\ Devolve o primeiro nodo da arvore criada pela libxmlsoft
 *@param t  Estrutura criada pela libxml
 *@return   Primeiro nodo da arvore de parsing
 */
xmlNodePtr xmlGetHead(xmlDocPtr t)
{
    return (t->children);
}

/**\ Devolve  o conteudo do nodo do libxml
 *@param cur  Nodo da estrutura de libxml
 *@return     Retorna o apontar para o texto
 */
char *getNodeContent(xmlNodePtr cur)
{
    char *r = NULL;
    if(xmlNodeIsText(cur))
        r = (char *) cur->content;
    else if(xmlNodeIsText(cur->children))
        r = (char *) cur->children->content;

    assert(r!=NULL);
    return r;
}

/**\ Insire um artigo(nodo) numa Arvore de artigos
 *@param t      arvore onde queremos inserir artigo
 *@param art    artigo que queremos inserir
 */
void insereArtArv(ArtTree t, ART art)
{
    g_tree_insert(t,art, art);
}

/**\ Insere um artigo numa treeHash , apos calcular o index com a funçao de hash e adicionar a sua arvore repetiva
 *@param qs     Estrutura que contém a treeHash onde queremos inserir artigo
 *@param art    artigo que queremos inserir
 */
void insereArtigo(TAD_istruct qs, ART art)
{
    TreeHash h = qs->treeTable;
    ArtTree aux=g_ptr_array_index(h,artigoHash(art));
    if(aux==NULL) {
        ArtTree nova = newArtTree();
        insereArtArv(nova,art);
        g_ptr_array_insert (h,artigoHash(art),nova);
        g_ptr_array_remove_index(h,(artigoHash(art))+1);
    } else {
        insereArtArv((ArtTree) g_ptr_array_index(h,artigoHash(art)), art);
    }
}

/**\ Procura Artigo numa arvore de artigos
 *@param a      arvore onde queremos procurar artigo
 *@param art    artigo que queremos procurar
 *@return       Pointer para o artigo da arvore ou NULL
 */
ART procuraArtArv(ArtTree a, ART art)
{
    assert((art->id)!=NULL);
    if(a==NULL)
        return NULL;
    else
        return g_tree_lookup(a,art);
}

/**\ Procura artigo numa treeHash
 *@param t      treeHash onde queremos procurar artigo
 *@param art    artigo que queremos procurar
 *@return       Pointer para o artigo da arvore ou NULL
 */
ART procuraArtigo(TreeHash t, ART art)
{
    assert((art->id) != NULL);
    ArtTree aux = (g_ptr_array_index(t,artigoHash(art)));
    if(aux != NULL)
        return procuraArtArv(aux,art);
    else
        return NULL;
}
/**\ Insere Revisão na lista ligada
 *@param qs     Estrutura global
 *@param art    artigo que contem a revisão que queremos inserir
 *@param cont    contribuidor que contém a informação que queremos inserir acerca do contribuidor
*/
void insereRevisao(TAD_istruct qs, ART art,CONT cont)
{
    ART aux= procuraArtigo(qs->treeTable,art);
    if(g_slist_find_custom(aux->revisao,((REVISION)(art->revisao->data)),(GCompareFunc) revIDcmp) == NULL) {
        qs->numeroRevisoes++;
        REVISION test=((RevList)art->revisao)->data;
        ((RevList)art->revisao)->data=NULL;
        freeArt(art,art,NULL);
        aux->revisao = g_slist_prepend(aux->revisao,test);
        if(cont!=NULL)
            insereCont(qs,cont);
        else
            freeCont(cont, cont, NULL);

    } else {
        freeArt(art,art,NULL);
        freeCont(cont,cont,NULL);
    }
}

/**\ Carrega as informações de uma revisao para a estrutura REVISION e a informação do contribuidor para a estrutura CONT
 *@param t       Nodo de revisao
 *@param cont    Estrutura CONT onde vamos carregar a informação do contribuidor desta revisão
 *@return        REVISION
 */

REVISION carregaRevisao(xmlNodePtr t,CONT *cont)
{

    char *id=NULL, *timestamp=NULL, *content=NULL;
    char *aux=NULL;
    xmlNodePtr tmp = t->children;
    int flagContent=0;
    while(tmp != NULL) {
        if(isID(tmp) == 0) {
            id=getNodeContent(tmp);
        } else if(isTimestamp(tmp) == 0) {
            timestamp=getNodeContent(tmp);
        } else if(flagContent==0 && isContent(tmp)==0) {
            aux= getNodeContent(tmp);
            if(tmp->children!=NULL) {
                content=aux;
                flagContent=1;
            }
        } else if(isContributor(tmp)==0) {
            *cont=carregaCont(tmp);
        }
        tmp = xmlNextSibling(tmp);
    }
    assert(content != NULL);
    return newRevision(id, timestamp, content);
}




/**\ Carrega as informações de um artigo para uma estrutura concebida para o mesmo.
  *@param t       Nodo de artigo.
  *@param cont    Estrutura CONT onde vamos carregar a informação do contribuidor qd encontrarmos a respetiva tag
  *@return        Artigo.
 */
ART carregaArtigo(xmlNodePtr t,CONT *cont)
{
    char *id=NULL;
    char *titulo=NULL;
    REVISION rev=NULL;
    xmlNodePtr tmp = t->children;

    while(tmp != NULL) {
        if(isTitle(tmp) == 0) {
            titulo=getNodeContent(tmp);
        } else if(isID(tmp) == 0) {
            id=getNodeContent(tmp);
        } else if(isRevision(tmp) == 0) {
            rev = carregaRevisao(tmp,cont);
            assert(rev!= NULL);
        }
        tmp = xmlNextSibling(tmp);
    }
    return newArticle(id, titulo, rev);
}
/**\ Carrega as informações de um artigo para uma estrutura concebida para o mesmo.
  @param t  Nodo de artigo.
  @return   Contribuidores.
 */

CONT carregaCont(xmlNodePtr t)
{
    char *id=NULL;
    int contN=1;
    char *nome=NULL;
    xmlNodePtr tmp=t->children;

    while(tmp!=NULL) {
        if(isIP(tmp)==0) {
            return  NULL;
        }
        if(isID(tmp)==0) {
            id=getNodeContent(tmp);
        } else if(isNome(tmp)==0) {
            nome=getNodeContent(tmp);
        }
        tmp=xmlNextSibling(tmp);
    }
    return newContributor(id,contN,nome);
}

/**\ Insere um contribuidor na Árvore
 *@param qs     Estrutura global
 *@param cont   Estrutura CONT onde vamos inserir a informação do contribuidor
 */

void insereCont(TAD_istruct qs, CONT cont)
{
    if(qs->ContriTree!=NULL) {
        CONT res=g_tree_lookup(qs->ContriTree,cont);
        if(res!=NULL) {
            res->contN ++;
            freeCont(cont,cont,NULL);
        } else {
            g_tree_insert(qs->ContriTree,cont,cont);
            qs->numeroContributor++;
        }
    } else {
        g_tree_insert(qs->ContriTree,cont,cont);
        qs->numeroContributor++;
    }
}


/**\ É adicionada uma árvore do xmlsoft à nossa estrutura de dados.
  @param qs Nossa estrutura de dados.
  @param t Cabeça de árvore de xmlsoft.
 */
void addArvore(TAD_istruct qs, xmlNodePtr t)
{
    xmlNodePtr tmp;
    ART art;
    CONT cont=NULL;

    if(isTree(t) == 0) {
        tmp = t->children;
        while(tmp != NULL) {
            if(isPage(tmp) == 0) {
                art = carregaArtigo(tmp,&cont);
                (qs->numeroTotal)++;

                if(procuraArtigo(qs->treeTable,art) != NULL) {
                    insereRevisao(qs,art,cont);
                } else {
                    qs->numeroArtigos++;
                    qs->numeroRevisoes++;
                    insereArtigo(qs, art);
                    if(cont!=NULL) {
                        insereCont(qs,cont);
                    } else
                        freeCont(cont, cont, NULL);
                }
            }
            tmp = xmlNextSibling(tmp);
        }
    }
}
/**\ De um array de árvores construídas pela biblioteca xmlsoft são carregadas as informações ou acessos às mesmas para a nossa estrutura de dados.
  @param qs Nossa estrutura de dados.
  @param nsnaps Número de árvores.
 */
void carregaArvores(TAD_istruct qs,int nsnaps)
{
    xmlDocPtr tXML = NULL;
    for(int i =0 ; i<nsnaps ; i++) {
        tXML =g_ptr_array_index(qs->xmlInfo,i);
        addArvore(qs, xmlGetHead(tXML));
    }
}
/**\ Query de carregamento.
  @param qs Estrutura de acesso aos dados.
  @param nsnaps Número de ficheiros a serem importados.
  @param snaps_paths Nome dos ficheiros a serem importados.
  @return Estrutura de acesso aos dados.
 */
TAD_istruct load (TAD_istruct qs, int nsnaps, char *snaps_paths[])
{
    qs->xmlInfo = parseMult(qs->xmlInfo, nsnaps,snaps_paths);
    carregaArvores(qs,nsnaps);
    return qs;
}
