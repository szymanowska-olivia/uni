typeof "hihi" // "string"
typeof 65 // "number"
typeof null // "object" - błąd js

// typeof - wypisuje w stringu jaki jest typ danej zmiennej
// ale nie sprawdza dokładnego typu i nie odroznia np tablicy od obiektu

const tab = [1, 2, 3];

console.log(tab instanceof Array); 
console.log(tab instanceof Object);
//oba true bo tablica tez obiekt

//zwraca true false - czy cos jest konkretnego typu
// sprawdza typ obiektu, dla primitywow nie zadziala

// typeof bardziej dla prymitywow / funkcji - np dla tablicy zwroci "object" zamiast dokladniej "array"
// instanceof dla obiektow - dla prymitywow zwroci false a dla obiektow sprawdzi ich dokladny typ - tablica instanceof Array = true
