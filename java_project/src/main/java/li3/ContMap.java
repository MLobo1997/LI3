package li3;

import com.sun.org.apache.xpath.internal.patterns.ContextMatchStepPattern;

import java.util.HashMap;
import java.util.concurrent.CopyOnWriteArrayList;


public class ContMap {
   private HashMap <Long,Contributors> contMap;

    /**
     * Construtor vazio
     */

    public ContMap() {contMap = new HashMap<>();
    }

    /**
     * Construtor copia
     * @param ini ContMap que vai ser copiado
     */

    public ContMap(ContMap ini) {
         this.contMap = new HashMap<>();
         HashMap<Long,Contributors> aux = ini.getContMap();
        for(Contributors a : aux.values()){

               contMap.put(a.getId(),a.clone());
        }
    }

    /**
     * Clone
     * @return copia do objecto
     */

    public ContMap clone() {
        return new ContMap(this);
    }

    /**Conversao do objeto para String para finalidades de debugging.
     *
     * @return Representacao do objeto em String.
     */
    public String toString() {
        return super.toString();
    }

    /**
     * getter do contMap
     * @return contMap
     */

    public HashMap<Long, Contributors> getContMap() {
        return this.contMap;
    }

    /**
     * Setter do contMap
     * @param contM contMap
     */
    public void setContMap(HashMap<Long, Contributors> contM) {
        contMap = contM;
    }

    /**
     * Adicionar um contribuidor ao contMap
     * @param c contribuidor
     */
    public void addContribuidor(Contributors c){
        if(!contMap.containsKey(c.getId())){
            contMap.put(c.getId(),c.clone());
        }
        else{
           Contributors aux =  contMap.get(c.getId());
            aux.setContN((aux.getContN()+1));
            contMap.put(aux.getId(),aux.clone());
        }

    }
}
