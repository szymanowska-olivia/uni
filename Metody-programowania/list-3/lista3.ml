(*(*zadanie 1*)
let product f a xs =    
   let rec it xs acc =
    match xs with
    | [] -> acc
    | x::xs -> it xs (f acc x)
  in it xs a;;

  (*product ( * ) 1 xs;;*)

  (*
  fold_right (fun x xs -> x::xs) [] xs

  jezeli dla tych samych argumentow zrobimy fold left i right to 
  left bedzie odwrocone
  *)

  (*zadanie 2*)
  let compose f g = fun x -> f (g x);;

  let square x = x * x;;

  let inc x = x + 1;;
  (*compose square inc 5 = fun x -> square(inc 5) 
  = square(5+1) = square 6 = 6*6 = 36
  
  compose inc square 5 = fun x -> inc(square 5)
  = inc (5*5) = inc 25 = 25+1 = 26*)

  (*zadanie 3*)
  let inc x = x + 1;;

  let build_list n f = 
    let rec it acc xs =
      if acc = n  then xs
      else it (inc acc) ((f n)::xs)
    in it 0 [];;

    (*let negatives n = 
      build_list (inc n) (fun n -> n * (-1))
      let xs = build_list 1 []
      match xs with 
      | [] -> []
      | x::xs' -> xs';;*)


    (*let reciprocals n = 
      let xs = build_list (inc n) (fun n -> 1.0 /. n)
      match xs with 
      | [] -> []
      | x::xs' -> xs';;*)

    let evens n = build_list n (fun n -> n + 2);;

   (* let identityM n =
      let it acc n ys =
      let xs = build_list n (fun n -> if n = acc then 1 else 0)
      if acc = n then ys
      else it (inc acc) n (xs::ys)
      in it 0 n [];;*)

  (*zadanie 4*)

  let empty_set  = fun _ -> false;;

  let singleton a = fun x -> x = a;;

  let in_set a s = s a;;  

  let union s t = fun x -> (s x) || (t x);;

  let intersect s t = fun x -> (s x) && (t x);;

  (*zadanie 5*)

  
  let t =
    Node ( Node ( Leaf , 2 , Leaf ) ,
            5 ,
            ( Node ( Node ( Leaf , 6 , Leaf ) ) ,
                    8 ,
                    ( Node ( Leaf , 9 , Leaf ) ) ) );;

 (* 
          5
        /   \
      2      8
            /  \
          6      9  
*)

  type int_tree = IntLeaf | IntNode of int_tree * int * int_tree;;

  let rec insert_bst x t =
    match t with
    | Leaf -> Node (Leaf, x, Leaf)
    | Node (l, v, r) ->
        if x = v
        then t
        else if v < x
        then Node (l, v, insert_bst x r)
        else Node (insert_bst x l, v, r);; 

  insert_bst 7 t;;


(* 
           5
          / \
         2   8
            / \
           6   9 
            \
             7 
*)

(*zadanie 6*)

let rec fold_tree f a t =
  match t with
  | Leaf -> a
  | Node (l, v, r) -> f (fold_tree f a l) v (fold_tree f a r);;

let tree_product t = 
  fold_tree (fun l v r -> l * v * r) 1 t;;

let tree_flip t = 
  fold_tree (fun l v r -> Node (r, v, l)) Leaf t;;

let tree_height t = 
  fold_tree (fun l v r -> 1 + max l r) 0 t;;

let tree_span t =
    fold_tree (fun (l_min, l_max) v (r_min, r_max) ->
      (min l_min (min v r_min), max l_max (max v r_max))
    ) (max_int, min_int) t;;

let flatten t = 
  fold_tree (fun l v r -> l @ [v] @ r) [] t;;

(*zadanie 7*)

let flatten t =
  let rec flat_append t xs =
    match t with
    | Leaf -> xs
    | Node (l, v, r) -> flat_append l (v :: flat_append r xs)
  in flat_append t []

*)




