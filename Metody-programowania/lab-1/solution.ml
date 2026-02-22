type 'a tree = Leaf | Node of 'a tree * 'a * 'a tree
type 'a sgtree = { tree : 'a tree; size : int; max_size: int }
type 'a context = (bool * 'a * 'a tree) list (*zipper*)

let alpha_num = 3
let alpha_denom = 4

let alpha = float_of_int alpha_num /. float_of_int alpha_denom

let alpha_height (n : int) : int =
  int_of_float (Float.floor (Float.log (float_of_int n) /. Float.log (1.0 /. alpha)))

let rebuild_balanced (t : 'a tree) : 'a tree =
  let rec flatten t acc =
    match t with
    | Leaf -> acc
    | Node (l, v, r) ->
        let acc = flatten r acc in
        let acc = v :: acc in
        flatten l acc
  in
  let sorted = flatten t [] |> Array.of_list in
  let rec build l r =
    if l > r then Leaf
    else
      let m = l + (r - l) / 2 in
      Node (build l (m - 1), sorted.(m), build (m + 1) r)
  in
  build 0 (Array.length sorted - 1)

let empty : 'a sgtree = { tree = Leaf; size = 0; max_size = 0 }

let find (x : 'a) (sgt : 'a sgtree) : bool =
  let rec it t =
    match t with
    | Leaf -> false
    | Node (l, v, r) ->
        if x < v then it l
        else if x > v then it r
        else true
  in
  it sgt.tree

let insert (x : 'a) (sgt : 'a sgtree) : 'a sgtree =
  let rec size t =
    match t with
    | Leaf -> 0
    | Node (l, _, r) -> 1 + size l + size r
  in

  let alpha_h = alpha_height (sgt.size + 1) in
  
  let rec insert_remember t ctx depth =
    match t with
    | Leaf -> (Node (Leaf, x, Leaf), ctx, depth)
    | Node (l, v, r) ->
        if x < v then insert_remember l ((true, v, r) :: ctx) (depth + 1)
        else if x > v then insert_remember r ((false, v, l) :: ctx) (depth + 1)
        else (t, ctx, depth) 
  in

  let rec goat subtree ctx =
    let rec it current ctx_rev ctx_tail =
      match ctx_tail with
      | [] -> None
      | (where, v, sibling) :: rest ->
          let parent =
            if where then Node (current, v, sibling)
            else Node (sibling, v, current)
          in
          let ls = size (match parent with Node (l, _, _) -> l | _ -> Leaf) in
          let rs = size (match parent with Node (_, _, r) -> r | _ -> Leaf) in
          let total = ls + rs + 1 in
          if float_of_int ls > alpha *. float_of_int total || float_of_int rs > alpha *. float_of_int total
          then Some (parent, rest)
          else it parent ((where, v, sibling) :: ctx_rev) rest
    in
    it subtree [] ctx
  in

  let rec plug t ctx =
    List.fold_left (fun acc (where, v, sibling) ->
      if where then Node (acc, v, sibling)
      else Node (sibling, v, acc)
    ) t ctx
  in

  if find x sgt then failwith "x already exists"
  else

  let (inserted_subtree, ctx, depth) = insert_remember sgt.tree [] 0 in
    let new_tree = plug inserted_subtree ctx in
    let updated = { tree = new_tree; size = sgt.size + 1; max_size = sgt.max_size } in

    if depth <= alpha_h then updated
    else
      match goat inserted_subtree ctx with
      | None -> updated
      | Some (unbalanced, path_to_unbalanced) ->
          let rebuilt = rebuild_balanced unbalanced in
          let final_tree = plug rebuilt path_to_unbalanced in
          { tree = final_tree; size = updated.size; max_size = updated.max_size }

let remove (x : 'a) (sgt : 'a sgtree) : 'a sgtree =
  let rec remove t =
    match t with
    | Leaf -> Leaf
    | Node (l, v, r) ->
        if x < v then Node (remove l, v, r)
        else if x > v then Node (l, v, remove r)
        else match l, r with
          | Leaf, Leaf -> Leaf
          | Leaf, _ -> r
          | _, Leaf -> l
          | _ ->
              let rec mini t =
                match t with
                | Node (Leaf, v, _) -> v
                | Node (l, _, _) -> mini l
                | Leaf -> failwith "leaf"
              in
              let m = mini r in
              Node (l, m, remove r)
  in

  if not (find x sgt) then failwith "x not found"
  else
    let new_size = sgt.size - 1 in
    let new_tree = remove sgt.tree in
    if float_of_int new_size < alpha *. float_of_int sgt.max_size then
      let rebuilt = rebuild_balanced new_tree in
      { tree = rebuilt; size = new_size; max_size = new_size }
    else
      { tree = new_tree; size = new_size; max_size = sgt.max_size }
