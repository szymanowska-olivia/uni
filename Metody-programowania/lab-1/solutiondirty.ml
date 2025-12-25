type 'a tree = Leaf | Node of 'a tree * 'a * 'a tree
type 'a sgtree = { tree : 'a tree; size : int; max_size: int }

let alpha_num = 3
let alpha_denom = 4

let alpha = float_of_int alpha_num /. float_of_int alpha_denom

let alpha_height (n : int) : int =
  if n <= 1 then 0 else
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
  let rec aux t =
    match t with
    | Leaf -> false
    | Node (l, v, r) ->
        if x < v then aux l
        else if x > v then aux r
        else true
  in
  aux sgt.tree

type 'a context = (bool * 'a * 'a tree) list

let insert (x : 'a) (sgt : 'a sgtree) : 'a sgtree =
  (* Oblicz rozmiar poddrzewa *)
  let rec size t =
    match t with
    | Leaf -> 0
    | Node (l, _, r) -> 1 + size l + size r
  in

  (* Maksymalna dopuszczalna wysokość drzewa *)
  let alpha_h = alpha_height (sgt.size + 1) in

  (* Zipperowa ścieżka w dół — zapamiętujemy kontekst *)
  let rec insert_zip t ctx depth =
    (* Debug: wypisanie stanu zippera przed każdym krokiem 
    Printf.printf "Insert step - Current Tree: %s, Context: [%s], Depth: %d\n"
      (match t with Leaf -> "Leaf" | Node (_, v, _) -> Printf.sprintf "Node(%d)" v)
      (String.concat "; " (List.map (fun (dir, v, _) -> Printf.sprintf "(%b, %d)" dir v) ctx))
      depth;
    *)
    match t with
    | Leaf -> (Node (Leaf, x, Leaf), ctx, depth)
    | Node (l, v, r) ->
        if x < v then insert_zip l ((true, v, r) :: ctx) (depth + 1)
        else if x > v then insert_zip r ((false, v, l) :: ctx) (depth + 1)
        else (t, ctx, depth) (* już istnieje — nie wstawiamy ponownie *)
  in

  (* Sprawdzanie, czy trzeba przebudować któreś z poddrzew po drodze *)
  let rec rebuild_if_needed subtree ctx =
    let rec go current ctx_rev ctx_tail =
      match ctx_tail with
      | [] -> None
      | (dir, v, sibling) :: rest ->
          let parent =
            if dir then Node (current, v, sibling)
            else Node (sibling, v, current)
          in
          let l_size = size (match parent with Node (l, _, _) -> l | _ -> Leaf) in
          let r_size = size (match parent with Node (_, _, r) -> r | _ -> Leaf) in
          let total = l_size + r_size + 1 in
          (* Debug: Wypisanie informacji o przebudowie 
          Printf.printf "Rebuild check - Parent Node: %d, Left size: %d, Right size: %d, Total: %d\n"
            v l_size r_size total;*)
          if float_of_int l_size > alpha *. float_of_int total ||
             float_of_int r_size > alpha *. float_of_int total
          then 
            match ctx_tail with
            | _::ctx_fin-> Some (parent, ctx_fin)
            | [] -> Some (parent, [])
          else go parent ((dir, v, sibling) :: ctx_rev) rest
    in
    go subtree [] ctx
  in

  (* Składanie drzewa z powrotem na podstawie kontekstu *)
  let rec plug t ctx =
    (* Debug: Wypisanie ctx przed wykonaniem plug 
    Printf.printf "Context before plug: [%s]\n"
      (String.concat "; " (List.map (fun (dir, v, _) -> Printf.sprintf "(%b, %d)" dir v) ctx));*)

    List.fold_left (fun acc (dir, v, sibling) ->
      (* Debug: Wypisanie każdego kroku przy składaniu drzewa 
      Printf.printf "Plugging: Direction: %b, Value: %d, Sibling: %s\n"
        dir v (match sibling with Leaf -> "Leaf" | Node (_, sv, _) -> Printf.sprintf "Node(%d)" sv);*)
      
      if dir then Node (acc, v, sibling)
      else Node (sibling, v, acc)
    ) t ctx
  in

  (* Przechodzimy do miejsca wstawienia *)
  let (inserted_subtree, ctx, depth) = insert_zip sgt.tree [] 0 in

  (* Debug: Wypisanie stanu przed wstawieniem nowego poddrzewa 
  Printf.printf "Inserted Subtree: %s\n"
    (match inserted_subtree with Leaf -> "Leaf" | Node (_, v, _) -> Printf.sprintf "Node(%d)" v);*)

  (* Jeśli wstawiamy duplikat, nie zmieniamy drzewa *)
  if inserted_subtree = sgt.tree then sgt
  else
    let new_tree = plug inserted_subtree ctx in

    (* Debug: Wypisanie stanu tree po wstawieniu 
    Printf.printf "New Tree after Insertion: %s\n"
      (match new_tree with Leaf -> "Leaf" | Node (_, v, _) -> Printf.sprintf "Node(%d)" v);*)

    let updated = { tree = new_tree; size = sgt.size + 1; max_size = sgt.max_size } in

    (* Sprawdzamy, czy nie przekroczyliśmy wysokości alpha *)
    if depth <= alpha_h then updated
    else
      match rebuild_if_needed inserted_subtree ctx with
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
              let rec min t =
                match t with
                | Node (Leaf, v, _) -> v
                | Node (l, _, _) -> min l
                | Leaf -> failwith "Unexpected Leaf"
              in
              let m = min r in
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
