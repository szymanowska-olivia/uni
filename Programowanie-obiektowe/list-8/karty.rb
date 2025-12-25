class Karta include Comparable
    attr_reader :figura, :kolor
  
    @@dostepne_karty = []
    @@wszystkie_karty = {} 
    
  
    FIGURY = [2, 3, 4, 5, 6, 7, 8, 9, 10, 'J', 'Q', 'K', 'A']
    KOLORY = { kier: '♡', karo: '♢', pik: '♠', trefl: '♣' }
  
    def initialize(figura, kolor)
      @figura = figura
      @kolor = kolor
    end
  
    private_class_method :new  

    def self.znajdz_lub_utworz(figura, kolor)
      klucz = [figura, kolor]
      @@wszystkie_karty[klucz] ||= new(figura, kolor)
    end
  
    def self.utworz_talie
      @@dostepne_karty.clear
      FIGURY.each do |figura|
        KOLORY.keys.each do |kolor|
          karta = znajdz_lub_utworz(figura, kolor)
          @@dostepne_karty << karta
        end
      end
    end
  
    def self.tasuj
      @@dostepne_karty.shuffle!
    end
  
    def self.rozdaj
      @@dostepne_karty.pop
    end
  
    def self.karty_pozostale
      @@dostepne_karty.size
    end
  
    def to_s
      "#{figura}#{KOLORY[kolor]}"
    end
  
    def wartosc
      FIGURY.index(figura)
    end
  
    def <=>(inna_karta)
      wartosc <=> inna_karta.wartosc
    end
  end
  
  class GraczCzlowiek
    attr_reader :nick, :karty
  
    def initialize(nick)
      @nick = nick
      @karty = []
    end
  
    def dobierz_karte(karta)
      @karty << karta
    end
  
    def wykonaj_ruch
      puts "#{nick}, Twoje karty: #{karty.map(&:to_s).join(', ')}"
      puts "Wybierz numer karty, żeby ją wyłożyć (0 - #{karty.size - 1}):"
      indeks = gets.to_i
      karty.delete_at(indeks)
    end
  end
  
  class GraczAI
    attr_reader :nick, :karty
  
    def initialize(nick)
      @nick = nick
      @karty = []
    end
  
    def dobierz_karte(karta)
      @karty << karta
    end
  
    def wykonaj_ruch
      karty.delete_at(rand(karty.size))
    end
  end
  
  class Gra
    def initialize(gracz1, gracz2)
      @gracze = [gracz1, gracz2]
      @stol = []
    end
  
    def rozpocznij
      Karta.utworz_talie
      Karta.tasuj
  
      rozdanie_kart
  
      until koniec_gry?
        @stol.clear
        puts "\n*~* Nowa tura *~*"
        @gracze.each do |gracz|
          karta = gracz.wykonaj_ruch
          puts "#{gracz.nick} wyłożył: #{karta}"
          @stol << [gracz, karta]
        end
        rozstrzygnij_ture
      end
  
      oglos_zwyciezce
    end
  
    def rozdanie_kart
      while Karta.karty_pozostale > 0
        @gracze.each do |gracz|
          gracz.dobierz_karte(Karta.rozdaj) if Karta.karty_pozostale > 0
        end
      end
    end
  
    def rozstrzygnij_ture
      gracz1, karta1 = @stol[0]
      gracz2, karta2 = @stol[1]
  
      if karta1 > karta2
        puts "#{gracz1.nick} wygrywa turę!"
      elsif karta1 < karta2
        puts "#{gracz2.nick} wygrywa turę!"
      else
        puts "Remis w tej turze!"
      end
    end
  
    def koniec_gry?
      @gracze.any? { |g| g.karty.empty? }
    end
  
    def oglos_zwyciezce
      puts "\n*~* Koniec gry *~*"
      @gracze.each do |gracz|
        puts "#{gracz.nick} - zostało kart: #{gracz.karty.size}"
      end
    end
  end
  
  
  class MenedzerGry
    def self.rozpocznij_nowa_gre
      puts "Podaj swój nick lub użyj domyślnego (Enter):"
      nick = gets.chomp
      czlowiek = GraczCzlowiek.new(nick.empty? ? "człowiek" : nick)
      komputer = GraczAI.new("Komputer")
      gra = Gra.new(czlowiek, komputer)
      gra.rozpocznij 
    end
  end

  MenedzerGry.rozpocznij_nowa_gre