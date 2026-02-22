import https from 'https';

function getPage(url) {
    return new Promise((resolve, reject) => {
        https.get(url, (response) => {
            let res = '';

            response.on('data', x => {
                res += x;
            });

            response.on('end', () => {
                resolve(res);
            });

        }).on('error', (err) => {
            reject(err);
        });
    });
}
async function main() {
    try {
        const html = await getPage("https://skos.ii.uni.wroc.pl/course/view.php?id=828");
        console.log("zawartość strony:\n");
        console.log(html);
    } catch (e) {
        console.error("Blad:", e);
    }
}

main();

