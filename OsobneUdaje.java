/**
 * 
 * 
 * @author Vojtas
 * @version 1.0
 */

public class OsobneUdaje {
    
    private String aMeno;
    private String aPriezvisko;
    private MojDatum aDatumNarodenia;
    
    public OsobneUdaje(String paMeno, String paPriezvisko, MojDatum paDatumNarodenia) {
        aMeno = paMeno;
        aPriezvisko = paPriezvisko;
        aDatumNarodenia = paDatumNarodenia;
    }
    
    //metoda vypise zakladne osobne udaje o osobe 
    public String toString() {
        return String.format ("[Osoba : %s %s narodena : %s ]", aMeno, aPriezvisko, aDatumNarodenia);
    }
}
