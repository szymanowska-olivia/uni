"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
function fib(n) {
    if (n <= 1)
        return n;
    return fib(n - 1) + fib(n - 2);
}
function memoize(fn) {
    const mem = new Map();
    return ((...args) => {
        const key = JSON.stringify(args);
        if (mem.has(key))
            return mem.get(key);
        const res = fn(...args);
        mem.set(key, res);
        return res;
    });
}
const fibMemo = memoize(fib);
console.log(fibMemo(40));
//# sourceMappingURL=2.js.map