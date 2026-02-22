open Syntax

module Env = Map.Make(String)

type env = formula Env.t

let type_error pos msg = raise (Type_error (pos, msg))

let rec type_check_expr (env : env) (e : expr) : formula =
  match e.data with
  | EVar x ->
      (match Env.find_opt x env with
       | Some f -> f
       | None -> type_error e.pos ("Unbound proof variable '" ^ x ^ "'"))
  | ELet (x, e1, e2) ->
      let f1 = type_check_expr env e1 in
      let env' = Env.add x f1 env in
      type_check_expr env' e2
  | EFun (x, f, e_body) ->
      let env' = Env.add x f env in
      let f_body = type_check_expr env' e_body in
      Imp (f, f_body)
  | EApp (e1, e2) ->
      let f1 = type_check_expr env e1 in
      let f2 = type_check_expr env e2 in
      (match f1 with
        | Imp (fa, fb) ->
            if Formula.equal fa f2 then fb
            else
              (match (fa, f2) with
                | Or (f_left, _), Or (f2_left, _) when Formula.equal f_left f2_left -> fb
                | Or (_, f_right), Or (_, f2_right) when Formula.equal f_right f2_right -> fb
                | _ -> type_error e.pos
                         ("Function argument type mismatch: expected " ^ Formula.to_string fa ^
                          ", got " ^ Formula.to_string f2))
        | _ -> type_error e1.pos
                 ("Expected implication type in function position, got " ^ Formula.to_string f1))
  | ETermFun (x, e_body) ->
      let f_body = type_check_expr env e_body in
      Forall (x, f_body)
  | ETermApp (e1, t) ->
      let f1 = type_check_expr env e1 in
      (match f1 with
       | Forall (x, f_body) -> Formula.subst x t f_body
       | _ -> type_error e1.pos
                ("Expected ∀ quantifier in term application, got " ^ Formula.to_string f1))
  | ERelApp (e1, x, f_sub) ->
      let f1 = type_check_expr env e1 in
      (match f1 with
       | ForallRel (r, f_body) -> Formula.subst_rel r (x, f_sub) f_body
       | _ -> type_error e1.pos
                ("Expected ∀Rel quantifier in relational application, got " ^ Formula.to_string f1))
  | EPair (e1, e2) ->
      let f1 = type_check_expr env e1 in
      let f2 = type_check_expr env e2 in
      And (f1, f2)
  | EFst e1 ->
      let f1 = type_check_expr env e1 in
      (match f1 with
       | And (fa, _) -> fa
       | _ -> type_error e1.pos
                ("Expected conjunction type in fst, got " ^ Formula.to_string f1))
  | ESnd e1 ->
      let f1 = type_check_expr env e1 in
      (match f1 with
       | And (_, fb) -> fb
       | _ -> type_error e1.pos
                ("Expected conjunction type in snd, got " ^ Formula.to_string f1))
  | ELeft (e1, f_right) ->
      let f1 = type_check_expr env e1 in
      Or (f1, f_right)
  | ERight (e1, f_left) ->
      let f1 = type_check_expr env e1 in
      Or (f_left, f1)
  | ECase (e0, x1, e1, x2, e2) ->
      let f0 = type_check_expr env e0 in
      (match f0 with
       | Or (f_left, f_right) ->
           let env1 = Env.add x1 f_left env in
           let res1 = type_check_expr env1 e1 in
           let env2 = Env.add x2 f_right env in
           let res2 = type_check_expr env2 e2 in
           if Formula.equal res1 res2 then res1
           else type_error e0.pos
                  ("Branches of case must have the same type: left branch " ^ Formula.to_string res1 ^
                   ", right branch " ^ Formula.to_string res2)
       | _ -> type_error e0.pos
                ("Expected disjunction type in case, got " ^ Formula.to_string f0))
  | EAbsurd (e1, f_goal) ->
      let f1 = type_check_expr env e1 in
      (match f1 with
       | False -> f_goal
       | _ -> type_error e1.pos
                ("Expected ⊥ (False) in absurd, got " ^ Formula.to_string f1))
  | EPack (t, e1, f_goal) ->
      let f1 = type_check_expr env e1 in
      (match f_goal with
       | Exists (x, f_body) ->
           let f_sub = Formula.subst x t f_body in
           if Formula.equal f1 f_sub then f_goal
           else type_error e.pos
                  ("Pack: type mismatch: expected " ^ Formula.to_string f_sub ^ ", got " ^ Formula.to_string f1)
       | _ -> type_error e.pos
                ("Pack: expected ∃ quantifier, got " ^ Formula.to_string f_goal))
  | EUnpack (x, y, e1, e2) ->
      let f1 = type_check_expr env e1 in
      (match f1 with
       | Exists (v, f_body) ->
           let f_sub = Formula.subst v (Var x) f_body in
           let env' = Env.add y f_sub env in
           type_check_expr env' e2
       | _ -> type_error e1.pos
                ("Expected ∃ type in unpack, got " ^ Formula.to_string f1))

let check_def env def =
  match def with
  | Axiom (pos, name, f) ->
      if Env.mem name env then
        type_error pos ("Duplicate axiom name: '" ^ name ^ "'")
      else
        Env.add name f env
  | Theorem (pos, name, f, e) ->
      if Env.mem name env then
        type_error pos ("Duplicate theorem name: '" ^ name ^ "'")
      else
        let f_e = type_check_expr env e in
        if Formula.equal f f_e then
          Env.add name f env
        else
          type_error pos
            ("Theorem proof does not match its statement: expected " ^ Formula.to_string f ^
             ", got " ^ Formula.to_string f_e)

let check_defs defs =
  let _final_env =
    List.fold_left
      (fun env def -> check_def env def)
      Env.empty
      defs
  in
  ()
