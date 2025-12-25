module Stopper
  def przerwij(plik = 'save.dat')
    puts "Przerwano rozgrywkę"
    File.open(plik, "wb") do |f|
      Marshal.dump(self, f)  # Zapisujemy całą instancję gry
    end
    puts "Zapisano w #{plik}"
  end
end

module Renewer
  def wznow(plik = 'save.dat')
    puts "Wznawianie rozgrywki..."
    gra = File.open(plik, "rb") do |f|
      Marshal.load(f)  # Odczytujemy całą instancję gry
    end
    puts "Odczytano z pliku #{plik}"

    gra  # Zwracamy odczytany obiekt, który powinien być instancją klasy Gra
  end
end
