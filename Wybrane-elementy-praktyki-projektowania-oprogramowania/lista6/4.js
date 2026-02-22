"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const persons = [
    {
        typ: 'user',
        name: 'Jan Kowalski',
        age: 17,
        occupation: 'Student'
    },
    {
        typ: 'admin',
        name: 'Tomasz Malinowski',
        age: 20,
        role: 'Administrator'
    }
];
function logPerson(person) {
    let additionalInformation;
    if (person.typ === 'admin') {
        additionalInformation = person.role;
    }
    else {
        additionalInformation = person.occupation;
    }
    console.log(' - ${person.name}, ${person.age}, ${additionalInformation}');
}
//# sourceMappingURL=4.js.map