import readline from 'readline';

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

const rand = Math.floor(Math.random() * 101);
console.log("Zgadywanka, jaka liczba została wylosowana?");

function ask() {
  rl.question('Podaj liczbę: ', (input) => {
    const a = Number(input.trim()); 

    if (a === rand) {
      console.log(`To jest właśnie ta liczba! Wynik: ${rand}`);
      rl.close(); 
    } else if (a < rand) {
      console.log("Moja liczba jest większa.");
      ask(); 
    } else {
      console.log("Moja liczba jest mniejsza.");
      ask(); 
    }
  });
}

ask();
