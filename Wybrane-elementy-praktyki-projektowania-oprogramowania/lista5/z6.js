const fs = require("fs");
const readline = require("readline");

const ipCount = {};

const rl = readline.createInterface({
  input: fs.createReadStream("log.txt"),
});

rl.on("line", (line) => {
  const ip = line.split(" ")[1];
  ipCount[ip] = (ipCount[ip] + 1|| 1); 
});

rl.on("close", () => {
  Object.entries(ipCount)//tablica z obiektu
    .sort((a, b) => b[1] - a[1])
    .slice(0, 3)
    .forEach(([ip, count]) => console.log(ip, count));
});
