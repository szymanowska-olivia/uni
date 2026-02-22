open Ast

module Env = Map.Make(String)

let empty_env = Env.empty

let parse (s : string) : expr =
  Parser.main Lexer.read (Lexing.from_string s)


type value =
  | VInt of int
  | VBool of bool

type env = value Env.t

let eval_op (op : bop) (val1 : value) (val2 : value) : value =
  match op, val1, val2 with
  | Add,  VInt  v1, VInt  v2 -> VInt  (v1 + v2)
  | Sub,  VInt  v1, VInt  v2 -> VInt  (v1 - v2)
  | Mult, VInt  v1, VInt  v2 -> VInt  (v1 * v2)
  | Div,  VInt  v1, VInt  v2 -> VInt  (v1 / v2)
  | And,  VBool v1, VBool v2 -> VBool (v1 && v2)
  | Or,   VBool v1, VBool v2 -> VBool (v1 || v2)
  | Leq,  VInt  v1, VInt  v2 -> VBool (v1 <= v2)
  | Eq,   _,        _        -> VBool (val1 = val2)
  | _,    _,        _        -> failwith "type error"

let rec subst (x : ident) (s : expr) (e : expr) : expr =
  match e with
  | Binop (op, e1, e2) -> Binop (op, subst x s e1, subst x s e2)
  | If (b, t, e) -> If (subst x s b, subst x s t, subst x s e)
  | Var y -> if x = y then s else e
  | Let (y, e1, e2) ->
      Let (y, subst x s e1, if x = y then e2 else subst x s e2)
  | _ -> e

let reify (v : value) : expr =
  match v with
  | VInt a -> Int a
  | VBool b -> Bool b

  let rec eval (e : expr) : value =
    match e with
    | Int i -> VInt i
    | Bool b -> VBool b
    | Binop (op, e1, e2) ->
        eval_op op (eval e1) (eval e2)
    | If (b, t, e) ->
        (match eval b with
             | VBool true -> eval t
             | VBool false -> eval e
             | _ -> failwith "type error")
    | Let (x, e1, e2) ->
        eval (subst x (reify (eval e1)) e2)
    | Var x -> failwith ("unknown var " ^ x)

let rec alpha_eq e1 e2 env1 env2 =
  match e1, e2 with
  | Int n1, Int n2 -> n1 = n2
  | Bool b1, Bool b2 -> b1 = b2
  | Var x1, Var x2 ->
      (match Env.find_opt x1 env1, Env.find_opt x2 env2 with
       | Some y1, Some y2 -> x2 = y1 && x1 = y2
       | None, None -> x1 = x2
       | _, _ -> false)

  | Binop (op1, a1, b1), Binop (op2, a2, b2) ->
      op1 = op2 &&
      alpha_eq a1 a2 env1 env2 &&
      alpha_eq b1 b2 env1 env2

  | If (b1, t1, e1), If (b2, t2, e2) ->
      alpha_eq b1 b2 env1 env2 &&
      alpha_eq t1 t2 env1 env2 &&
      alpha_eq e1 e2 env1 env2

  | Let (x1, e1l, e1r), Let (x2, e2l, e2r) ->
      alpha_eq e1l e2l env1 env2 &&
      let env1' = Env.add x1 x2 env1 in
      let env2' = Env.add x2 x1 env2 in
      alpha_eq e1r e2r env1' env2'

  | _, _ -> false

let string_of_e e : string = 
  match e with 
  | Int i -> string_of_int i
  | Bool b -> string_of_bool b 
  | _ -> failwith "unknown type"
  
  let rename_expr (e : expr) : expr =
    let rec it (e : expr) (env : expr Env.t) (path : string) : expr =
      match e with
      | Int _ -> e
      | Bool _ -> e
      | Var x -> 
          (match Env.find_opt x env with
           | Some (Var y) -> Var y
           | _ -> Var x)
      | Binop (op, e1, e2) ->
          Binop (op, it e1 env (path ^ "L"), it e2 env (path ^ "R"))
      | If (b, t, f) ->
          If (it b env (path ^ "W"), it t env (path ^ "T"), it f env (path ^ "F"))
      | Let (x, e1, e2) ->
          let new_var = "#" ^ path in
          let env' = Env.add x (Var new_var) env in
          let e1' = it e1 env (path ^ "L") in
          let e2' = it e2 env' (path ^ "R") in
          Let (new_var, e1', e2')
    in
    it e Env.empty ""
  
let interp (s : string) : value =
  eval (parse s)

