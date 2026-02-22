const max = 100000;
const res = [];

for (let i = 1; i <= max; i++){
    all = true;
    pom = i;
    sum = 0;
    while (pom > 0){
        if (i % (pom % 10) != 0){
            all = false;
            break;
        } 

        sum += pom%10;
        pom = Math.floor(pom / 10);

    }

    if(!all || i % sum != 0) continue;
    
    res.push(i);
}

console.log(res);