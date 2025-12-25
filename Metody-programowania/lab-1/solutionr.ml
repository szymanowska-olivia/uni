let alpha_num = 3
let alpha_denom = 4

type 'a tree = Leaf | Node of 'a tree * 'a * 'a tree
type 'a sgtree = { tree : 'a tree; size : int; max_size: int }

let alpha_height (n : int) : int =
  let logarytm : float = (Float.log (float_of_int n)) /. (Float.log (float_of_int alpha_denom /. float_of_int alpha_num)) in
  int_of_float (Float.floor logarytm)

let rebuild_balanced (t : 'a tree) : 'a tree =
  let rec flatten acc = function
    | Leaf -> acc
    | Node (left, value, right) ->
        let acc = flatten acc left in
        let acc = value :: acc in
        flatten acc right
  in

  let flattened_array = Array.of_list (List.rev (flatten [] t)) in

  let rec build arr start_idx end_idx =
    if start_idx > end_idx then Leaf
    else
      let len = end_idx - start_idx + 1 in
      let mid = start_idx + (len - 1) / 2 in
      let left = build arr start_idx (mid - 1) in
      let right = build arr (mid + 1) end_idx in
      Node (left, arr.(mid), right)
  in

  build flattened_array 0 (Array.length flattened_array - 1)

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
  let rec size_of_tree (t : 'a tree) : int =
    match t with
    | Leaf -> 0
    | Node (l, _, r) -> 1 + size_of_tree l + size_of_tree r
  in

  let { tree; size; max_size } = sgt in

  let rec better_find x t context depth =
    match t with
    | Leaf -> (Node (Leaf, x, Leaf), depth + 1, context)
    | Node (l, v, r) ->
        let current_size = size_of_tree t in
        if x < v then
          let (new_left, d, new_context) = better_find x l context (depth + 1) in
          let rebuilt = Node (new_left, v, r) in
          (rebuilt, d, (rebuilt, true, current_size) :: new_context)
        else if x > v then
          let (new_right, d, new_context) = better_find x r context (depth + 1) in
          let rebuilt = Node (l, v, new_right) in
          (rebuilt, d, (rebuilt, false, current_size) :: new_context)
        else
          (t, depth, context)
  in

  let (new_tree, depth, context) = better_find x tree [] 0 in
  let updated_sgt = { tree = new_tree; size = size + 1; max_size = max_size } in

  if depth <= alpha_height updated_sgt.size + 1 then
    updated_sgt
  else
    let rec find_goat_from_context ctx =
      let rec aux ctx acc =
        match ctx with
        | [] -> None
        | (Node (l, v, r) as t, went_left, size) :: rest ->
            let left_size = match l with Leaf -> 0 | _ -> size_of_tree l in
            let right_size = match r with Leaf -> 0 | _ -> size_of_tree r in
            let total_size = left_size + right_size + 1 in
            let left_balance = float_of_int left_size /. float_of_int total_size in
            let right_balance = float_of_int right_size /. float_of_int total_size in

            if left_balance > (float_of_int alpha_num /. float_of_int alpha_denom)
            || right_balance > (float_of_int alpha_num /. float_of_int alpha_denom)
            then Some (t, acc, v)
            else aux rest ((t, went_left, size) :: acc)
        | _ -> None
      in
      aux ctx []
    in

    match find_goat_from_context (List.rev context) with
    | None -> updated_sgt
    | Some (goat_tree, _, ko) ->
        let rebuilt_subtree = rebuild_balanced goat_tree in

        let rec find_path_to_goat (t : 'a tree) (goat_value : 'a) : ('a tree * bool * int) list =
          let rec aux t acc =
            match t with
            | Leaf -> acc
            | Node (l, v, r) ->
                if v = goat_value then (Node (l, v, r), false, 0) :: acc
                else if goat_value < v then aux l ((Node (l, v, r), true, 0) :: acc)
                else aux r ((Node (l, v, r), false, 0) :: acc)
          in
          aux t []
        in

        let path_to_goat = find_path_to_goat new_tree ko in

        let rec plug subtree context =
          match context with
          | [] -> subtree
          | (Node (l, v, r), went_left, _) :: rest ->
              let new_tree =
                if went_left then Node (subtree, v, r)
                else Node (l, v, subtree)
              in
              plug new_tree rest
        in

        match path_to_goat with
        | _ :: rightous_path_to_goat ->
            let final_tree = plug rebuilt_subtree rightous_path_to_goat in
            { tree = final_tree; size = updated_sgt.size; max_size = updated_sgt.max_size }

let remove (x : 'a) (sgt : 'a sgtree) : 'a sgtree =
  let alpha = 0.75 in

  let rec remove_from_tree x tree =
    match tree with
    | Leaf -> Leaf
    | Node (l, v, r) ->
        if x < v then
          let l' = remove_from_tree x l in Node (l', v, r)
        else if x > v then
          let r' = remove_from_tree x r in Node (l, v, r')
        else
          match (l, r) with
          | Leaf, Leaf -> Leaf
          | Leaf, _ -> r
          | _, Leaf -> l
          | _ ->
              let rec find_min t =
                match t with
                | Node (Leaf, v, _) -> v
                | Node (l, _, _) -> find_min l
                | Leaf -> failwith "Unexpected Leaf"
              in
              let min_right = find_min r in
              let r' = remove_from_tree min_right r in
              Node (l, min_right, r')
  in

  let exists = find x sgt in
  if not exists then failwith "x does not exist"
  else
    let after_remove = remove_from_tree x sgt.tree in
    let after_remove_size = sgt.size - 1 in
    if float_of_int after_remove_size < float_of_int sgt.max_size *. (float_of_int alpha_num /. float_of_int alpha_denom)
    then
      let final = rebuild_balanced after_remove in
      { tree = final; size = after_remove_size; max_size = after_remove_size }
    else
      { tree = after_remove; size = after_remove_size; max_size = sgt.max_size }
