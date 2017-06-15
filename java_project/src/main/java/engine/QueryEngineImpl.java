package engine;


import li3.*;

import javax.xml.stream.XMLStreamException;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Comparator;

public class QueryEngineImpl implements Interface {
    private HashMap hashmap;
    private ContMap contMap;
    private long NTotal;

    /**
     * Inicializacao de todas as collections necessarias
     */

    public void init() {
        hashmap = new HashMap(113);
        NTotal = 0;
    }

    /**
     * Carrega os dados para as collections
     * @param nsnaps numero de ficheiros para importar
     * @param snaps_paths nome dos ficheiros para importar
     */

    public void load(int nsnaps, ArrayList<String> snaps_paths) {
        try {
            Parse p = new Parse(113);
            p.parse(snaps_paths);
            hashmap = p.getHashMap().clone();
            contMap = p.getC().clone();
            NTotal = p.getNumeroTotalDeArtigos();
        } catch (XMLStreamException | FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    /**
     *Numero de artigos encontrados nos backups analisados(artigos duplicados em backups sucessivos e novas revisoes sao tomadas em conta)
     *  * @return Numero total de artigos
     */

    public long all_articles() {
        return NTotal;
    }

    /**
     *Numero de artigos unicos encontrados nos backups analisados
     * @return Numero de artigos unicos
     */
    public long unique_articles() {

        long soma = 0;
        for(ArtMap aux : hashmap.getHash()){
            soma += aux.getMap().size();
        }
        return soma;
        /*
        return  hashmap
                .getHash()
                .stream()
                .flatMap(artree -> artree.getMap().values().stream())
                .count();
                */
    }

    /**
     *Numero de revisoes dos artigos encontrados nos backups analisados
     * @return Numero de revisoes
     */

    public long all_revisions() {
         long soma = 0;
        for(ArtMap aux : hashmap.getHash()){
            for(Article ar : aux.getMap().values()){
                soma += ar.numeroDeRevisoes();
            }
        }
        return soma;

        /*
        return  hashmap
                .getHash()
                .stream()
                .flatMap(artree -> artree.getMap().values().parallelStream())
                .mapToLong(Article::numeroDeRevisoes)
                .sum();
                */

    }

    /**
     * Id's dos 10 autores que contribuiram para um maior numero de versoes de um artigo
     * @return Array com  os identificadores(id's) dos 10 autores
     */

    public ArrayList<Long> top_10_contributors(){
        return  contMap
                .getContMap()
                .values()
                .stream()
                .sorted(Comparator.comparing(Contributors::getContN).reversed())
                .limit(10)
                .mapToLong(Contributors::getId)
                .collect(ArrayList<Long>::new, ArrayList<Long>::add, ArrayList<Long>::addAll);
    }

    /**
     * Dado o id do autor devolve o seu nome
     * @param contributor_id id do contribuidor
     * @return Nome do contribuidor
     */

    public String contributor_name(long contributor_id) {
        Contributors c;
        c=contMap.getContMap().get(contributor_id);

        if(c!=null)
                return c.getNome();
        else
            return null;
    }

    /**
     * 20 artigos com o maior tamanho de texto
     * @return Array com  os identificadores(id's) dos 20 artigos
     */

    public ArrayList<Long> top_20_largest_articles() {
        return  hashmap
                .getHash()
                .stream()
                .flatMap(artree -> artree.getMap().values().parallelStream())
                .sorted(Comparator.comparing(Article::LargestRevLength).reversed().thenComparing(Article::getId))
                .limit(20)
                .mapToLong(Article::getId)
                .collect(ArrayList<Long>::new, ArrayList<Long>::add, ArrayList<Long>::addAll);
    }

    /**
     * Dado o id do atigo devolve o seu titulo
     * @param article_id id do artigo
     * @return titulo do artigo
     */
    
    public String article_title(long article_id) {
        Article a = hashmap.getArticle(article_id);
        String r = null;

        if(a != null)
            r = a.getTitle();

        return r;
    }

    /**
     * n artigos que com o maior numero de palavras
     * @param n numero de artigos para retornar
     * @return  Array com  os identificadores(id's) dos n artigos com mais palavras
     */

    public ArrayList<Long> top_N_articles_with_more_words(int n) {
        return hashmap
                .getHash()
                .stream()
                .flatMap(artree -> artree.getMap().values().stream())
                .sorted(Comparator.comparing(Article::largestRevWords).reversed().thenComparing(Article::getId))
                .limit(n)
                .mapToLong(Article::getId)
                .collect(ArrayList<Long>::new, ArrayList<Long>::add, ArrayList<Long>::addAll);
    }

    /**
     * Query pedida no enunciado, devolve todos os titulos de artigos que tem um determinado prefixo.
     * @param prefix Prefixo a ser encontrado
     * @return  Array de strings com todos os titulos correspondentes e ordenados alfabeticamente.
     */

    public ArrayList<String> titles_with_prefix(String prefix) {
        return  hashmap
                .getHash()
                .stream()
                .flatMap(artree -> artree.getMap().values().stream())
                .filter(art -> art.getTitle().startsWith(prefix))
                .map(Article::getTitle)
                .sorted()
                .collect(ArrayList<String>::new, ArrayList<String>::add, ArrayList<String>::addAll);
    }

    /**
     * Timestamp de uma certa revisao de um artigo
     * @param article_id id do artigo
     * @param revision_id id da revisao
     * @return timestamp da revisao do artigo
     */


    public String article_timestamp(long article_id, long revision_id) {
        Article a = hashmap.getArticle(article_id);
        if (a != null) {
            Revision r = a.getRevision(revision_id);
            if (r != null)
                return a.getRevisions().stream()
                        .filter(rev -> rev.getId()== revision_id)
                        .findFirst()
                        .get()
                        .getTimestamp();
            else
                return null;
        }
        else
            return null;

    }
    /**
     * Liberta a memoria
     */

    public void clean() {
        contMap = null;
        hashmap = null;
        NTotal = 0;
    }
}
