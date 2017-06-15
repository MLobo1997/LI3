#include "program.h"
#include "time.h"
#include <assert.h>

int main(int argc, char **argv)
{
    double a = clock();
    char **p9;
    TAD_istruct t;
    t = init();
    if(argc>1)
        t = load(t, argc-1, &argv[1]);
    else {
        char    *snapshots[] = {"../snapshots/snapshot_dec16","../snapshots/snapshot_jan17","../snapshots/snapshot_fev17"};
        t =  load(t,3,snapshots);
    }
    /*
    printf("NUMERO TOTAL DE ARTIGOS:%ld\n",t->numeroTotal);
    printf("NUMERO ARTIGOS UNICOS: %ld\n",t->numeroArtigos);
    printf("NUMERO REVISOES: %ld\n",t->numeroRevisoes);
    */
    printf("Numero de contribuidores:%ld\n",t->numeroContributor);
    printf("01-all_articles:%ld\n",all_articles(t));
    printf("02-unique_article:%ld\n",unique_articles(t));
    printf("03-all_revision:%ld\n",all_revisions(t));
    printf("07-articleTitle:%s\n",article_title(15910,t));
    printf("07-articleTitle:%s\n",article_title(25507,t));
    printf("07-articleTitle:%s\n",article_title(0,t));
    printf("10-article_timestamp:%s\n",article_timestamp(10,631144794,t));
    printf("10-article_timestamp:%s\n",article_timestamp(12,763082287,t));
    printf("10-article_timestamp:%s\n",article_timestamp(12,755779730,t));
    printf("10-article_timestamp:%s\n",article_timestamp(12,4479730,t));
    printf("05-contributor_name:%s\n",contributor_name(28903366,t));
    printf("05-contributor_name:%s\n",contributor_name(1000,t));

    p9 = titles_with_prefix("Anax",t);

    printf("---------------------\n09-prefixos:\n");
    for(int i = 0 ; p9[i]!= NULL ; i++)
        printf("Titulo : \"%s\"\n",p9[i]);

    p9 = titles_with_prefix("Anax",t);

    printf("---------------------\n09-prefixos:\n");
    for(int i = 0 ; p9[i]!= NULL ; i++)
        printf("Titulo : \"%s\"\n",p9[i]);

    long *pCont=top_10_contributors(t);
    for(int i=0; i<10; i++) {
        printf("C %d: %ld\n",i,pCont[i]);
    }

    pCont=top_10_contributors(t);
    for(int i=0; i<10; i++) {
        printf("C %d: %ld\n",i,pCont[i]);
    }

    long *t20Maior = top_20_largest_articles(t);
    for(int i=0; i<20; i++) {
        printf("L %d: %ld\n",i,t20Maior[i]);
    }

    t20Maior = top_20_largest_articles(t);
    for(int i=0; i<20; i++) {
        printf("L %d: %ld\n",i,t20Maior[i]);
    }

    long *tWords = top_N_articles_with_more_words(10,t);
    for(int i=0; i<10; i++) {
        printf("W %d: %ld\n",i,tWords[i]);
    }
    long *tWords2 = top_N_articles_with_more_words(10,t);
    for(int i=0; i<10; i++) {
        printf("W %d: %ld\n",i,tWords2[i]);
    }
    double b = clock();
//    printf("tamanho é  %ld\n", numero(t)) ;
    printf("tempo %f\n",(double)(b-a)/CLOCKS_PER_SEC);
    // printf("contribuidor %d\n",g_tree_nnodes(t->ContriTree));
    //g_tree_foreach(t->ContriTree,(GTraverseFunc) imprime_contri,NULL);

    t=clean(t);
    return 0;
}
