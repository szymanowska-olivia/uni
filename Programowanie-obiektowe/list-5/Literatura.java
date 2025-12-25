import java.util.ArrayList;

class Ksiazka{
    String tytul;
    Pisarz autor;
    ArrayList<Pisarz> autorzy = new ArrayList<Pisarz>();

    Ksiazka(String tytul, Pisarz autor){
        this.tytul = tytul;
        this.autor = autor;
    }

    Ksiazka(String tytul, ArrayList<Pisarz> autorzy){
        this.tytul = tytul;
        this.autorzy = new ArrayList<>(autorzy);
    }

    public String toString() {
        if (autorzy.isEmpty()) return tytul + " " + autor;
        return tytul + " " + autorzy;
    }
}

interface Obserwator
{
    void powiadomienie(Ksiazka k);
} 

class Pisarz {
    String pseudonim;
    Obserwator w;

    ArrayList<Obserwator> obserwatorzy = new ArrayList<Obserwator>();


    Pisarz (String pseudonim, Obserwator w)
    {
        this.pseudonim = pseudonim;
        this.w = w;
    }

    Pisarz (String pseudonim, ArrayList<Obserwator> obserwatorzy)
    {
        this.pseudonim = pseudonim;
        this.obserwatorzy = obserwatorzy;
    }

    void dodaj_obs(Obserwator w)
    {
        this.obserwatorzy.add(w);
    }

    void usun_obs(Obserwator w)
    {
        this.obserwatorzy.remove(w);
    }

    ArrayList<Ksiazka> ksiazki = new ArrayList<Ksiazka>();
    
    void napisz(String tytul){
        Ksiazka ksiazka = new Ksiazka(tytul, this);
        this.ksiazki.add(ksiazka);

        for(int i=0;i<this.obserwatorzy.size();i++)
            this.obserwatorzy.get(i).powiadomienie(ksiazka);   
    }

    void napiszKsiążkę(String tytul, ArrayList<Pisarz> autorzy){
        if (autorzy == null || autorzy.isEmpty()) {
            System.out.println("Blad: pusta lista autorow");
            return;
        }

        Ksiazka ksiazka = new Ksiazka(tytul, autorzy);

        for(int i=0;i<autorzy.size();i++){
            autorzy.get(i).ksiazki.add(ksiazka);
            for(int j=0;j<autorzy.get(i).obserwatorzy.size();j++)
                autorzy.get(i).obserwatorzy.get(j).powiadomienie(ksiazka);  

        }
       
    }

    public String toString() {
        /*
        if (obserwatorzy.isEmpty()) return pseudonim + " " + w;
        return pseudonim + " " + obserwatorzy;
        */
        return pseudonim;
    }
}

class Wydawnictwo implements Obserwator {
    char nazwa;
    Wydawnictwo(char nazwa)
    {
        this.nazwa = nazwa;
    }

    void wydajKsiazke(Ksiazka ksiazka) {
        System.out.println("Wydaje ksiazkę " + ksiazka);
    }

    public void powiadomienie(Ksiazka ksiazka)
    {
        if (ksiazka.tytul.charAt(0) == this.nazwa)
            this.wydajKsiazke(ksiazka);
    }

    public String toString() {
        return nazwa + " ";
    }
}

class Czytelnik implements Obserwator
{
    public void powiadomienie(Ksiazka k){
        System.out.println("Nowa ksiazka " + k);
    }
}

class Krytyk implements Obserwator
{
    String imie;

    Krytyk (String imie)
    {
        this.imie = imie;
    }

    public void powiadomienie(Ksiazka k){
        System.out.println("Nowa ksiazka " + k + " czeka na twoja ocene " + this.imie);
    }

    public void feedback(Ksiazka k){

        if (!k.tytul.isEmpty() && this.imie.charAt(0)!=k.tytul.charAt(k.tytul.length()-1)){
            System.out.println("ocena " + imie + "," + k + " to okropna ksiazka ");
        }
        else System.out.println("ocena " + imie + "," + k + " to cudowna ksiazka ");
    }

}

class Mama implements Obserwator
{
    String imie, zupa;

    Mama (String imie, String ulubiona_zupa_dziecka)
    {
        this.imie = imie;
        this.zupa = ulubiona_zupa_dziecka;
    }

    public void powiadomienie(Ksiazka k){
        System.out.println("Nowa ksiazka " + k + "! Czy autor zasluzyl na zupe?");
    }

    public void ugotuj(Ksiazka k){
        if (k.autorzy.isEmpty()){
            Pisarz czlowiek = k.autor;
             if (czlowiek.pseudonim.length()==this.imie.length())
                 System.out.println(this.imie + " jest dumna ze swojego dziecka, " + this.zupa + " czeka na " + czlowiek );
        }else{ 
            for (int i=0;i<k.autorzy.size();i++){
                Pisarz czlowiek = k.autorzy.get(i);
                System.out.println(this.imie + " jest dumna ze swojego dziecka, " + this.zupa + " czeka na " + czlowiek );
             }
        }
    }

}

public class Literatura
{    public static void main(String[] args) {
        Wydawnictwo wydawnictwo = new Wydawnictwo('T');
        Krytyk krytyk = new Krytyk("Jan");
        Czytelnik czytelnik = new Czytelnik();
    
        Pisarz aho = new Pisarz("Aho", new ArrayList<>());
        Pisarz hopcroft = new Pisarz("Hopcroft", new ArrayList<>());
        Pisarz ullmann = new Pisarz("Ullmann", new ArrayList<>());
    
        aho.dodaj_obs(krytyk);
        hopcroft.dodaj_obs(czytelnik);
        ullmann.dodaj_obs(wydawnictwo);
    
        ArrayList<Pisarz> autorzy = new ArrayList<>();
        autorzy.add(aho);
        autorzy.add(hopcroft);
        autorzy.add(ullmann);
    
        aho.napiszKsiążkę("AiSD", autorzy);
    }
    

}