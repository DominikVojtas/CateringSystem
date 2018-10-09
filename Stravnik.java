/**
 * 
 * 
 * @author Vojtas
 * @version 1.0
 */

public class Stravnik {
    private static int aPrvyStravnik = 1;
    private OsobneUdaje aStravnik;
    private int aCisloStravnika;
    
    
    public Stravnik(OsobneUdaje paStravnik) {
        aStravnik = paStravnik;
        aCisloStravnika = aPrvyStravnik++;
    }
    
    //metoda na vypisanie cisla stravnika a jeho osobnych udajov
    public String toString() {
        return (aCisloStravnika + "." + aStravnik );
    }
}
