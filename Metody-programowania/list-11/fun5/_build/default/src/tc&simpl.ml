open RawAst

exception Type_error of
  (Lexing.position * Lexing.position) * string

let binop_name (bop : bop) =
  match bop with
  | Add  -> "add"
  | Sub  -> "sub"
  | Mult -> "mult"
  | Div  -> "div"
  | And  -> "and"
  | Or   -> "or"
  | Eq   -> "eq"
  | Neq  -> "neq"
  | Leq  -> "leq"
  | Lt   -> "lt"
  | Geq  -> "geq"
  | Gt   -> "gt"

module Env = struct
  module StrMap = Map.Make(String)
  type t = typ StrMap.t

  let initial = StrMap.empty

  let add_var env x tp =
    StrMap.add x tp env

  let lookup_var env x =
    StrMap.find_opt x env
end

module VarMap = struct
  module M = Map.Make(String)

  let var_id_counter = ref 0
  let env_var_to_int = ref M.empty

  let get_var_id (x : string) : int =
    match M.find_opt x !env_var_to_int with
    | Some id -> id
    | None ->
      let id = !var_id_counter in
      var_id_counter := id + 1;
      env_var_to_int := M.add x id !env_var_to_int;
      id
end

let rec typecheck_and_simplify (env : Env.t) (e : expr) : typ * expr =
  match e.data with
  | Unit -> (TUnit, Unit)
  | Int n -> (TInt, Int n)
  | Bool b -> (TBool, Bool b)
  | Var x_str -> 
    begin match Env.lookup_var env x_str with
    | Some tp ->
      let id = VarMap.get_var_id x_str in
      (tp, Var id)
    | None -> raise (Type_error(e.pos, Printf.sprintf "Unbound variable %s" x_str))
    end
  | Binop(bop, e1, e2) ->
    let (t1, e1') = typecheck_and_simplify env e1 in
    let (t2, e2') = typecheck_and_simplify env e2 in
    let expected_type, result_type =
      match bop with
      | Add | Sub | Mult | Div -> (TInt, TInt)
      | And | Or -> (TBool, TBool)
      | Leq | Lt | Geq | Gt -> (TInt, TBool)
      | Eq | Neq -> (t1, TBool)
    in
    if t1 <> expected_type || t2 <> expected_type then
      raise (Type_error(e.pos, "Type error in binary operation"));
    let op = Builtin (binop_name bop) in
    (result_type, App(App(op, e1'), e2'))
  | If (b, e1, e2) ->
    let (tb, b') = typecheck_and_simplify env b in
    if tb <> TBool then raise (Type_error(e.pos, "Condition must be boolean"));
    let (t1, e1') = typecheck_and_simplify env e1 in
    let (t2, e2') = typecheck_and_simplify env e2 in
    if t1 <> t2 then raise (Type_error(e.pos, "Branches must have same type"));
    (t1, If(b', e1', e2'))
  | Let(x_str, e1, e2) ->
    let (t1, e1') = typecheck_and_simplify env e1 in
    let env' = Env.add_var env x_str t1 in
    let (t2, e2') = typecheck_and_simplify env' e2 in
    let id = VarMap.get_var_id x_str in
    (t2, Let(id, e1', e2'))
  | Pair(e1, e2) ->
    let (t1, e1') = typecheck_and_simplify env e1 in
    let (t2, e2') = typecheck_and_simplify env e2 in
    (TPair(t1, t2), Pair(e1', e2'))
  | App(e1, e2) ->
    let (tf, e1') = typecheck_and_simplify env e1 in
    let (ta, e2') = typecheck_and_simplify env e2 in
    begin match tf with
    | TArrow(targ, tret) ->
      if targ <> ta then raise (Type_error(e.pos, "Function argument type mismatch"));
      (tret, App(e1', e2'))
    | _ -> raise (Type_error(e.pos, "Attempt to apply non-function"))
    end
  | Fst e ->
    let (tp, e') = typecheck_and_simplify env e in
    begin match tp with
    | TPair(t1, _) -> (t1, App(Builtin "fst", e'))
    | _ -> raise (Type_error(e.pos, "Expected pair for fst"))
    end
  | Snd e ->
    let (tp, e') = typecheck_and_simplify env e in
    begin match tp with
    | TPair(_, t2) -> (t2, App(Builtin "snd", e'))
    | _ -> raise (Type_error(e.pos, "Expected pair for snd"))
    end
  | Fun(x_str, tx, e) ->
    let env' = Env.add_var env x_str tx in
    let (ty, e') = typecheck_and_simplify env' e in
    let id = VarMap.get_var_id x_str in
    (TArrow(tx, ty), Fun(id, tx, e'))
  | Funrec(f_str, x_str, tx, ty, e) ->
    let env' = env |> Env.add_var x_str tx |> Env.add_var f_str (TArrow(tx, ty)) in
    let (_, e') = typecheck_and_simplify env' e in
    let f_id = VarMap.get_var_id f_str in
    let x_id = VarMap.get_var_id x_str in
    (TArrow(tx, ty), Funrec(f_id, x_id, tx, ty, e'))

let typecheck_program e =
  let _, simplified = typecheck_and_simplify Env.initial e in
  simplified