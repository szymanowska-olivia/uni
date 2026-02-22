fun x -> x + 0;;

fun f g x -> f(g x);;
fun x y -> x;;
fun x x-> x;; (*failwith*)

let rec it x = it x;; (*nie robi efektow ubocznych
kazda funkcja ktora ich nie ma sie zapetla i jest tautologia

jezeli jest funknckja ktorej typ nie jest tautologia ma efekty uboczne*)
let it2 x = failwith " ";;
Obj.magic