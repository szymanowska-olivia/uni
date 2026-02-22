let length' xs = List.fold_left (fun acc _ -> acc + 1 ) 0 xs
let rev' xs = List.fold_left (fun xs' x -> x::xs') [] xs
let map' xs f = List.fold_right (fun xs' x -> (f x)::xs') [] xs
let append' xs ys = List.fold_right (fun x xs' -> x::xs') xs ys
let rev_append' xs ys = List.fold_left (fun xs' x -> x::xs') ys xs
let filter' xs p = List.fold_right (fun x xs' -> if p x = true then x::xs' else xs') xs []
let rev_map' xs f = List.fold_left (fun x xs' -> (f x)::xs') xs [] 
(*destruktor nakarmiony consem robi konstruktor*)