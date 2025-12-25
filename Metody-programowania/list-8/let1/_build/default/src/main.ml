open Ast

module Env = Map.Make(String)

let empty_env = Env.empty

let parse (s : string) : expr =
  Parser.main Lexer.read (Lexing.from_string s)


type value =
  | VInt of int
  | VBool of bool

type env = value Env.t

let rec cp (env : expr Env.t) (e : expr) : expr =
  match e with
  | Int _ | Bool _ -> e
  | Var x -> (try Env.find x env with Not_found -> Var x)
  | Binop (op, e1, e2) ->
      let e1' = cp env e1 in
      let e2' = cp env e2 in
      (match e1', e2' with
       | Int a, Int b -> 
        (match op with
        | Add  -> Int (a + b)
        | Sub  -> Int (a - b)
        | Mult -> Int (a * b)
        | Div  -> Int (a / b)
        | Leq  -> Bool (a <= b)
        | Eq   -> Bool (a = b)
        | _    -> failwith "unknown binop")
       | _ -> Binop (op, e1', e2'))
  | If (b, t, e) ->
      let b' = cp env b in
      (match b' with
       | Bool true -> cp env t
       | Bool false -> cp env e
       | _ -> If (b', cp env t, cp env e))
  | Let (x, e1, e2) ->
      let e1' = cp env e1 in
      (match e1' with
       | Int _ | Bool _ ->
           let env' = Env.add x e1' env in
           cp env' e2
       | _ ->
           let env' = Env.add x (Var x) env in
           Let (x, e1', cp env' e2))


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



  let interp (s : string) : value =
    let e = parse s in                  
    let simplified = cp Env.empty e in  
    eval simplified      

