let rec fix f x = f (fix f) x

let rec fix_with_limit limit f x = 
  if limit >= 0 then f (fix_with_limit (limit - 1) f) x
  else raise (Failure "recursion went over the limit")

let fix_memo f =
  let table = Hashtbl.create 100 in
  let rec it x = 
    if Hashtbl.mem table x then Hashtbl.find table x
    else Hashtbl.add table x (f it x)
  in it 

let fib_f fib n =
  if n <= 1 then n
  else fib (n-1) + fib (n-2)

let fib = fix fib_f
