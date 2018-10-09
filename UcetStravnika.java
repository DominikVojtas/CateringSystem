/**
 * Trieda vytvori ucet stravnika
 * @param Stravnik paNazovUctu
 * @param double paPociatocnyVklad
 * @author Vojtas 
 * @version 1.0
 */

public class UcetStravnika {
    private double aZostatok;
    private Stravnik aNazovUctu;
    private JedloVTyzdni aObjednanie;
   
    /**
     *  @param Stravnik paNazovUctu
     *  @param double paPociatocnyVklad
     */
    public UcetStravnika(Stravnik paNazovUctu, double paPociatocnyVklad) {
        aNazovUctu = paNazovUctu;
        if ( paPociatocnyVklad < 0) {
            aZostatok = paPociatocnyVklad * (-1);
        } else {
            aZostatok = paPociatocnyVklad;
        }
        
        aObjednanie = new JedloVTyzdni();
    }
     
    //metoda vlozi peniaze na ucet
    public String  vklad(double paSuma) {
            
        if (paSuma > 0) {
            aZostatok += paSuma;  
            String vysledok = String.format ("[Bolo vlozene %10.2f € ]", paSuma );   
            return vysledok;
        } else {
            String vysledok = String.format ("[Operacia bola zamietnuta, zly vklad ]");   
            return vysledok;
        }
    }
    
    public double dajStavNaUcte() {
        return aZostatok;        
    }
    
    
    public String vyberJedloVPondelok(String paJedlo, double paCena, int paIndex) {
       
        String vysledok = "";
        if (aObjednanie.pridajJedloNaPondelok(paJedlo, paCena )) {
            aZostatok = aZostatok - aObjednanie.dajCenuVPondelok(paIndex);
            vysledok = "Jedlo bolo objednane." + "\n " + "Stalo vas to " + aObjednanie.dajCenuVPondelok(paIndex) + " €" + "\n" 
                + "Na ucte mate zostatok: " + aZostatok + " €";
        }
        return vysledok; 
    }
     
    //tieto metody sluzia na objednanie jedla v jednotlivych dnoch   
    public String vyberJedloVUtorok(String paJedlo, double paCena, int paIndex) {
       
        String vysledok = "";
        if (aObjednanie.pridajJedloNaUtorok(paJedlo, paCena )) {
            aZostatok = aZostatok - aObjednanie.dajCenuVUtorok(paIndex);
            vysledok = "Jedlo bolo objednane." + "\n " + "Stalo vas to " + aObjednanie.dajCenuVUtorok(paIndex) + " €" + "\n" 
                + "Na ucte mate zostatok: " + aZostatok + " €";
        }
        return vysledok; 
    }    
    
    public String vyberJedloVStredu(String paJedlo, double paCena, int paIndex) {
       
        String vysledok = "";
        if (aObjednanie.pridajJedloNaStredu(paJedlo, paCena )) {
            aZostatok = aZostatok - aObjednanie.dajCenuVStredu(paIndex);
            vysledok = "Jedlo bolo objednane." + "\n " + "Stalo vas to " + aObjednanie.dajCenuVStredu(paIndex) + " €" + "\n" 
                + "Na ucte mate zostatok: " + aZostatok + " €";
        }
        return vysledok; 
    }    
    
    public String vyberJedloVoStvrtok(String paJedlo, double paCena, int paIndex) {
       
        String vysledok = "";
        if (aObjednanie.pridajJedloNaStvrtok(paJedlo, paCena )) {
            aZostatok = aZostatok - aObjednanie.dajCenuVoStvrtok(paIndex);
            vysledok = "Jedlo bolo objednane." + "\n " + "Stalo vas to " + aObjednanie.dajCenuVoStvrtok(paIndex) + " €" + "\n" 
                + "Na ucte mate zostatok: " + aZostatok + " €";
        }
        return vysledok; 
    }    
    
    public String vyberJedloVPiatok(String paJedlo, double paCena, int paIndex) {
       
        String vysledok = "";
        if (aObjednanie.pridajJedloNaPiatok(paJedlo, paCena )) {
            aZostatok = aZostatok - aObjednanie.dajCenuVPiatok(paIndex);
            vysledok = "Jedlo bolo objednane." + "\n " + "Stalo vas to " + aObjednanie.dajCenuVPiatok(paIndex) + " €" + "\n" 
                + "Na ucte mate zostatok: " + aZostatok + " €";
        }
        return vysledok; 
    }    
        
        
}

