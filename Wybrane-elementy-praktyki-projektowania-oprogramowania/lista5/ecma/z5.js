import https from 'https';

const url = "https://skos.ii.uni.wroc.pl/course/view.php?id=828";

https.get(url, (response) => {
    let res = '';

    response.on('data', x => {
        res += x;
    });

    response.on('end', () => {
        console.log("zawartość strony:");
        console.log(res);
    });

}).on('error', (err) => {
    console.error("Blad", err);
});
