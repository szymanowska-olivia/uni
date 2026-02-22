open Ast

let parse (s : string) : expr =
  Parser.main Lexer.read (Lexing.from_string s)

type value =
  | VInt of int
  | VBool of bool
  | VUnit
  | VPair of value * value

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
  | MatchPair (e1, x1, x2, e2) -> 
      MatchPair (Pair (subst x s e1, if x = x1 then e2 else subst x s e2), x1, x2, Pair (subst x s e1, if x = x2 then e2 else subst x s e2))
  | Sum (y, e1, e2, body) ->
      Sum (y, subst x s e1, subst x s e2, if x = y then body else subst x s body)
  | _ -> e

let rec reify (v : value) : expr =
  match v with
  | VInt a -> Int a
  | VBool b -> Bool b
  | VUnit -> Unit
  | VPair (v1, v2) -> Pair (reify v1, reify v2)

let rec eval (e : expr) : value =
  match e with
  | Int i -> VInt i
  | Unit -> VUnit
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
  | Pair (e1, e2) -> VPair (eval e1, eval e2)
  | MatchPair (e, x, y, body) ->
    (match eval e with
     | VPair (v1, v2) ->
         eval (subst x (reify v1) (subst y (reify v2) body))
     | _ -> failwith "type error") 
  | Sum (x, e1, e2, body) ->
    let v1 = eval e1 in
    let v2 = eval e2 in
    (match v1, v2 with
     | VInt n, VInt m ->
         let rec loop i acc =
           if i > m then acc
           else
             match eval (subst x (Int i) body) with
             | VInt v -> loop (i + 1) (acc + v)
             | _ -> failwith "type error"
         in
         VInt (loop n 0)
     | _ -> failwith "type error")


let interp (s : string) : value =
  eval (parse s)
