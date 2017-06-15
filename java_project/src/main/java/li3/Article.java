package li3;

import java.util.Iterator;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.stream.Collectors;


public class Article {
    private Long id;
    private String title;
    private LinkedBlockingQueue<Revision> revisions;

    public Article() {
        this.id = (long) -1;
        this.title = null;
        this.revisions = new LinkedBlockingQueue<>();
    }
    /**Construtor por copia.
     *
     * @param a Outro artigo.
     */
    public Article(Article a){
        this.id = a.getId();
        this.title = a.getTitle();
        this.revisions =    a
                            .getRevisions()
                            .parallelStream()
                            .map(Revision::clone)
                            .collect(Collectors.toCollection(LinkedBlockingQueue::new));
    }

    /**Construtor do artigo parametrizado.
     *
     * @param id ID do artigo em String.
     * @param title Titulo do artigo.
     */
    public Article(String id, String title) {
        this.id = Long.valueOf(id);
        this.title = title;
        this.revisions = new LinkedBlockingQueue<Revision>();
    }

    /**Getter do ID.
     *
     * @return ID.
     */
    public Long getId() {
        return id;
    }

    /**Getter do titulo.
     *
     * @return Titulo.
     */
    public String getTitle() {
        return title;
    }

    /**Getter da lista de revisoes.
     *
     * @return Lista de revisoes.
     */
    public LinkedBlockingQueue<Revision> getRevisions() {
        return revisions;
    }

    /**
     * Setter id
     * @param id
     */
    public void setId(Long id) {
        this.id = id;
    }

    /**
     * Setter tittle
     * @param title
     */
    public void setTitle(String title) {
        this.title = title;
    }

    /**
     * Setter revisions
     * @param revisions
     */
    public void setRevisions(LinkedBlockingQueue<Revision> revisions) {
        this.revisions = revisions;
    }

    /**
     * Retorna a revisao do id passado como argumento
     * @param id id da revisao
     * @return Revisao com aquele id ou null
     */

    public Revision getRevision(Long id){
        Iterator<Revision> it =this.revisions.iterator();
        Revision rev;

        while(it.hasNext()){
            rev=it.next();
            if(rev.getId().equals(id))
                return rev;
        }
        return null;
    }

    /**Metodo da instancia de equal.
     *
     * @param o Objeto ao qual this sera comparado.
     * @return
     */
    @Override
    public boolean equals(Object o) {
        if (this == o)
            return true;
        if (o == null || o.getClass() != this.getClass())
            return false;

        Article article = (Article) o;

        return (this.id.equals(article.getId()));
    }

    /**Obtencao de uma hash do artigo.
     *
     * @return Hash.
     */
    @Override
    public int hashCode(){
        return id.hashCode();
    }

    /**
     *Adiciona uma revisao a cabeca da lista.
     *
     * @param rev Revision.
     */
    public void addRevision(Revision rev) {
        revisions.offer(rev.clone());
    }

    /**
     * Verifica se a lista de revisoes contem uma revisao
     * @param revision revisao
     * @return true caso a revisao esteja na lista, false caso contrario
     */

    public boolean contains(Revision revision){
        return revisions.contains(revision);
    }

    /**Calcula o tamanho da revisao com um conteudo maior.
     *
     * @return Tamanho da maior revisao.
     */
    public Long LargestRevLength(){
        return  revisions
                .stream()
                .mapToLong(rev -> rev.getTamanho())
                .max()
                .getAsLong();

    }


    /**
     * Encontra a revisao que tem o maior numero de palavras
     *
     * @return o numero de palavras da maior revisao
     */
    public long largestRevWords() {
        return revisions
                .stream()
                .mapToLong(rev -> rev.getWords())
                .max()
                .getAsLong();
    }

    /**
     * Numero de revisoes existentes
     * @return numero de revisoes
     */
    public long numeroDeRevisoes() {
        return revisions.size();
    }

    /**
     * Clone do artigo
     * @return artigo clonado
     */

    public Article clone() {
        return new Article(this);
    }

    /**Conversao do objeto para String para finalidades de debugging.
     *
     * @return Representacao do objeto em String.
     */

    public String toString() {
        return "Article{" +
                "id=" + id +
                ", title='" + title + '\'' +
                "\n, revisions=" + revisions +
                "}\n";
    }
}
