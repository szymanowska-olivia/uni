function Foo() {
    function Qux() { console.log("Foo::Qux"); }
    this.Bar = function() { Qux(); }
}

