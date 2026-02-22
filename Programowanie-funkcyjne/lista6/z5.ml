let rec fold_left_cps (f : 'a -> 'b -> ('a -> 'c) -> 'c) 
(acc : 'a) (xs : 'b list) (k : 'a -> 'c) : 'c =
  match xs with 
  | [] -> k acc
  | x :: xs' -> f acc x (fun acc' -> fold_left_cps f acc' xs' k)

let rec fold_left_cps_mod f acc xs k break =
  match xs with
  | [] -> k acc
  | x :: xs' ->
      if break acc x then acc
      else f acc x (fun acc' -> fold_left_cps_mod f acc' xs' k break)

let for_all p xs =
  let f acc x k = k (acc && p x) in
  fold_left_cps_mod f true xs (fun acc -> acc) (fun acc x -> acc <> p x)

let mult_list xs =
  let f acc x k = k (acc * x) in
  fold_left_cps_mod f 1 xs (fun acc -> acc) (fun _ x -> x = 0)

let sorted xs =
  match xs with
  | [] | [_] -> true
  | first :: rest ->
      let f prev x k = k x in
      fold_left_cps_mod f first rest (fun _ -> true) (fun acc x -> acc > x)

