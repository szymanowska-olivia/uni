import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Comparator;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;


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

class Czytelnik implements Obserwator {
    public void powiadomienie(Ksiazka k) {
        System.out.println("Nowa ksiazka " + k);
    }
}

class Krytyk implements Obserwator {
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

class Mama implements Obserwator {
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

class KsiazkaPanel extends JPanel {
    private JTextField tytulField;
    private JTextField autorField;

    public KsiazkaPanel(ArrayList<Pisarz> dostepniAutorzy) {
        setLayout(new GridLayout(2, 2));
        add(new JLabel("Tytuł:"));
        tytulField = new JTextField();
        add(tytulField);

        add(new JLabel("Autor:"));
        autorField = new JTextField(); 
        add(autorField);
    }

    public Ksiazka getKsiazka() {
        String tytul = tytulField.getText();
        String pseudonim = autorField.getText();
        Pisarz autor = new Pisarz(pseudonim, new ArrayList<>());
        return new Ksiazka(tytul, autor);
    }

    public void setKsiazka(Ksiazka ksiazka) {
        tytulField.setText(ksiazka.tytul);
        autorField.setText(ksiazka.autor != null ? ksiazka.autor.pseudonim : "");
    }
}

class PisarzPanel extends JPanel {
    private JTextField pseudonimField;

    public PisarzPanel() {
        setLayout(new GridLayout(1, 2));
        add(new JLabel("Pseudonim:"));
        pseudonimField = new JTextField();
        add(pseudonimField);
    }

    public Pisarz getPisarz() {
        return new Pisarz(pseudonimField.getText(), new ArrayList<>());
    }

    public void setPisarz(Pisarz p) {
        pseudonimField.setText(p.pseudonim);
    }
}

class WydawnictwoPanel extends JPanel {
    private JTextField nazwaField;
    private JTextField rokField;

    public WydawnictwoPanel() {
        setLayout(new GridLayout(2, 2));
        add(new JLabel("Nazwa (1 znak):"));
        nazwaField = new JTextField();
        add(nazwaField);

        add(new JLabel("Rok założenia:"));
        rokField = new JTextField();
        add(rokField);
    }

    public Wydawnictwo getWydawnictwo() {
        char nazwa = nazwaField.getText().charAt(0);
        int rok = Integer.parseInt(rokField.getText());
        Wydawnictwo w = new Wydawnictwo(nazwa);
        w.rok_zalozenia = rok;
        return w;
    }

    public void setWydawnictwo(Wydawnictwo w) {
        nazwaField.setText(String.valueOf(w.nazwa));
        rokField.setText(String.valueOf(w.rok_zalozenia));
    }
}


// Kontynuacja pliku, dodane klasy edytorów i modyfikacja metody main:

class KsiazkaEditor extends JFrame implements ActionListener {
    JComboBox<Ksiazka> combo;
    JTextField tytulField, autorField;
    ArrayList<Pisarz> pisarze;
    ArrayList<Ksiazka> ksiazki;

    public KsiazkaEditor(ArrayList<Pisarz> pisarze) {
        super("Edytor książek");
        this.pisarze = pisarze;
        this.ksiazki = new ArrayList<>();
        for (Pisarz p : pisarze) ksiazki.addAll(p.ksiazki);

        setLayout(new GridLayout(4, 2));

        combo = new JComboBox<>(ksiazki.toArray(new Ksiazka[0]));
        combo.addActionListener(e -> uzupelnijPola((Ksiazka) combo.getSelectedItem()));
        add(new JLabel("Wybierz książkę:"));
        add(combo);

        add(new JLabel("Tytuł:"));
        tytulField = new JTextField();
        add(tytulField);

        add(new JLabel("Autor:"));
        autorField = new JTextField();
        add(autorField);

        JButton zapisz = new JButton("Zapisz");
        zapisz.addActionListener(this);
        add(zapisz);

        if (!ksiazki.isEmpty()) {
            combo.setSelectedIndex(0);
            uzupelnijPola(ksiazki.get(0));
        }

        setDefaultCloseOperation(EXIT_ON_CLOSE);
        pack();
        setVisible(true);
    }

    void uzupelnijPola(Ksiazka k) {
        if (k != null) {
            tytulField.setText(k.tytul);
            autorField.setText(k.autor != null ? k.autor.pseudonim : "");
        }
    }

    public void actionPerformed(ActionEvent e) {
        Ksiazka k = (Ksiazka) combo.getSelectedItem();
        if (k != null) {
            k.tytul = tytulField.getText();
            k.autor = new Pisarz(autorField.getText(), new ArrayList<>());
            Literatura.zapisz(pisarze);
        }
    }
}

class PisarzEditor extends JFrame implements ActionListener {
    JComboBox<Pisarz> combo;
    JTextField pseudonimField;
    ArrayList<Pisarz> pisarze;

