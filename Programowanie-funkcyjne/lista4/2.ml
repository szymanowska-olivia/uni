type 'a zlist = {
  left  : 'a list;  
  right : 'a list;  
}

let of_list l = { left = []; right = l }

let to_list z = List.rev z.left @ z.right

let elem z = 
  match z.right with
  | x::_ -> Some x
  | _ -> None

let move_left z = 
  match z.left with
  | x::xs -> {left = xs; right = x::z.right} 
  | _ -> z

let move_right z = 
  match z.right with
  | x::xs -> {left = x::z.left; right = xs}
  |_ -> z

let insert x z = { left = x :: z.left; right = z.right }
{ z with left = }
let remove z = 
  match z.left with
  | x::xs-> {left = xs; right = z.right}
  | _ -> z

  