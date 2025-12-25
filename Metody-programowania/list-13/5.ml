(* Sprawdzenie, czy lista jest niemalejąca *)
let rec niemalejaca lista =
  match lista with
  | [] -> true
  | [_] -> true
  | x :: y :: reszta ->
      if x <= y then niemalejaca (y :: reszta)
      else false

(* Wstawienie elementu na właściwe miejsce *)
let rec wstaw x lista =
  match lista with
  | [] -> [x]
  | y :: ys -> if x <= y then x :: lista
               else y :: wstaw x ys

(* Sortowanie przez wstawianie *)
let rec insertion_sort lista =
  match lista with
  | [] -> []
  | x :: xs -> wstaw x (insertion_sort xs)

(* Sprawdzenie, czy dwie listy są permutacjami - implementacja relacji ∼ *)

(* Zamiana dwóch sąsiednich elementów w liście *)
let rec zamien_sasiednie x y lista =
  match lista with
  | [] -> []
  | z :: zs when z = x && (match zs with y' :: _ when y' = y -> true | _ -> false) ->
      y :: x :: (match zs with _ :: reszta -> reszta | _ -> [])
  | z :: zs -> z :: zamien_sasiednie x y zs

(* Sprawdzenie czy dwie listy mają te same elementy z tą samą liczbą powtórzeń *)
let rec jest_permutacja l1 l2 =
  let rec usun x lista =
    match lista with
    | [] -> []
    | y :: ys -> if x = y then ys else y :: usun x ys
  in
  match l1, l2 with
  | [], [] -> true
  | x :: xs, _ ->
      if List.mem x l2 then
        jest_permutacja xs (usun x l2)
      else
        false
  | _, _ -> false

(* Testy *)
let () =
  let lista = [3; 1; 4; 2] in
  let posortowana = insertion_sort lista in
  Printf.printf "Lista wejściowa: ";
  List.iter (Printf.printf "%d ") lista;
  Printf.printf "\nPosortowana: ";
  List.iter (Printf.printf "%d ") posortowana;
  Printf.printf "\nCzy niemalejąca? %b" (niemalejaca posortowana);
  Printf.printf "\nCzy permutacja oryginału? %b\n" (jest_permutacja lista posortowana)