    public PisarzEditor(ArrayList<Pisarz> pisarze) {
        super("Edytor pisarzy");
        this.pisarze = pisarze;

        setLayout(new GridLayout(3, 2));

        combo = new JComboBox<>(pisarze.toArray(new Pisarz[0]));
        combo.addActionListener(e -> uzupelnij((Pisarz) combo.getSelectedItem()));
        add(new JLabel("Wybierz pisarza:"));
        add(combo);

        add(new JLabel("Pseudonim:"));
        pseudonimField = new JTextField();
        add(pseudonimField);

        JButton zapisz = new JButton("Zapisz");
        zapisz.addActionListener(this);
        add(zapisz);

        if (!pisarze.isEmpty()) {
            combo.setSelectedIndex(0);
            uzupelnij(pisarze.get(0));
        }

        setDefaultCloseOperation(EXIT_ON_CLOSE);
        pack();
        setVisible(true);
    }

    void uzupelnij(Pisarz p) {
        if (p != null) pseudonimField.setText(p.pseudonim);
    }

    public void actionPerformed(ActionEvent e) {
        Pisarz p = (Pisarz) combo.getSelectedItem();
        if (p != null) {
            p.pseudonim = pseudonimField.getText();
            Literatura.zapisz(pisarze);
        }
    }
}

class WydawnictwoEditor extends JFrame implements ActionListener {
    JComboBox<Wydawnictwo> combo;
    JTextField nazwaField, rokField;
    ArrayList<Wydawnictwo> wydawnictwa;

    public WydawnictwoEditor(ArrayList<Wydawnictwo> lista) {
        super("Edytor wydawnictw");
        this.wydawnictwa = lista;

        setLayout(new GridLayout(3, 2));

        combo = new JComboBox<>(wydawnictwa.toArray(new Wydawnictwo[0]));
        combo.addActionListener(e -> uzupelnij((Wydawnictwo) combo.getSelectedItem()));
        add(new JLabel("Wybierz wydawnictwo:"));
        add(combo);

        add(new JLabel("Nazwa (1 znak):"));
        nazwaField = new JTextField();
        add(nazwaField);

        add(new JLabel("Rok założenia:"));
        rokField = new JTextField();
        add(rokField);

        JButton zapisz = new JButton("Zapisz");
        zapisz.addActionListener(this);
        add(zapisz);

        if (!wydawnictwa.isEmpty()) {
            combo.setSelectedIndex(0);
            uzupelnij(wydawnictwa.get(0));
        }

        setDefaultCloseOperation(EXIT_ON_CLOSE);
        pack();
        setVisible(true);
    }

    void uzupelnij(Wydawnictwo w) {
        if (w != null) {
            nazwaField.setText(String.valueOf(w.nazwa));
            rokField.setText(String.valueOf(w.rok_zalozenia));
        }
    }

    public void actionPerformed(ActionEvent e) {
        Wydawnictwo w = (Wydawnictwo) combo.getSelectedItem();
        if (w != null) {
            w.nazwa = nazwaField.getText().charAt(0);
            w.rok_zalozenia = Integer.parseInt(rokField.getText());
        }
    }
}


class Aplikacja {
    static ArrayList<Pisarz> pisarze;

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("dodaj <Ksiazka|Pisarz|Wydawnictwo>");
            return;
        }

        pisarze = Literatura.odczytaj();
        if (pisarze == null) {
            pisarze = new ArrayList<>();
            Pisarz aho = new Pisarz("Aho", new ArrayList<>());
            Pisarz hop = new Pisarz("Hopcroft", new ArrayList<>());
            Pisarz ull = new Pisarz("Ullmann", new ArrayList<>());

            Wydawnictwo w = new Wydawnictwo('A');
            Krytyk krytyk = new Krytyk("Jan");
            Czytelnik c = new Czytelnik();

            aho.dodaj_obs(c);
            hop.dodaj_obs(krytyk);
            ull.dodaj_obs(w);

            ArrayList<Pisarz> autorzy = new ArrayList<>();
            autorzy.add(aho);
            autorzy.add(hop);
            autorzy.add(ull);

            aho.napiszKsiążkę("AiSD", autorzy);

            pisarze.addAll(autorzy);
            Literatura.zapisz(pisarze);
        }

        switch (args[0]) {
            case "Ksiazka" -> SwingUtilities.invokeLater(() -> new KsiazkaEditor(pisarze));
            case "Pisarz" -> SwingUtilities.invokeLater(() -> new PisarzEditor(pisarze));
            case "Wydawnictwo" -> {
                ArrayList<Wydawnictwo> wydawnictwa = new ArrayList<>();
                Wydawnictwo w1 = new Wydawnictwo('A');
                w1.rok_zalozenia = 1999;
                wydawnictwa.add(w1);
                Wydawnictwo w2 = new Wydawnictwo('B');
                w2.rok_zalozenia = 2005;
                wydawnictwa.add(w2);
                SwingUtilities.invokeLater(() -> new WydawnictwoEditor(wydawnictwa));
            }
        }
    }
}


public class Literatura {

    static final String PLIK = "pisarze.dat";
/* 
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
*/
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
            System.out.println("Brak pliku lub błąd odczytu – tworzymy nowe dane.");
            return null;
        }
    }
}

