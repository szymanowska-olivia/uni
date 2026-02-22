import fs from 'fs';

const path = './tekst.txt';

fs.readFile(path, 'utf8', (err, data) => {
    if (err) {
        console.error('Blad', err);
        return;
    }
    console.log('tekst z pliku: ');
    console.log(data);
});
