type ty_name = string
type ctor_name = string
type ctor = Ctor of ctor_name * ty_name list
type ty_def = ty_name * ctor list

let print_induction_rule (ty : ty_def) : unit =
  let (ty_name, ctors) = ty in
  Printf.printf "Aby dowieść ∀x:%s. P(x), wystarczy pokazać:\n\n" ty_name;
  List.iter (fun (Ctor (ctor_name, args)) ->
    let args_with_names =
      List.mapi (fun i arg_ty -> (arg_ty, "x" ^ string_of_int i)) args
    in
    let hyp =
      args_with_names
      |> List.filter (fun (arg_ty, _) -> arg_ty = ty_name) (*czy rek*)
      |> List.map (fun (_, var_name) -> "P(" ^ var_name ^ ")")
    in

    let ctor_expr =
      match args_with_names with
      | [] -> ctor_name
      | _ ->
        let vars = List.map snd args_with_names in
        Printf.sprintf "%s(%s)" ctor_name (String.concat ", " vars)
    in

    match hyp with
    | [] ->
        Printf.printf "- P(%s) zachodzi.\n" ctor_expr
    | _ ->
        Printf.printf "- Jeśli %s, to P(%s) zachodzi.\n"
          (String.concat " i " hyp) ctor_expr
  ) ctors

  let perm_type : ty_def = (
  "Perm",
  [
    Ctor ("perm_nil", []);
    Ctor ("perm_cons", ["A"; "list"; "list"; "Perm"]);
    Ctor ("perm_swap", ["A"; "A"; "list"]);
    Ctor ("perm_trans", ["list"; "list"; "list"; "Perm"; "Perm"])
  ]
)