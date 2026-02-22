"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
function PAA(pv) {
    console.log(pv);
}
function PAS(pv) {
    console.log(pv.name);
}
function isAnimal(p) {
    return 'species' in p;
}
function POA(pv) {
    if (isAnimal(pv))
        console.log(pv.name, pv.species);
    else
        console.log(pv.name, pv.surname);
}
function POS(pv) {
    if (typeof pv === 'string')
        console.log(pv);
    else
        console.log(pv.name, pv.surname);
}
function SAN(pv) {
    console.log(pv);
    console.log(typeof pv);
}
function SON(pv) {
    if (typeof pv === 'string')
        console.log(pv);
    else
        console.log(pv + 1);
}
PAA({ name: "Max", surname: "Smith", species: "Dog" });
//PAS({ name: "Alice", surname: "Brown" }); 
//PAS("Alice"); 
POA({ name: "John", surname: "Doe" });
POA({ name: "Rex", species: "Dog" });
POS({ name: "Alice", surname: "Brown" });
POS("Hafaff");
//SAN(42);           
//SAN("hello");      
SON("fafsaf");
SON(42);
//# sourceMappingURL=3.js.map