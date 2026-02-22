const food = {
    types: 'pizza',

    eat() {
        console.log(`Eating ${this.type}..`)
    },

    get type(){
        return "tu jest" + this.type 
    },

    set type(x){
        this.type = this.type + "and" + x 
    }
}

food.cnt = 2

food.whocookedit = function () {
    console.log(`me! I cookedc${this.types}`)
}

Object.defineProperty(food, 'fullInfo', {
    get() {
        return `${this.types} (${this.cnt})`;
    },
    set(x, y) {
        this.types = x;
        this.cnt = y;
    },
    enumerable: true,
    configurable: true
});

//object.defineproperty najczesciej do get/set ale mozna do wszystkiego
//normalnie tylko pola i funkcje