let rec fold_left f acc xs =
  match xs with
  | [] -> acc
  | x :: xs -> fold_left f (f acc x) xs

let rec fold_left_cps (f : 'a -> 'b -> ('a -> 'c) -> 'c) 
(acc : 'a) (xs : 'b list) (k : 'a -> 'c) : 'c =
  match xs with 
  | [] -> k acc
  | x :: xs' -> f acc x (fun acc' -> fold_left_cps f acc' xs' k)

(* w fold_left f acc x  aplikuje jakas funkcje na f i acc - zwraca nowy akumulator
ale robimy to w cps wiec nie chcemy zwrocic od razu nowego akumulatora tylko
to co się z nim dzieje pózniej*)

let rec fold_left_from_cps (f : 'a -> 'b -> ('a -> 'c) -> 'c) 
(acc : 'a) (xs : 'b list) = 
let k (x : 'a) : 'c = x in fold_left_cps f acc xs k

