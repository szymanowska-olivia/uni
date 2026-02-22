type Person = {
name: string,
surname: string
}
type Animal = {
name: string,
species: string
}

type PersonAndAnimal = Person & Animal;
type PersonAndString = Person & string;//never
type PersonOrAnimal = Person | Animal;
type PersonOrString = Person | string;
type StringAndNumber = string & number; //never
type StringOrNumber = string | number;

function PAA( pv : PersonAndAnimal){
    console.log( pv );
}

function PAS( pv: PersonAndString ){
    console.log( pv.name);
}

function isAnimal( p: PersonOrAnimal ): p is Animal {
    return 'species' in p;
}

function POA( pv : PersonOrAnimal){
    if (isAnimal(pv)) console.log( pv.name, pv.species );
    else console.log( pv.name, pv.surname );

}

function POS( pv : PersonOrString){
    if (typeof pv === 'string') console.log( pv);
    else console.log( pv.name, pv.surname );
}

function SAN( pv : StringAndNumber){
    console.log( pv);
    console.log( typeof pv);
}

function SON( pv : StringOrNumber){
    if (typeof pv === 'string') console.log( pv);
    else console.log( pv + 1);
}

PAA({ name: "Max", surname: "Smith", species: "Dog"});

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