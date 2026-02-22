type bop =
  (* arithmetic *)
  | Add | Sub | Mult | Div
  (* logic *)
  | And | Or
  (* comparison *)
  | Eq | Neq | Leq | Lt | Geq | Gt

type ident = string

type expr =
  | Int    of int
  | Binop  of bop * expr * expr
  | Bool   of bool
  | If     of expr * expr * expr
  | Let    of ident * expr * expr
  | Var    of ident
  | Cell   of int * int
  | Unit
  | Pair   of expr * expr
  | Fst    of expr
  | Snd    of expr
  | Match  of expr * ident * ident * expr
  | IsPair of expr
  | Fun    of ident * expr
  | Funrec of ident * ident * expr
  | App    of expr * expr

exception Unknown_cell 
exception Circular_dependency 

module M = Map.Make(String)

type env = value M.t

and value =
  | VInt of int
  | VBool of bool
  | VUnit
  | VPair of value * value
  | VClosure of ident * expr * env
  | VRecClosure of ident * ident * expr * env

module IntPair = struct
  type t = int * int
  let compare = compare
end

module C = Map.Make(IntPair)

type cenv = value C.t 

let eval_op (op : bop) (val1 : value) (val2 : value) : value =
  match op, val1, val2 with
  | Add,  VInt  v1, VInt  v2 -> VInt  (v1 + v2)
  | Sub,  VInt  v1, VInt  v2 -> VInt  (v1 - v2)
  | Mult, VInt  v1, VInt  v2 -> VInt  (v1 * v2)
  | Div,  VInt  v1, VInt  v2 -> VInt  (v1 / v2)
  | And,  VBool v1, VBool v2 -> VBool (v1 && v2)
  | Or,   VBool v1, VBool v2 -> VBool (v1 || v2)
  | Leq,  VInt  v1, VInt  v2 -> VBool (v1 <= v2)
  | Lt,   VInt  v1, VInt  v2 -> VBool (v1 < v2)
  | Gt,   VInt  v1, VInt  v2 -> VBool (v1 > v2)
  | Geq,  VInt  v1, VInt  v2 -> VBool (v1 >= v2)
  | Neq,  _,        _        -> VBool (val1 <> val2)
  | Eq,   _,        _        -> VBool (val1 = val2)
  | _,    _,        _        -> failwith "type error"

let rec eval_env (sheet : expr list list) (cenv : cenv ref) (visited : IntPair.t list) (env : env) (pos_opt : IntPair.t option) (e : expr) : value =
  match e with
  | Int i -> VInt i
  | Bool b -> VBool b
  | Binop (op, e1, e2) ->
      eval_op op (eval_env sheet cenv visited env pos_opt e1) (eval_env sheet cenv visited env pos_opt e2)
  | If (b, t, e) ->
      (match (eval_env sheet cenv visited env pos_opt b) with
       | VBool true -> eval_env sheet cenv visited env pos_opt t
       | VBool false -> eval_env sheet cenv visited env pos_opt e
       | _ -> failwith "type error")
  | Var x ->
      (match M.find_opt x env with
       | Some v -> v
       | None -> failwith "unknown var")
  | Let (x, e1, e2) ->
      let v1 = eval_env sheet cenv visited env pos_opt e1 in
      let env' = M.add x v1 env in
      eval_env sheet cenv visited env' pos_opt e2
  | Pair (e1, e2) ->
      VPair (eval_env sheet cenv visited env pos_opt e1, eval_env sheet cenv visited env pos_opt e2)
  | Unit -> VUnit
  | Fst e ->
      (match eval_env sheet cenv visited env pos_opt e with
       | VPair (v1, _) -> v1
       | _ -> failwith "type error")
  | Snd e ->
      (match eval_env sheet cenv visited env pos_opt e with
       | VPair (_, v2) -> v2
       | _ -> failwith "type error")
  | IsPair e ->
      (match eval_env sheet cenv visited env pos_opt e with
       | VPair _ -> VBool true
       | _ -> VBool false)
  | Fun (x, e) -> VClosure (x, e, env)
  | Funrec (f, x, e) -> VRecClosure (f, x, e, env)
  | App (e1, e2) ->
      let v1 = eval_env sheet cenv visited env pos_opt e1 in
      let v2 = eval_env sheet cenv visited env pos_opt e2 in
      (match v1 with
       | VClosure (x, body, clo_env) ->
           eval_env sheet cenv visited (M.add x v2 clo_env) pos_opt body
       | VRecClosure (f, x, body, clo_env) as c ->
           let env' = clo_env |> M.add x v2 |> M.add f c in
           eval_env sheet cenv visited env' pos_opt body
       | _ -> failwith "not a function")
  | Cell (r, c) ->
      let pos = (r, c) in
      if List.mem pos visited then
        raise Circular_dependency
      else
        (match C.find_opt pos !cenv with
         | Some v -> v
         | None ->
           let expr_opt =
             try Some (List.nth (List.nth sheet r) c)
             with _ -> None
           in
           (match expr_opt with
            | None -> raise (Unknown_cell)
            | Some expr ->
              let v = eval_env sheet cenv (pos :: visited) env (Some pos) expr in
              cenv := C.add pos v !cenv;
              v))
  | Match _ -> failwith "Not implemented"

let eval_spreadsheet (s : expr list list) : value list list option =
  let cenv = ref C.empty in
  try
    Some (List.mapi (fun r row ->
         List.mapi (fun c _expr -> 
          eval_env s cenv [] M.empty (Some (r,c)) (List.nth (List.nth s r) c)) row) s)
  with
  | Circular_dependency -> None
  | Unknown_cell -> None

