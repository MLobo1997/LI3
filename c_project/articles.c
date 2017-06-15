#include "articles.h"

/**\ QUERY 1:Número de artigos encontrados nos backups analisados(artigos duplicados em backups sucessivos e novas revisões são tomadas em conta)
 *@param qs  Estrutura global
 *@return  	 Número de artigos
 */
long all_articles(TAD_istruct qs)
{
    return(qs->numeroTotal);
}

/**\ QUERY 2:Número de artigos únicos encontrados nos backups analisados
 *@param qs  Estrutura global
 *@return  	 Número de artigos únicos
 */
long unique_articles(TAD_istruct qs)
{
    return(qs->numeroArtigos);
}

/**\ QUERY 3: Número de revisões dos artigos encontrados nos backups analisados
 *@param qs  Estrutura global
 *@return  	 Número de revisões
 */
long all_revisions(TAD_istruct qs)
{
    return(qs->numeroRevisoes);
}

/**\ QUERY 7:Dado o id do atigo devolve o seu titulo
 *@param article_id  Id do artigo
 *@param qs  		 Estrutura global
 *@return  			 Titulo do artigo do respetivo id
 */

char* article_title(long article_id, TAD_istruct qs)
{
    const int n = snprintf(NULL, 0, "%lu",article_id);
    char buf[n+1];
    char* s=LtoS(article_id,buf,n);

    ART art=newArticle(s,NULL,NULL);
    ART novo = procuraArtigo(qs->treeTable,art);
    freeArt(art,art,NULL);
    if(novo==NULL)
        return NULL;
    else
        return (novo->titulo);
}

/**\ QUERY 10: Data de uma certa revisão de um artigo
 *@param article_id   Id do artigo que possui a revisão
 *@param revision_id  Id da revisão que possui a data a devolver
 *@param qs           Estrutura global
 *@return  	 		  Data daquela revisão de um artigo
 */

char* article_timestamp(long article_id, long revision_id, TAD_istruct qs)
{
    const int n1 = snprintf(NULL, 0, "%lu",article_id);
    const int n2 = snprintf(NULL, 0, "%lu", revision_id);
    char buf1[n1+1];
    char buf2[n2+1];
    char* s1=LtoS(article_id, buf1,n1);
    char* s2=LtoS(revision_id, buf2,n2);

    ART art=newArticle(s1,NULL,NULL);
    REVISION aux =newRevision(s2,NULL,NULL);
    ART res=procuraArtigo(qs->treeTable,art);
    freeArt(art,art,NULL);
    if(res != NULL) {
        RevList rev = g_slist_find_custom(res->revisao, aux,(GCompareFunc) revIDcmp);
        freeRev(aux);
        if( rev == NULL)
            return NULL;
        else
            return ((REVISION) rev->data)->timestamp;
    } else
        freeRev(aux);

    return NULL;
}


