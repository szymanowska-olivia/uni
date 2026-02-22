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

let rec alpha_equiv e1 e2 env1 env2 =
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
      alpha_equiv a1 a2 env1 env2 &&
      alpha_equiv b1 b2 env1 env2

  | If (b1, t1, e1), If (b2, t2, e2) ->
      alpha_equiv b1 b2 env1 env2 &&
      alpha_equiv t1 t2 env1 env2 &&
      alpha_equiv e1 e2 env1 env2

  | Let (x1, e1l, e1r), Let (x2, e2l, e2r) ->
      alpha_equiv e1l e2l env1 env2 &&
      let env1' = Env.add x1 x2 env1 in
      let env2' = Env.add x2 x1 env2 in
      alpha_equiv e1r e2r env1' env2'

  | _, _ -> false


  let interp (s : string) : value =
    eval (parse s)      

