type cbool = { cbool : 'a. 'a -> 'a -> 'a }
type cnum  = { cnum  : 'a. ('a -> 'a) -> 'a -> 'a }

let ctrue = {cbool = fun t f -> t}
let cfalse = {cbool = fun t f -> f}  

let cand p q = 
  { cbool = fun t f -> p.cbool (q.cbool t f) f }

let cor p q = 
  { cbool = fun t f -> p.cbool t (q.cbool t f) }

let cbool_of_bool b =
    if b = true then ctrue
    else cfalse

let bool_of_cbool p = p.cbool true false


let zero = {cnum = fun f x -> x}
let succ n = {cnum = fun f x -> f (n.cnum f x)}
let add n m = {cnum = fun f x -> n.cnum f (m.cnum f x)}
let mul n m = {cnum = fun f x -> n.cnum (m.cnum f) x }
let is_zero n = {cbool = fun t f -> n.cnum (fun _ -> f) t }
let cnum_of_int x = 
  let rec it x n =
    if x>0 then it (x-1) (succ n)
    else n
  in it x zero

let int_of_cnum n = n.cnum (fun x -> x + 1) 0






