let rec niemalejaca lista =
  match lista with
  | [] -> true
  | [_] -> true
  | x :: y :: reszta ->
      if x <= y then niemalejaca (y :: reszta)
      else false

let rec wstaw x lista =
  match lista with
  | [] -> [x]
  | y :: ys -> if x <= y then x :: lista
               else y :: wstaw x ys

let rec insertion_sort lista =
  match lista with
  | [] -> []
  | x :: xs -> wstaw x (insertion_sort xs)

