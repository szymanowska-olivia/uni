(*type 'a stream = int -> 'a*)
let hd s =  s 0
let tl s = fun n -> s n+1

let add s x = fun n -> (s n) + x

let map f s = fun n -> f (s n)

let map f s1 s2 = fun n -> f (s1 n) (s2 n)

let replace n a s = 
  fun i ->
    if i = n then a
    else s i

let take_every n s = fun i -> s (i*n)

(*let natural_numbers : int stream = fun n -> n / n*n / c*)
(*implementacja strumienia liczb pierwszych

filter (p : 'a -> bool) (s: 'a stream) : 'a stream = 

let rec p n -> 
  if p (hd s) then hd s
  else f p(tl s)

let rec g p s n =
  if n = 0 then f p s
  else if p (hd s) then g p (hd s) (n-1)
        else g p (hd s) n
    *)