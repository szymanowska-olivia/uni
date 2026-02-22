const max = 100000;
const is_prime = Array(max + 1).fill(true);

is_prime[0] = false;
is_prime[1] = false;


for (let i = 2; i * i <= max; i++){
    if (!is_prime[i]) continue;
    for ( let j = i * i; j <= max; j+=i) is_prime[j] = false;
}

is_prime.forEach((val, idx) => val && console.log(idx));
