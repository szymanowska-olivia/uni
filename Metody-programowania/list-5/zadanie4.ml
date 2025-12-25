let compare_nawiasy2 (left, right, last_left) c =
  match c with
  | '(' -> (left + 1, right, '(') 
  | ')' -> if left > right && last_left = '(' then (left, right + 1, '(') else (-1, -1, ' ')
  | '{' -> (left + 1, right, '{') 
  | '}' -> if left > right && last_left = '{' then (left, right + 1, '{') else (-1, -1, ' ')
  | '[' -> (left + 1, right, '[') 
  | ']' -> if left > right && last_left = '[' then (left, right + 1, '[') else (-1, -1, ' ')
  | _ -> (-1, -1, ' ')

let list_of_string s = String.to_seq s |> List.of_seq

let parens_ok2 xs =
let rec fold_left_mod : (int * int * char -> char -> int * int * char) -> (int * int * char) -> char list -> (int * int * char) =
  fun f acc xs -> 
    match xs with
    | [] -> acc
    | x :: xs' -> 
      let (p, r, s) = f acc x in 
      if p = -1 then (p, r, s)
      else fold_left_mod f (p, r, s) xs'
  in 
  let (left, right, _) = fold_left_mod compare_nawiasy2 (0,0,' ') (list_of_string xs) 
  in left = right && left >= 0
