package li3;

public class Contributors {
    private Long id;
    private String nome;
    private Integer contN;

    /**
     * Construtor vazio
     */

    public Contributors() {
        this.id = (long) -1;
        this.nome = null;
        this.contN = null;
    }

    /**
     * Construtor parametrizado
     * @param id id
     * @param nome nome
     * @param contN numero de contribuicoes
     */
    public Contributors(Long id, String nome, Integer contN) {
        this.id = id;
        this.nome = nome;
        this.contN = contN;
    }

    /**
     * Construtor de copia
     * @param c contribuidor
     */

    public Contributors(Contributors c) {
        this.id=c.getId();
        this.nome=c.getNome();
        this.contN=c.getContN();
    }

    /**
     * Getter id
     * @return id
     */

    public Long getId() {
        return id;
    }

    /**
     * Setter id
     * @param id id
     */

    public void setId(Long id) {
        this.id = id;
    }

    /**
     * Getter nome
     * @return nome
     */

    public String getNome() {
        return nome;
    }

    /**
     * Setter nome
     * @param nome nome
     */

    public void setNome(String nome) {
        this.nome = nome;
    }

    /**
     * Getter contN
     * @return contN
     */

    public Integer getContN() {
        return contN;
    }

    /**
     * Setter contN
     * @param contN contN
     */

    public void setContN(Integer contN) {
        this.contN = contN;
    }

    /**Metodo da instancia de equal.
     *
     * @param o Objeto ao qual this sera comparado.
     * @return
     */

    public boolean equals(Object o) {
        if (this == o)
            return true;
        if(o==null || o.getClass()!=this.getClass())
            return false;

        Contributors contri = (Contributors) o;

        return ((contri.getId()).equals(this.id));
    }

    /**Conversao do objeto para String para finalidades de debugging.
     *
     * @return Representacao do objeto em String.
     */

    public String toString() {
        return "Contributors{" +
                "id=" + id +
                ", nome='" + nome + '\'' +
                ", contN=" + contN +
                '}';
    }

    /**
     * Clone contributors
     * @return  contributors clonado
     */


    public Contributors clone () {
        return new Contributors(this);
    }
}

