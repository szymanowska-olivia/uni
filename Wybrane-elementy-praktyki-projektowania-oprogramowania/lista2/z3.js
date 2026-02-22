//console.log( (![]+[])[+[]]+(![]+[])[+!+[]]+([![]]+[][[]])[+!+[]+[+[]]]+(![]+[])[!+[]+!+[]] );
//string "fail"

console.log( (![]+[])[+[]]) 
// [] = true, więc ![] = false 
// (![]+[]) = false + [] - konwertuje się na stringi "false" + "" = "false"
// [+[]] - + przed wartościa konwertuje do typu liczbowego, więc +[] = 0
// zatem [+[]] = [0] => (![]+[])[+[]] = "false"[0] => 'f'

console.log( (![]+[])[+!+[]]) 
// (![]+[]) = "false"
//  [+!+[]] = 1 - +[] = 0 => !+[] = !0 = true => +!+[] = +true = 1 
//  (![]+[])[+!+[]] = "false"[1] = 'a'
console.log( ([![]]+[][[]])[+!+[]+[+[]]])
// ([![]]+[][[]]) = [false]+[][[]] = "false"+[][[]]
// [][[]] = pusta tablica o indeksie ?? = undefined bo nie ma takiego indeksu
// ([![]]+[][[]]) = "false" + undefined = "false" + "undefined" = "falseundefined"

//[+!+[]+[+[]]] = [+!+[]+[0]] = [+!0+[0]] = [+true+[0]] = [1+[0]] = [1+"0"] = ["10"] = [10] 
//[![]]+[][[]])[+!+[]+[+[]]] = "falseundefined"[10] = 'i'

console.log( (![]+[])[!+[]+!+[]])
// (![]+[]) = "false"
// [!+[]+!+[]] = [!0+!0] = [true + true] = [1 + 1] = [2]
// (![]+[])[!+[]+!+[]] = "false"[2] = 'l'


console.log( (![]+[])[+[]]+(![]+[])[+!+[]]+([![]]+[][[]])[+!+[]+[+[]]]+(![]+[])[!+[]+!+[]] );
// 'f' + 'a' + 'i' + 'l' = "fail"