let alpha_num = 3
let alpha_denom = 4

type 'a tree = Leaf | Node of 'a tree * 'a * 'a tree
type 'a sgtree = { tree : 'a tree; size : int; max_size: int }

let alpha_height (n : int) : int = 
  begin
    let logarytm : float = (Float.log (float_of_int n)) /. (Float.log (float_of_int alpha_denom/. float_of_int alpha_num)) in
    print_endline "halfa";
    print_endline (string_of_int (int_of_float (Float.floor logarytm)));
    int_of_float (Float.floor logarytm)

  end

let rebuild_balanced (t : 'a tree) : 'a tree = (*dfs -> sort -> rebuild*)
  (* Krok 1: Spłaszcz drzewo do posortowanej listy *)
  let rec flatten = function
    | Leaf -> []
    | Node (left, value, right) ->
        flatten left @ [value] @ flatten right
  in

  (* Zwraca pierwsze n elementów listy *)
let rec take n lst =
  match (n, lst) with
  | (0, _) | (_, []) -> []
  | (n, x :: xs) -> x :: take (n - 1) xs  in

(* Pomija pierwsze n elementów listy *)
let rec drop n lst =
  match (n, lst) with
  | (0, lst) -> lst
  | (_, []) -> []
  | (n, _ :: xs) -> drop (n - 1) xs in

  (* Krok 2: Zbuduj zbalansowane drzewo z posortowanej listy *)
  let rec build lst =
    match lst with
    | [] -> Leaf
    | _ ->
        let len = List.length lst in
        let mid = int_of_float (float_of_int len *. (1.0 -. (float_of_int alpha_num /. float_of_int alpha_denom))) in
        let mid = if mid >= len then len - 1 else mid in
        let left_list = take mid lst in
        let right_list = drop (mid + 1) lst in
        let root = List.nth lst mid in
        Node (build left_list, root, build right_list) in

  build (flatten t)
let empty : 'a sgtree = { tree = Leaf; size = 0; max_size = 0}

let find (x : 'a) (sgt : 'a sgtree) : bool =
  let rec it t =
    match t with
    | Leaf -> false
    | Node (l, v, r) ->
        if x < v then it l
        else if x > v then it r
        else true in
  it sgt.tree

let insert (x : 'a) (sgt : 'a sgtree) : 'a sgtree =
  let rec size_of_tree (t : 'a tree) : int =
    match t with
    | Leaf -> 0
    | Node (l, _, r) -> 1 + (size_of_tree l) + (size_of_tree r)
  in

  let { tree; size; max_size } = sgt in

  (* Wstawianie z jednoczesnym zapamiętywaniem ścieżki — naprawione *)
  let rec better_find x t context depth =
    match t with
    | Leaf ->
        (Node (Leaf, x, Leaf), depth + 1, context)
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

  print_endline "[debug] Drzewo po wstawieniu (pełna struktura):";
  let rec tree_to_string t =
    match t with
    | Leaf -> "Leaf"
    | Node (l, v, r) ->
        Printf.sprintf "Node (%s, %d, %s)" (tree_to_string l) v (tree_to_string r)
  in
  print_endline (tree_to_string updated_sgt.tree);
  print_endline (string_of_int depth);
  if depth <= alpha_height updated_sgt.size + 1 then begin
    print_endline "brak budowy";
    updated_sgt
  end else begin
    print_endline "bob budowniczy";
    let string_of_context context =
      let string_of_entry (_, went_left, _) =
        if went_left then "L" else "R"
      in
      context |> List.map string_of_entry |> String.concat " -> "
    in
    print_endline (string_of_context context);

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

            Printf.printf "[debug] Wartość węzła: %d, lewy rozmiar: %d, prawy rozmiar: %d, bilans lewego: %.2f, bilans prawego: %.2f\n"
              v left_size right_size left_balance right_balance;

            if left_balance > (float_of_int alpha_num /. float_of_int alpha_denom)
               || right_balance > (float_of_int alpha_num /. float_of_int alpha_denom)
            then begin
              Printf.printf "[debug] Kozioł ofiarny: %d\n" v;
              Some (t, acc, v)
            end
            else aux rest ((t, went_left, size) :: acc)
        | _ -> None
      in
      aux ctx []
    in

    match find_goat_from_context (List.rev context) with
  | None -> 
      print_endline "[debug] Pełne drzewo zostało zrekonstruowane! (brak lokalnego kozła)";
      updated_sgt
  | Some (goat_tree, path_to_goat, ko) -> 
      let rebuilt_subtree = rebuild_balanced goat_tree in
      print_endline "[debug] Przebudowano tylko lokalne poddrzewo kozła";

      (* Debugowanie: wypisanie ścieżki do kozła *)

     let rec find_path_to_goat (t : 'a tree) (goat_value : 'a) : ('a tree * bool * int) list =
          let rec aux t acc =
            match t with
            | Leaf -> acc
            | Node (l, v, r) ->
                if v = goat_value then
                  (* Wyszukaliśmy kozła, kończymy *)
                  (Node (l, v, r), false, 0) :: acc
                else if goat_value < v then
                  (* Idziemy w lewo *)
                  aux l ((Node (l, v, r), true, 0) :: acc)
                else
                  (* Idziemy w prawo *)
                  aux r ((Node (l, v, r), false, 0) :: acc)
          in
          aux t []
        in

        (* Znajdź i zbuduj ścieżkę do kozła *)
        let path_to_goat = find_path_to_goat new_tree ko in

        Printf.printf "[debug] Ścieżka do kozła: ";
      (* Wyciągamy wartości z krotek i wypisujemy je *)
      List.iter (fun (Node(_, v, _), _, _) -> Printf.printf "%d -> " v) path_to_goat;
      Printf.printf "END\n";  (* Wypisujemy zakończenie ścieżki *)

        let rec plug subtree context =
          match context with
          | [] -> subtree
          | (Node (l, v, r), went_left, _) :: rest -> 
              let new_tree =
                if went_left then 
                  Node (subtree, v, r)  (* Jeśli idziemy w lewo, nowe poddrzewo staje się lewym dzieckiem *)
                else 
                  Node (l, v, subtree)  (* Jeśli idziemy w prawo, nowe poddrzewo staje się prawym dzieckiem *)
              in
              plug new_tree rest  (* Rekurencyjnie wstawiamy do następnego węzła w kontekście *)
        in

        (* Finalnie łączymy wszystkie części *)
        match path_to_goat with 
        | _::rightous_path_to_goat ->
        let final_tree = plug rebuilt_subtree rightous_path_to_goat in

        { tree = final_tree; size = updated_sgt.size; max_size = updated_sgt.max_size }
  end

let remove (x : 'a) (sgt : 'a sgtree) : 'a sgtree =
  let alpha = 0.75 in

  (* Pomocnicza funkcja usuwania z drzewa BST *)
  let rec remove_from_tree x tree =
    match tree with
    | Leaf -> Leaf
    | Node (l, v, r) ->
      if x < v then
        let l' = remove_from_tree x l in
        Node (l', v, r)
      else if x > v then
        let r' = remove_from_tree x r in
        Node (l, v, r')
      else
        (* Znaleziono element do usunięcia *)
        match (l, r) with
        | Leaf, Leaf -> Leaf
        | Leaf, _ -> r
        | _, Leaf -> l
        | _ ->
          (* Zamień z najmniejszym z prawego poddrzewa *)
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

  (* Jeśli drzewo jest puste, nie ma czego usuwać *)
  (*let { tree; size; max_size } = sgt in*)
  let exists = find x sgt in
  if not exists then failwith "x does not exist"
  else
    begin
    let after_remove = remove_from_tree x sgt.tree in
    let after_remove_size = sgt.size - 1 in
    if (float_of_int after_remove_size) < (float_of_int sgt.max_size *. (float_of_int alpha_num /. float_of_int alpha_denom) )
      then let final = rebuild_balanced after_remove in {tree = final; size = after_remove_size; max_size = after_remove_size}
    else {tree = after_remove; size = after_remove_size; max_size = sgt.max_size}
    (* Jeśli rozmiar drzewa jest za mały, to je odbudowujemy z listy *)
    end