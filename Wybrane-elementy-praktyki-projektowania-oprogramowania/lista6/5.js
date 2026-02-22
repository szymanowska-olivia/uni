"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const persons = [
    {
        name: 'Jan Kowalski',
        age: 17,
        occupation: 'Student'
    },
    {
        name: 'Tomasz Malinowski',
        age: 20,
        role: 'Administrator'
    }
];
function isAdmin(person) {
    return 'role' in person;
}
/*
function isAdmin(person: Person) {
    return 'role' in person;
}
*/
function isUser(person) {
    return 'occupation' in person;
}
function logPerson(person) {
    let additionalInformation = '';
    if (isAdmin(person)) {
        additionalInformation = person.role;
    }
    if (isUser(person)) {
        additionalInformation = person.occupation;
    }
    console.log(' - ${person.name}, ${person.age}, ${additionalInformation}');
}
//# sourceMappingURL=5.js.map