/**
 * Trieda, ktorá vytvorí menu.
 * 
 * @author Vojtas
 * @version 1.0
 */

public class JedloVTyzdni {
    private String[] aPondelok;
    private String[] aUtorok;
    private String[] aStreda;
    private String[] aStvrtok;
    private String[] aPiatok;
    private double[] aCenaPondelok;
    private double[] aCenaUtorok;
    private double[] aCenaStreda;
    private double[] aCenaStvrtok;
    private double[] aCenaPiatok;
    private int aPocetJedalPondelok = 0;
    private int aPocetJedalUtorok = 0;
    private int aPocetJedalStreda = 0;
    private int aPocetJedalStvrtok = 0;
    private int aPocetJedalPiatok = 0;
    private int aPocetCienPondelok = 0;
    private int aPocetCienUtorok = 0;
    private int aPocetCienStreda = 0;
    private int aPocetCienStvrtok = 0;
    private int aPocetCienPiatok = 0;
    private static final int MAX_DRUHOV_JEDAL = 3;
    private static final int MAX_POCET_CIEN = 3;
    
    
    public JedloVTyzdni() {
        
        aPondelok = new String [MAX_DRUHOV_JEDAL];
        aUtorok = new String [MAX_DRUHOV_JEDAL];
        aStreda = new String [MAX_DRUHOV_JEDAL];
        aStvrtok = new String [MAX_DRUHOV_JEDAL];
        aPiatok = new String [MAX_DRUHOV_JEDAL];
        aCenaPondelok = new double [MAX_POCET_CIEN];
        aCenaUtorok = new double [MAX_POCET_CIEN];
        aCenaStreda = new double [MAX_POCET_CIEN];
        aCenaStvrtok = new double [MAX_POCET_CIEN];
        aCenaPiatok = new double [MAX_POCET_CIEN];
 
    }
    
    public boolean pridajJedloNaPondelok(String paJedlo, double paCena ) {
        if (aPocetJedalPondelok < aPondelok.length) {
            aPondelok[aPocetJedalPondelok] = paJedlo;
            aCenaPondelok[aPocetCienPondelok] = paCena;
            aPocetJedalPondelok++;
            aPocetCienPondelok++;
            return true;
           
        } else {
            
            return false;
        }      
          
    }
    
    public boolean pridajJedloNaUtorok(String paJedlo, double paCena) {
        if (aPocetJedalUtorok < aUtorok.length) {
            aUtorok[aPocetJedalUtorok] = paJedlo;
            aCenaUtorok[aPocetCienUtorok] = paCena;
            aPocetJedalUtorok++;
            aPocetCienUtorok++;
            return true;
           
        } else {
            
            return false;
        }      
          
    }
    
    //tieto metody sluzia na pridanie jedal do jednotlivych dni
    public boolean pridajJedloNaStredu(String paJedlo, double paCena) {
        if (aPocetJedalStreda < aStreda.length) {
            aStreda[aPocetJedalStreda] = paJedlo;
            aCenaStreda[aPocetCienStreda] = paCena;
            aPocetJedalStreda++;
            aPocetCienStreda++;
            return true;
           
        } else {
            
            return false;
        }      
          
    }
    
    public boolean pridajJedloNaStvrtok(String paJedlo, double paCena) {
        if (aPocetJedalStvrtok < aStvrtok.length) {
            aStvrtok[aPocetJedalStvrtok] = paJedlo;
            aCenaStvrtok[aPocetCienStvrtok] = paCena;
            aPocetJedalStvrtok++;
            aPocetCienStvrtok++;
            return true;
           
        } else {
            
            return false;
        }      
          
    }
    
    public boolean pridajJedloNaPiatok(String paJedlo, double paCena) {
        if (aPocetJedalPiatok < aPiatok.length) {
            aPiatok[aPocetJedalPiatok] = paJedlo;
            aCenaPiatok[aPocetCienPiatok] = paCena;
            aPocetJedalPiatok++;
            aPocetCienPiatok++;
            return true;
           
        } else {
            
            return false;
        }      
          
    }
    
