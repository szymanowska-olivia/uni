type stack_elem =
  | Value of int
  | Pending of Ast.bop * int list

let emit_bop (op : Ast.bop) : string =
  Ast.(
    match op with
    | Add  -> "+"
    | Sub  -> "-"
    | Mult -> "*"
    | Div  -> "/"
    | _ -> failwith "not implemented"
  )

let rec to_prefix (expr : Ast.expr) : string =
  match expr with
  | Ast.Int n -> string_of_int n
  | Ast.Binop (op, e1, e2) ->
      let op_str = emit_bop op in
      let left = to_prefix e1 in
      let right = to_prefix e2 in
      op_str ^ " " ^ left ^ " " ^ right
  | _ -> failwith "not implemented"

let eval_op (op : Ast.bop) (val1 : int) (val2 : int) : int =
  match op with
  | Ast.Add  -> val1 + val2
  | Ast.Sub  -> val1 - val2
  | Ast.Mult -> val1 * val2
  | Ast.Div  -> val1 / val2
  | _        -> failwith "operator not implemented"

let to_bop (s : string) : Ast.bop =
  match s with
  | "+" -> Ast.Add
  | "-" -> Ast.Sub
  | "*" -> Ast.Mult
  | "/" -> Ast.Div
  | _   -> failwith ("unknown operator: " ^ s)

let rec process_stack stack =
  match stack with
  | Value n :: Pending (op, [a]) :: rest ->
      let res = eval_op op a n in
      process_stack (Value res :: rest)
  | Value n :: Pending (op, args) :: rest ->
      Pending (op, args @ [n]) :: rest
  | _ -> stack

let rec eval tokens stack =
  match tokens with
  | [] ->
      (match stack with
       | [Value n] -> n
       | _ -> failwith "invalid expression")
  | hd :: tl ->
      let stack' =
        if List.mem hd ["+"; "-"; "*"; "/"] then
          Pending (to_bop hd, []) :: stack
        else
          let n = int_of_string hd in
          let stack_with_value = Value n :: stack in
          process_stack stack_with_value
      in
      eval tl stack'

let compile (s : string) : string =
  s
  |> Interp.parse
  |> to_prefix


let compile_and_eval (s : string) : int =
  let prefix_str = s |> Interp.parse |> to_prefix in    (* krok 1 i 2 *)
  let tokens = String.split_on_char ' ' prefix_str in   (* krok 3 *)
  eval tokens []                                        (* krok 4 *)
