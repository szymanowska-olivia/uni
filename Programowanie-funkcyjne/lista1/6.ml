let ctrue t f = t
let cfalse t f = f 

let cand p q = 
  fun t f -> p (q t f) f

let cor p q = 
  fun t f -> p t (q t f)

let cbool_of_bool b =     (*destruktor*) (*bool -> 'a -> 'a -> 'a = typ ifa*)
    if b = true then ctrue
    else cfalse 

let bool_of_cbool p = p true false