exception Stop

let for_all (p : 'a -> bool) (xs : 'a list) : bool =
  try 
    List.fold_left (fun _ x -> 
    if (p x) = true then true
    else raise Stop ) true xs
  with Stop -> false

let mult_list (xs : int list) : int =
  try
    List.fold_left (fun acc x ->
      if x = 0 then raise Stop
      else acc * x ) 1 xs
  with Stop -> 0 

let sorted (xs : int list) : bool =
  match xs with
  | [] -> true
  | x::xs' -> (try ignore
                (List.fold_left (fun acc x ->
                    if x < acc then raise Stop
                    else x) x xs'); true
              with Stop -> false)
            