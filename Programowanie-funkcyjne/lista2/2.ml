let sublists xs =
  List.fold_right
    (fun x acc ->
       let with_x = List.map (fun s -> x :: s) acc in 
       with_x @ acc) (*@ twoży nieużytki bo kopiujemy z with_x*)
    xs [[]]           (*do acc a with_x zostaje nieużytkiem*)
(* iteruje po akumulatorze czyli dodajac nowa 
liczbe tworzy sublisty z nia i liczbami po niej*)

(*rev_append lepszy bo wtedy nieużytkiem będzie wejscie 
zamiast acc a to już lepiej (??) (albo wgl nie bedzie nieuzytkow?)*)

(*zamiast map robimy map_append i wtedy nie ma nieużytków*)