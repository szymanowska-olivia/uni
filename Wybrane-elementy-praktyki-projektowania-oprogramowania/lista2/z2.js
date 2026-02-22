//.
const food = {
    types: 'only pizza'
}
console.log(food.types) //nazwa jest znana z góry i nie ma żadnych dziwnych znaków(spacja/znakispeclajne/cyfry)
console.log(food['types']) //zawsze dziala

//.
food[310] = "example"  //js przekonwertował liczbe na string
console.log(food)

const osoba = {
  imie: "Ala",
  wiek: 40,
};

food[osoba] = "example2"
console.log(food) //js konwertuje wywolujac .toString() na obiekcie, a domyslnie zwykly obiekt  =  [object Object], czyli jak zrobimy 2 pola bedace obiekatmi to js ich nie rozróżni
console.log(food[osoba]) 
console.log(food['osoba']) //undefined

//na liczbe nie mamy wplywu, js zamieni ja na stringa
//mozemy ewentualnie sami zdefiniowac pole toString dla danego obiektu zeby byl rozny

//.

const tablica = [0, 1, 2]
console.log(tablica[0])
console.log(tablica['a']) //undefined
console.log(tablica[osoba]) //undefined

tablica['c'] = 32 //dopisuje sie do konca tablicy 
console.log(tablica['c']) 
console.log(tablica) //działa jak pole obiektu

tablica.length = 10
tablica['a'] = 39
console.log(tablica.length)
console.log(tablica)
tablica.length = 1 //zjada elementy ale tylko te "normalne" z indeksami, te bardziej jak pola zostawia
console.log(tablica.length)
console.log(tablica)
