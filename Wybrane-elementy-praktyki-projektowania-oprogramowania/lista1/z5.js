function fib_rec(n){
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fib_rec(n-1) + fib_rec(n-2);
}

function fib_it(n){
    prev2 = 0;
    prev = 1;
    for (let i = 2; i <=n ; i++){
        pom = prev + prev2;
        prev = pom;
        prev2 = prev;
    }
    return prev;
}

for(let i = 10; i <= 60; i++){
    console.time("fib_rec_" + i);
    console.log(fib_rec(i));
    console.timeEnd("fib_rec_" + i);

    console.time("fib_it_" + i);
    console.log(fib_it(i));
    console.timeEnd("fib_it_" + i);
}
//wyniki zblizone, przy n = 45 chrome wolniejszy 0.7s