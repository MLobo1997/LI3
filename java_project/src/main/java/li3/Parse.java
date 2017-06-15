package li3;

import javax.xml.stream.*;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;

public class Parse {

    private HashMap h ;
    private ContMap c;
    private int numeroTotalDeArtigos;
    private int tamanho;

    /**
     * Construtor do parse
     * @param N tamanho do HashMap
     */

    public Parse(int N){
        numeroTotalDeArtigos = 0;
        h = new HashMap(N);
        c = new ContMap();
        tamanho = N;
    }

    /**
     * Parse do xml
     * @param paths ficheiros
     * @throws XMLStreamException
     * @throws FileNotFoundException
     */


    public void  parse(ArrayList <String> paths) throws XMLStreamException, FileNotFoundException {
        Article artigo = null;
        Revision revisao = null;
        Contributors contribuidor = null;

        String PAGE= "page" ;
        String TITLE= "title" ;
        String REVISION= "revision" ;
        String ID= "id" ;
        String USERNAME = "username";
        String TIMESTAMP= "timestamp";
        String CONTENT= "text";
        String CONTRIBUTOR= "contributor";
        int contId = 0;
        boolean fId = false ;
        boolean fTitle = false;
        boolean fRevisionId = false;
        boolean fContribuitor = false;
        boolean fContriId= false;
        boolean ftimeStamp = false;
        boolean fContent = false ;
        boolean fUsername = false ;
        String text = null;
            XMLInputFactory factory = XMLInputFactory.newInstance();
            factory.setProperty(XMLInputFactory.IS_COALESCING, true);
            for(String a : paths){

                XMLStreamReader eventReader =
                        factory.createXMLStreamReader(new FileInputStream((a)));

                while(eventReader.hasNext()){
                    int event = eventReader.next();

                    switch(event){
                        case XMLStreamConstants.START_ELEMENT:
                            if(PAGE.equals(eventReader.getLocalName())){
                                numeroTotalDeArtigos++;
                                artigo = new Article();
                                contId = 1;
                            }

                            if(TITLE.equals(eventReader.getLocalName())) {
                                fTitle = true;
                            }
                            if(ID.equals(eventReader.getLocalName())){
                                if(contId == 1)
                                    fId = true;
                                if(contId == 2)
                                    fRevisionId= true;
                                if(contId == 3)
                                    fContriId= true;
                            }

                            if(REVISION.equals(eventReader.getLocalName())){
                                revisao=new Revision();
                                contId++;
                            }

                            if(TIMESTAMP.equals(eventReader.getLocalName())){
                                ftimeStamp = true;
                            }

                            if(CONTRIBUTOR.equals(eventReader.getLocalName())) {
                                contribuidor = new Contributors();
                                contribuidor.setContN(1);
                                contId++;
                            }

                            if(USERNAME.equals(eventReader.getLocalName())){
                                fUsername = true;
                            }

                            if(CONTENT.equals(eventReader.getLocalName())){
                                fContent= true;
                            }

                            break;
                        case XMLStreamConstants.CHARACTERS:
                            if(fId){
                                artigo.setId(Long.valueOf(eventReader.getText()));
                                fId= false ;
                            }
                            if(fRevisionId){
                                revisao.setId(Long.valueOf(eventReader.getText()));
                                fRevisionId= false;
                            }
                            if(fContriId){
                                contribuidor.setId(Long.valueOf(eventReader.getText()));
                                fContriId= false;
                            }
                            if(fTitle){
                                artigo.setTitle(eventReader.getText());
                                fTitle = false;
                            }
                            if(ftimeStamp){
                                revisao.setTimestamp((eventReader.getText()));
                                ftimeStamp = false;
                            }
                            if(fContent){
                                text  = eventReader.getText();
                                try {
                                    revisao.setTamanho((long) text.getBytes("UTF-8").length);
                                } catch (UnsupportedEncodingException e) {
                                    e.printStackTrace();
                                }
                                revisao.setWords((long) countWords(text));
                                fContent= false;
                            }
                            if(fUsername){
                                contribuidor.setNome((eventReader.getText()));
                                fUsername= false;
                            }
                            break;
                        case XMLStreamConstants.END_ELEMENT:
                            if(PAGE.equals(eventReader.getLocalName())){
                                int pos = artigo.hashCode() % getTamanho();
                                if(contribuidor.getId() != -1 && !h.getHash().get(pos).existeRevisao(artigo))
                                    c.addContribuidor(contribuidor);
                                contribuidor = null; // TODO : funcao que adiciona contribuidor
                                h.addArticle(artigo);
                                artigo = null;
                                contId = 0;
                            }

                            if(REVISION.equals(eventReader.getLocalName())){
                               artigo.addRevision(revisao);
                               revisao = null;
                            }
                       //     if(CONTRIBUTOR.equals(eventReader.getLocalName())){

                       //     }

                            break;
                    }
            }




            }
    }

    /**
     * Conta palavras de uma String
     * @param str  String
     * @return numero de palavras da str
     */

    public int countWords(String str){
        int t=str.length();

        int w= 0;
        for(int e = 0; e < t; ++e) {
            if ((str.charAt(e) != ' ' && str.charAt(e) != '\t' && str.charAt(e) != '\n') && (e+1==t || str.charAt(e + 1) == ' ' || str.charAt(e + 1) == '\t' || str.charAt(e + 1) == '\n'))
                ++w;
        }
        return w;
    }

    /**Getter do NumeroTotal de Artigos
     *
     * @return numeroTotaldeArtigos
     */
    public int getNumeroTotalDeArtigos() {
        return numeroTotalDeArtigos;
    }

    /**Getter do HashMap
     *
     * @return HashMap
     */

    public HashMap getHashMap(){
        return h;
    }

    /**Getter do Tamanho
     *
     * @return Tamanho
     */


    public int getTamanho() {
        return tamanho;
    }

    /**Getter do ContMap
     *
     * @return ContMap
     */

    public ContMap getC() {
        return c;
    }

}
