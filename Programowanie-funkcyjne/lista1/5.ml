let tabulate ?(x=0) y s =
  let rec it xs n =
  if n<x then it [] (n+1)
  else if n >= x && n <= y then it ((s n)::xs) (n+1)
  else List.rev xs

  in it [] 0
 