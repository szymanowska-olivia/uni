class Karta
  include Comparable
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
    puts "Wybierz numer karty (0-#{karty.size - 1})"
    a = gets.chomp

    indeks = a.to_i
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

class DwuosobowaGra
  attr_reader :gracze

  def initialize(gracz1, gracz2)
    @gracze = [gracz1, gracz2]
    przygotuj_gre
  end

  def rozpocznij
    until koniec_gry?
      wykonaj_ture(gracze[0])
      break if koniec_gry?
      wykonaj_ture(gracze[1])
      break if koniec_gry?
      rozstrzygnij_ture
      mozliwosc_przerwania
    end
    oglos_zwyciezce
  end

  # Metody do nadpisania w klasie potomnej:
  def przygotuj_gre; end
  def wykonaj_ture(gracz); end
  def rozstrzygnij_ture; end
  def mozliwosc_przerwania; end
  def koniec_gry?; end
  def oglos_zwyciezce; end
end


class Gra < DwuosobowaGra
  require_relative 'stopnrenew'
  include Stopper
  include Renewer

  attr_reader :stol

  def initialize(gracz1, gracz2)
    @stol = []
    super(gracz1, gracz2)
  end

  def przygotuj_gre
    Karta.utworz_talie
    Karta.tasuj
    rozdanie_kart
  end

  def wykonaj_ture(gracz)
    karta = gracz.wykonaj_ruch
    puts "#{gracz.nick} wyłożył: #{karta}"
    @stol << [gracz, karta]
  end

  def rozstrzygnij_ture
    gracz1, karta1 = @stol[0]
    gracz2, karta2 = @stol[1]
    @stol.clear

    if karta1 > karta2
      puts "#{gracz1.nick} wygrywa turę!"
    elsif karta1 < karta2
      puts "#{gracz2.nick} wygrywa turę!"
    else
      puts "Remis w tej turze!"
    end
  end

  def mozliwosc_przerwania
    puts "Czy chcesz kontynuować? Tak (Enter) / Zapisz grę i przerwij (P)"
    wybor = gets.chomp
    if wybor.strip.upcase == 'P'
      przerwij
      exit
    end
  end

  def koniec_gry?
    gracze.any? { |g| g.karty.empty? }
  end

  def oglos_zwyciezce
    puts "\n*~* Koniec gry *~*"
    gracze.each do |gracz|
      puts "#{gracz.nick} - zostało kart: #{gracz.karty.size}"
    end
  end

  private

  def rozdanie_kart
    while Karta.karty_pozostale > 0
      gracze.each do |gracz|
        gracz.dobierz_karte(Karta.rozdaj) if Karta.karty_pozostale > 0
      end
    end
  end
end


class MenedzerGry
  load 'stopnrenew.rb'
  extend Renewer

  def self.start
    puts "Wznowić grę? (W) czy zacząć nową? (Enter)"
    odpowiedz = gets.chomp.strip.downcase
  
    if odpowiedz == 'w'
      wznow_gry
    else
      rozpocznij_nowa_gre
    end
  end

  private

  def self.wznow_gry
    gra = wznow  
    gra.rozpocznij 
  end

  def self.rozpocznij_nowa_gre
    puts "Gracz 1 - podaj swój nick lub użyj domyślnego (Enter):"
    nick1 = gets.chomp
    gracz1 = GraczCzlowiek.new(nick1.empty? ? "Gracz1" : nick1)

    puts "Gracz 2 - podaj swój nick lub użyj domyślnego (Enter):"
    nick2 = gets.chomp
    gracz2 = GraczCzlowiek.new(nick2.empty? ? "Gracz2" : nick2)

    gra = Gra.new(gracz1, gracz2)
    gra.rozpocznij 
  end
end

MenedzerGry.start
