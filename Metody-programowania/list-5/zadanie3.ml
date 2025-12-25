let compare_nawiasy (left, right) c =
  match c with
  | '(' -> (left + 1, right)
  | ')' -> if left > right then (left, right + 1) else (-1, -1)
 (* | ' ' -> (left, right)*)
  | _ -> (-1, -1)

let list_of_string s = String.to_seq s |> List.of_seq

let parens_ok xs =
  let rec fold_left f acc xs =
    match xs with
    | [] -> acc
    | x :: xs' -> let res = f acc x in 
    if fst res = -1 then res 
    else fold_left f (res) xs' 
  in let (left, right) = fold_left compare_nawiasy (0,0) (list_of_string xs)
in if (left=right) && (left >= 0) then true else false
