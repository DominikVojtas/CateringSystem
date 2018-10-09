/**
 * 
 * 
 * @author Vojtas
 * @version 1.0
 */

public class MojDatum {
    private int aDen;
    private int aMesiac;
    private int aRok;
    
    public MojDatum(int paDen, int paMesiac, int paRok) {
        aDen = paDen;
        aMesiac = paMesiac;
        aRok = paRok;
    }
    
    public MojDatum() {
        this(1, 1, 1970);
    }
    
    public String toString() {
        return  (aDen + ". " + aMesiac + ". " + aRok);
    }
    
    public boolean jePriestupny() {
        boolean jePriestupny = true;
        if ((aRok % 4 == 0 ) &  (aRok % 100 != 0)  | (aRok % 100 == 0)) {
            jePriestupny = true;
        } else {
            jePriestupny = false;
        }
        return jePriestupny;    
    }
    
    public int dajPocetDniVMesiaci() {
        int pocetDniVMesiaci = 0;
        switch (aMesiac) {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                pocetDniVMesiaci  = 31;
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                pocetDniVMesiaci  = 30;
                break;
            case 2:
                if (this.jePriestupny()) {
                    pocetDniVMesiaci  = 29;
                } else { 
                    pocetDniVMesiaci  = 28;
                }
                break;
                    
            default: 
                break;
                    
            
            
        }
        return (pocetDniVMesiaci);
    }
    
    public MojDatum vytvorZajtra () {
        int den = aDen;
        int mesiac = aMesiac;
        int rok = aRok;
        int pocetDniVMesiaci = this.dajPocetDniVMesiaci();
        MojDatum vysledok = null;
        
        if (den < pocetDniVMesiaci) {
            den++;
        } else {
            den = 1;
            if (mesiac == 12) {
                mesiac = 1;
                rok++;
            } else {
                mesiac++;
            }
               
        }
        vysledok = new MojDatum( den,  mesiac,  rok);
        return vysledok; 
    }



}

