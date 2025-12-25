import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Comparator;

class Ksiazka implements Serializable {
    String tytul;
    Pisarz autor;
    ArrayList<Pisarz> autorzy = new ArrayList<>();

    Ksiazka(String tytul, Pisarz autor) {
        this.tytul = tytul;
        this.autor = autor;
    }

    Ksiazka(String tytul, ArrayList<Pisarz> autorzy) {
        this.tytul = tytul;
        this.autorzy = new ArrayList<>(autorzy);
    }

    public String toString() {
        if (autorzy.isEmpty()) return tytul + " " + autor;
        return tytul + " " + autorzy;
    }
}

interface Obserwator {
    void powiadomienie(Ksiazka k);
}

class Pisarz implements Serializable{
    String pseudonim;
    ArrayList<Obserwator> obserwatorzy = new ArrayList<>();
    ArrayList<Ksiazka> ksiazki = new ArrayList<>();

    Pisarz(String pseudonim, ArrayList<Obserwator> obserwatorzy) {
        this.pseudonim = pseudonim;
        this.obserwatorzy = obserwatorzy;
    }

    void dodaj_obs(Obserwator w) {
        this.obserwatorzy.add(w);
    }

    void usun_obs(Obserwator w) {
        this.obserwatorzy.remove(w);
    }

    void napisz(String tytul) {
        Ksiazka ksiazka = new Ksiazka(tytul, this);
        this.ksiazki.add(ksiazka);

        this.obserwatorzy.sort(new CompareObs());
        for (Obserwator o : this.obserwatorzy) {
            o.powiadomienie(ksiazka);
        }
    }

    void napiszKsiążkę(String tytul, ArrayList<Pisarz> autorzy) {
        if (autorzy == null || autorzy.isEmpty()) {
            System.out.println("Blad: pusta lista autorow");
            return;
        }

        Ksiazka ksiazka = new Ksiazka(tytul, autorzy);

        for (Pisarz autor : autorzy) {
            autor.ksiazki.add(ksiazka);
            autor.obserwatorzy.sort(new CompareObs());
            for (Obserwator o : autor.obserwatorzy) {
                o.powiadomienie(ksiazka);
            }
        }
    }

    public String toString() {
        return pseudonim;
    }
}

class Wydawnictwo implements Obserwator, Serializable {
    char nazwa;
    int rok_zalozenia;

    Wydawnictwo(char nazwa) {
        this.nazwa = nazwa;
    }

    void wydajKsiazke(Ksiazka ksiazka) {
        System.out.println("Wydaje ksiazkę " + ksiazka);
    }

    public void powiadomienie(Ksiazka ksiazka) {
        if (ksiazka.tytul.charAt(0) == this.nazwa)
            this.wydajKsiazke(ksiazka);
    }

    public String toString() {
        return nazwa + " ";
    }
}

class Czytelnik implements Obserwator, Serializable {
    public void powiadomienie(Ksiazka k) {
        System.out.println("Nowa ksiazka " + k);
    }
}

class Krytyk implements Obserwator, Serializable {
    String imie;

    Krytyk(String imie) {
        this.imie = imie;
    }

    public void powiadomienie(Ksiazka k) {
        System.out.println("Nowa ksiazka " + k + " czeka na twoja ocene " + this.imie);
    }

    public void feedback(Ksiazka k) {
        if (!k.tytul.isEmpty() && this.imie.charAt(0) != k.tytul.charAt(k.tytul.length() - 1)) {
            System.out.println("ocena " + imie + "," + k + " to okropna ksiazka ");
        } else {
            System.out.println("ocena " + imie + "," + k + " to cudowna ksiazka ");
        }
    }
}

class Mama implements Obserwator, Serializable {
    String imie, zupa;

    Mama(String imie, String ulubiona_zupa_dziecka) {
        this.imie = imie;
        this.zupa = ulubiona_zupa_dziecka;
    }

    public void powiadomienie(Ksiazka k) {
        System.out.println("Nowa ksiazka " + k + "! Czy autor zasluzyl na zupe?");
    }

    public void ugotuj(Ksiazka k) {
        if (k.autorzy.isEmpty()) {
            Pisarz czlowiek = k.autor;
            if (czlowiek.pseudonim.length() == this.imie.length())
                System.out.println(this.imie + " jest dumna ze swojego dziecka, " + this.zupa + " czeka na " + czlowiek);
        } else {
            for (Pisarz czlowiek : k.autorzy) {
                System.out.println(this.imie + " jest dumna ze swojego dziecka, " + this.zupa + " czeka na " + czlowiek);
            }
        }
    }
}

class CompareObs implements Comparator<Obserwator> {
    public int compare(Obserwator o1, Obserwator o2) {
        return Priorytet(o1) - Priorytet(o2);
    }

    private int Priorytet(Obserwator o) {
        if (o instanceof Krytyk) return 1;
        if (o instanceof Wydawnictwo) return 2;
        if (o instanceof Czytelnik) return 3;
        return 4;
    }
}

public class Literatura {

    static final String PLIK = "pisarze.dat";

    public static void main(String[] args) {
        ArrayList<Pisarz> pisarze = odczytaj();

        if (pisarze == null){
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

            zapisz(autorzy);

        } else {
            for (Pisarz p : pisarze) {
                System.out.println("Pisarz: " + p);
                for (Ksiazka k : p.ksiazki) {
                    System.out.println("  Ksiazka: " + k);
                }
            }
        }
    }

    static void zapisz(ArrayList<Pisarz> pisarze) {
        try (ObjectOutputStream out = new ObjectOutputStream(new FileOutputStream(PLIK))) {
            out.writeObject(pisarze);
            System.out.println("Zapisano dane do pliku.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    static ArrayList<Pisarz> odczytaj() {
        try (ObjectInputStream in = new ObjectInputStream(new FileInputStream(PLIK))) {
            ArrayList<Pisarz> pisarze = (ArrayList<Pisarz>) in.readObject();
            System.out.println("Odczytano dane z pliku.");
            return pisarze;
        } catch (IOException | ClassNotFoundException e) {
            System.out.println("tworzymy nowe dane.");
            return null;
        }
    }
}

