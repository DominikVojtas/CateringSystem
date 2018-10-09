/**
 * Trieda, ktorá vytvorí jedáleň.
 * 
 * @author Vojtas
 * @version 1.0
 */

public class Jedalen {
    //konstatnta
    private static final int MAX_POCET_STRAVNIKOV = 200; 
    private int aPocetStravnikov;
    private Stravnik[] aPoleStravnikov;
    private String aNazovJedalne;
    private OsobneUdaje aVeducaJedalne;
    
    //konstruktor s dvoma parametrami
    public Jedalen(String paNazov, OsobneUdaje paVeducaJedalne) {
        aNazovJedalne = paNazov;
        aVeducaJedalne = paVeducaJedalne;
        aPocetStravnikov = 0;
        aPoleStravnikov = new Stravnik[MAX_POCET_STRAVNIKOV];
    }
    
    //metoda na pridanie stravnika
    public boolean pridajStravnika(Stravnik paPridany) {
        if (aPocetStravnikov > aPoleStravnikov.length) {
            return false;
        }  else {
            aPoleStravnikov[aPocetStravnikov] = paPridany;
            aPocetStravnikov++;
            return true;
        }
    
    }
    
    //metoda, ktora zmeni veducu jedalne
    public void zmenVeducuJedalne(OsobneUdaje paNovaVeduca) {
        aVeducaJedalne = paNovaVeduca;       
    
    }
}
