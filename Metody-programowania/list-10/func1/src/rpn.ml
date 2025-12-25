let emit_bop (op : Ast.bop) : string =
  Ast.(match op with
  | Add  -> "+"
  | Sub  -> "-"
  | Mult -> "*"
  | Div  -> "/"
  | _ -> failwith "not implemented")

let rec to_prefix (expr : Ast.expr) : string =
  match expr with
  | Ast.Int n -> string_of_int n
  | Ast.Binop (op, e1, e2) ->
      let op_str = emit_bop op in
      let left = to_prefix e1 in
      let right = to_prefix e2 in
      op_str ^ " " ^ left ^ " " ^ right
  | _ -> failwith "not implemented"

let compile (s : string) : string =
  s
  |> Interp.parse
  |> to_prefix

