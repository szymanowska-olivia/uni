type ('a, 'b) format = (string -> 'b) -> 'a

let lit (s : string) : ('a, 'a) format = fun k -> k s

let int : (int -> 'a, 'a) format = fun  k a-> k (string_of_int a)

let str : (string -> 'a, 'a) format = fun k s -> k s