function getLastProto(o) {
    var p = o;
    do {
        o = p;
        p = Object.getPrototypeOf(o);
    } while (p);
    return o;
}

const obj1 = {};
const obj2 = { a: 1 };
function Foo() {}
const obj3 = new Foo();
class A {}
const obj4 = new A();

console.log( getLastProto(obj1) === getLastProto(obj2), getLastProto(obj2) === getLastProto(obj3), getLastProto(obj3) === getLastProto(obj4));