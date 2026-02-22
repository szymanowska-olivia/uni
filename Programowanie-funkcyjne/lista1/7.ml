let zero f x = x
let succ n = fun f x -> f (n f x)
let add n m = fun f x -> n f (m f x)
let mul n m = fun f x -> n (m f) x
let is_zero n = fun t f -> n (fun _ -> f) t 
let cnum_of_int x = 
  let rec it x n =
    if x>0 then it (x-1) (succ n)
    else n 
  in it x zero

let int_of_cnum n = n (fun x -> x + 1) 0

(*destrukcja cnum = indukcja*)




