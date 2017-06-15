package li3;

import java.util.concurrent.ConcurrentSkipListMap;
import java.util.concurrent.LinkedBlockingQueue;

public class ArtMap{
    private ConcurrentSkipListMap<Long,Article> map;

    /**Construtor de ArtTree's.
     *
     */
    public ArtMap() {
        this.map = new ConcurrentSkipListMap<>();
    }

    /**Construtor por copia.
     *
     * @param a Outra ArtTree.
     */
    public ArtMap(ArtMap a){
        this.map = new ConcurrentSkipListMap<>();
        ConcurrentSkipListMap<Long,Article> aux = a.getMap();
        for(Article ar : aux.values()){

            this.map.put(ar.getId(),ar.clone());
        }
    }
    /**Getter do Map.
     *
     * @return Map.
     */
    public ConcurrentSkipListMap<Long, Article> getMap() {
        return map;
    }

    /**
     * Verifica se exite uma revisao de um determinado artigo
     * @param a artigo onde podera existir a revisao
     * @return true se exitir false caso contrario
     */

    public boolean existeRevisao(Article a){

        Long id = a.getId();
        LinkedBlockingQueue<Revision> revQueue;
        Revision rev = null;

        if(map.containsKey(id)){
            Article a2 = map.get(id);

            revQueue = a2.getRevisions();
            rev= a.getRevisions().peek();
            return revQueue.contains(rev);

        }
        else return false;
    }


    /**Adiciona um artigo a arvore, no caso de este ja existir adiciona as revisoes que nao se encontram no mesmo e no caso de o titulo de o artigo ter sido atualizado, verifica qual o que tem uma timestamp mais recente e utiliza o titulo do mesmo.
     * @param a Artigo a ser adicionado.
     */
    public void addArticle(Article a){
        Long id = a.getId();
        LinkedBlockingQueue<Revision> revTo, revFrom;

        if(map.containsKey(id)){
            Article a2 = map.get(id);

            revTo = a2.getRevisions();
            revFrom = a.getRevisions();

            revFrom
            .parallelStream()
            .filter(r -> !revTo.contains(r))
            .forEach(r -> revTo.offer(r.clone()));

           /*
           for(Revision r : revFrom)
              if(! revTo.contains(r))
                 revTo.offer(r.clone());
                 */
        }
        else
            map.put(id, a.clone());
    }

    /**Procura um artigo.
     *
     * @param id ID do artigo
     * @return Artigo (ou null).
     */
    public Article getArticle(Long id){
        return map.get(id);
    }

    /**Conversao do objeto para String para finalidades de debugging.
     *
     * @return Representacao do objeto em String.
     */
    @Override
    public String toString() {
        return "ArtMap{" +
                "map=\n" + map +
                '\n';
    }

    /**Clona a arvore e todos os seus conteudos.
     *
     * @return Nova ArtTree.
     */
    public ArtMap clone(){
        return new ArtMap(this);
    }
}
