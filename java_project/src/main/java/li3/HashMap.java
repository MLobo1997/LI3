package li3;

import java.util.ArrayList;
import java.util.concurrent.CopyOnWriteArrayList;

public class HashMap {
    private CopyOnWriteArrayList<ArtMap> hash;
    private Integer N;

    /**Construtor da HashTree
     *
     * @param N Numero de elementos que a hashtable devera ter.
     */
    public HashMap(Integer N){
        this.N = N;
        hash = new CopyOnWriteArrayList<>();

        for(int i = 0 ; i < N ; i++)
            hash.add(i, new ArtMap());
    }

    /**Construtor por copia.
     *
     * @param a Outra HashTree.
     */
    public HashMap(HashMap a){
        N = a.getN();
        this.hash = new CopyOnWriteArrayList<>();
        CopyOnWriteArrayList<ArtMap> aux = a.getHash();
        for(int i=0;i<N;i++)
            this.hash.add(i,aux.get(i));

    }

    /**Getter da hashtable
     *
     * @return Hashtable.
     */
    public CopyOnWriteArrayList<ArtMap> getHash(){
        return hash;
    }

    /**Getter de N
     *
     * @return N.
     */
    public Integer getN() {
        return N;
    }

    /**Adiciona um artigo.
     *
     * @param a Artigo.
     */
    public void addArticle(Article a){
        int pos = a.hashCode() % N;

        hash.get(pos).addArticle(a);
    }

    /**Procura um artigo.
     *
     * @param id ID do artigo.
     * @return Artigo ou null.
     */
    public Article getArticle(Long id){
        int pos = id.hashCode() % N;

        return hash.get(pos).getArticle(id);
    }

    public HashMap clone(){
        return new HashMap(this);
    }
}
