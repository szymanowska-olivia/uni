var n = 1;
// liczba ma prototyp?
console.log( typeof Object.getPrototypeOf( n ) );
// można jej dopisać pole/funkcję?
n.foo = 'foo';
console.log( n.foo );


// typy proste nie są obiektami ale mają powiązany prototyp 
// i można używać metod prototypowych, tworzony jest tymczasowy obiekt, 
// ale nie można trwale przypisywać własnych pól

let a = 42;

console.log(a.toString());  // "42"
console.log(a.valueOf());   // 42

let s = "Hello";
console.log(s.toUpperCase()); // "HELLO"

let b = true;
console.log(b.toString());   // "true"
console.log(b); 