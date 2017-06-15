package li3;

public class Revision {
    private Long id;
    private String timestamp;
    private Long words;
    private Long tamanho;

    /**
     * Construtor vazio
     */

    public Revision() {
        this.id = 0L;
        this.timestamp = null;
        this.words=0L;
        this.tamanho=0L;
    }
    /**Construtor por copia.
     *
     * @param r Outra revisao.
     */
    public Revision(Revision r) {
        this.id = r.getId();
        this.timestamp = r.getTimestamp();
        this.words=r.getWords();
        this.tamanho=r.getTamanho();

    }

    /**Construtor de revisao parametrizado.
     * @param id ID da revisao, em String.
     * @param timestamp Timestamp da revisao.
     * @param  words numero de palavras do texto da revisao.
     * @param  tamanho tamanho do texto da revisao.
     */
    public Revision(String id, String timestamp,Long words, Long tamanho) {
        this.id = Long.valueOf(id);
        this.timestamp = timestamp;
        this.words=words;
        this.tamanho=tamanho;
    }

    /**Getter do ID.
     *
     * @return O ID.
     */
    public Long getId() {
        return id;
    }

    /**Getter do timestamp.
     *
     * @return A timestamp.
     */
    public String getTimestamp() {
        return timestamp;
    }

    /**Getter do numero de palavras do texto.
     *
     * @return numero de palavras.
     */
    public Long getWords() {
        return words;
    }

    /**Getter do tamanho do texto.
     *
     * @return tamanho do texto.
     */
    public Long getTamanho() {
        return tamanho;
    }

    /**
     * Setter id
     * @param id
     */
    public void setId(Long id) {
        this.id = id;
    }

    /**
     * Setter Timestamp
     * @param timestamp
     */
    public void setTimestamp(String timestamp) {
        this.timestamp = timestamp;
    }

    /**
     * Setter Words
     * @param w numero de palavras
     */
    public void setWords(Long w) {
        this.words=w;
    }

    /**
     * Setter Tamanho
     * @param t tamanho do texto
     */
    public void setTamanho(Long t) {
        this.tamanho=t;
    }

    /**Metodo da instancia de equal.
     *
     * @param o Objeto ao qual this serq comparado.
     * @return
     */

    public boolean equals(Object o) {
        if (this == o)
            return true;
        if (o == null || o.getClass() != this.getClass())
            return false;

        Revision revision = (Revision) o;

        return getId().equals(revision.getId());
    }

    /**Obtencao de uma hash da revisao.
     *
     * @return Hash.
     */

    public int hashCode(){
        return id.hashCode();
    }

    /**Conversao do objeto para String para finalidades de debugging.
     *
     * @return Representacao do objeto em String.
     */
    public String toString() {
        return "Revision{" +
                "id=" + id +
                ", timestamp='" + timestamp + '\'' +
                ", tamanho='" + tamanho + '\'' +
                ", words='" + words + '\'' +
                "}\n";
    }

    /**Natural comparison method.
     *
     * @param r Revision comparing to;
     * @return Int identifying the comparation result.
     */
    public int compareTo(Revision r){
        return id.compareTo(r.getId());
    }

    /**Clona o objecto.
     * @return Um nova revisao igual a esta.
     */
    public Revision clone(){
        return new Revision(this);
    }
}
