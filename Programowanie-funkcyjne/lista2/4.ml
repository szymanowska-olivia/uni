let merge cmp xs ys =
  List.fold_left
  (fun acc y ->
    let rec it acc y =
      match acc with
      | x::xs' -> if (cmp y x) then y::acc else x :: it xs' y
      | [] -> [y] (*wracająć z rekurencji doklejamy tutaj  ^^^*)
    in it acc y)
    xs ys

let merge_w_tail cmp xs ys =
  let rec it cmp xs ys acc =
    match xs, ys with
    | x::xs', y::ys' -> 
      if cmp x y then it cmp xs' ys (x::acc) 
      else it cmp xs ys' (y::acc)
    | x::xs', [] -> it cmp xs' ys (x::acc)
    | [], y::ys' -> it cmp xs ys' (y::acc)
    | [], [] -> acc
  in List.rev (it cmp xs ys []) 

let halve xs =
  let rec it every1 every2 fsthalf =
    match every1, every2 with
    | x::xs', y::y'::ys' -> it xs' ys' (x::fsthalf)
    | x::xs', _ -> (List.rev fsthalf, xs')
    | [], _ -> ([], [])
  in it xs xs []

let rec mergesort xs cmp = 
  match xs with 
  | []  | [_] -> xs
  | _ ->
  match halve xs with
  | [x], [y] -> merge_w_tail cmp [x] [y]
  | [x], ys ->  merge_w_tail cmp [x] (mergesort ys cmp)
  | xs, [y] ->  merge_w_tail cmp [y] (mergesort xs cmp)
  | xs, ys ->  merge_w_tail cmp (mergesort xs cmp) (mergesort ys cmp)