    //tieto metody sluzia na ziskanie menu v jednotlivych dnoch
    public String[] dajMenuVPondelok() {
        return aPondelok;  
    }
    
    public String[] dajMenuVUtorok() {
        return aUtorok;    
    }
    
    public String[] dajMenuVStredu() {
        return aStreda;    
    }
    
    public String[] dajMenuVoStvrtok() {
        return aStvrtok;    
    }
    
    public String[] dajMenuVPiatok() {
        return aPiatok;    
    }
    
    //tieto metody sluzia na ziskanie cenz jednotlivych jedal v jednotlivych dnoch
    public double dajCenuVPondelok(int paIndex) {
        double vysledok = 0;
        if (paIndex == 0) {
            vysledok = aCenaPondelok[0];
                 
        } else if (paIndex == 1 ) {
            vysledok = aCenaPondelok[1];
        
        } else if (paIndex == 2) {
        
            vysledok = aCenaPondelok[2];
         
        } else {
            vysledok = -1;
        }
        return vysledok;              
    }
    
    public double dajCenuVUtorok(int paIndex) {        
        double vysledok = 0;
        if (paIndex == 0) {
            vysledok = aCenaUtorok[0];
         
        
        } else if (paIndex == 1 ) {
            vysledok = aCenaUtorok[1];
        

        } else if (paIndex == 2) {
        
            vysledok = aCenaUtorok[2];
         
        } else {
            vysledok = -1;
        }
        return vysledok;
   
    }
    
    public double dajCenuVStredu(int paIndex) {
        double vysledok = 0;
        if (paIndex == 0) {
            vysledok = aCenaStreda[0];
         
        
        } else if (paIndex == 1 ) {
            vysledok = aCenaStreda[1];
        

        } else if (paIndex == 2) {
        
            vysledok = aCenaStreda[2];
         
        } else {
            vysledok = -1;
        }
        return vysledok;
    }
    
    public double dajCenuVoStvrtok(int paIndex) {
        double vysledok = 0;
        if (paIndex == 0) {
            vysledok = aCenaStvrtok[0];
         
        
        } else if (paIndex == 1 ) {
            vysledok = aCenaStvrtok[1];
        

        } else if (paIndex == 2) {
        
            vysledok = aCenaStvrtok[2];
         
        } else {
            vysledok = -1;
        }
        return vysledok;
    }
    
    public double dajCenuVPiatok(int paIndex) {
        double vysledok = 0;
        if (paIndex == 0) {
            vysledok = aCenaPiatok[0];
         
        
        } else if (paIndex == 1 ) {
            vysledok = aCenaPiatok[1];
        

        } else if (paIndex == 2) {
        
            vysledok = aCenaPiatok[2];
         
        } else {
            vysledok = -1;
        }
        return vysledok;
    }
    
    // metoda sluziaca na kompletny vypis menu s cenami jednotlivych jedal
    public String toString() {
        String vysl = "Menu tyzdna\n\n";
        
        vysl += "Pondelok\n";
        for (int i = 0; i < aPocetJedalPondelok; i++) {
            vysl = vysl + (aPondelok[i] + " " +  aCenaPondelok[i] + " " + "€" + "\n");
        }
        vysl = vysl + "\nUtorok\n";
        for (int j = 0; j < aPocetJedalUtorok; j++) {
            vysl = vysl + (aUtorok[j] + " " + aCenaUtorok[j] + " " + "€"  + "\n");
        }
        vysl = vysl + "\nStreda\n";
        for (int k = 0; k < aPocetJedalStreda; k++) {
            vysl = vysl + (aStreda[k] + " " + aCenaStreda[k] + " " + "€" + "\n");
        }
        vysl = vysl + "\nStvrtok\n";
        for (int l = 0; l < aPocetJedalStvrtok; l++) {
            vysl = vysl + (aStvrtok[l] + " " + aCenaStvrtok[l] + " " + "€"  + "\n");
        }
        vysl = vysl + "\nPiatok\n";
        for (int m = 0; m < aPocetJedalPiatok; m++) {
            vysl = vysl + (aPiatok[m] + " " + aCenaPiatok[m] + " " + "€" + "\n");
        }   
        return vysl;
    }
    
   
    
   

}



