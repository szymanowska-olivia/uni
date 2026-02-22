const fs = require("fs");

const ips = ["12.34.56.78", "23.45.67.89", "123.245.167.289", "192.168.0.1", "10.0.0.5", "44.55.66.77", "8.8.8.8", "8.8.4.4", "1.1.1.1", "172.16.0.2", "172.16.0.3", "192.0.2.1"];

const methods = ["GET", "POST", "PUT", "DELETE", "PATCH"];
const resources = ["/a", "/b", "/c", "/d", "/e"];
const statuses = ["200", "201", "204", "301", "302", "400", "403", "404", "500", "502"];

const out = fs.createWriteStream("log.txt");

function rand(arr) {
  return arr[Math.floor(Math.random() * arr.length)];
}

for (let i = 0; i < 100000; i++) {
  const line = `${new Date().toTimeString().slice(0,8)} ` +
    `${rand(ips)} ` +
    `${rand(methods)} ` +
    `${rand(resources)} ` +
    `${rand(statuses)}\n`;
  out.write(line);
}

out.end(() => console.log("Wygenerowano log.txt"));
