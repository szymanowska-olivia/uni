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

let rec typecheck_and_simplify (env : Env.t) (e : expr) : typ * Ast.expr =
  match e.data with
  | Unit -> (TUnit, Unit)
  | Int n -> (TInt, Int n)
  | Bool b -> (TBool, Bool b)
  | Var x ->
    begin match Env.lookup_var env x with
    | Some tp -> (tp, Var x)
    | None -> raise (Type_error(e.pos, Printf.sprintf "Unbound variable %s" x))
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
  | Let(x, e1, e2) ->
    let (t1, e1') = typecheck_and_simplify env e1 in
    let (t2, e2') = typecheck_and_simplify (Env.add_var env x t1) e2 in
    (t2, Let(x, e1', e2'))
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
  | Fun(x, tx, e) ->
    let env' = Env.add_var env x tx in
    let (ty, e') = typecheck_and_simplify env' e in
    (TArrow(tx, ty), Fun(x, e'))
  | Funrec(f, x, tx, ty, e) ->
    let env' = env |> Env.add_var x tx |> Env.add_var f (TArrow(tx, ty)) in
    let (_, e') = typecheck_and_simplify env' e in
    (TArrow(tx, ty), Funrec(f, x, e'))

let typecheck_program e =
  let _, simplified = typecheck_and_simplify Env.initial e in
  simplified