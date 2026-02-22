type 'a clist = {clist : 'z. ('a -> 'z -> 'z) -> 'z -> 'z}

let cnil = {clist = fun f z -> z}
let ccons x xs = {clist = fun f z -> f x (xs.clist f z)} (*mamy ta wartosc poczatkowa 
f z i nakladamy ja tyle razy ile jest wyrazow w xs, potem doczepiamy glowe*)
let map g xs = {clist = fun f z -> xs.clist (fun )}



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

(*ista Churcha jest funkcją, która mówi: 
„jeśli dasz mi funkcję f i wartość początkową z, 
to zastosuję f kolejno do wszystkich elementów”.*)