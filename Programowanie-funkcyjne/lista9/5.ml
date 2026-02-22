type empty = |
let absurd (x : empty) = match x with _ -> .

module NestedQBF = struct
  type 'v inc = Z | S of 'v

  type 'v formula =
    | Var of 'v
    | Bot
    | Not of 'v formula
    | And of 'v formula * 'v formula
    | All of ('v inc) formula

  type 'v env = 'v -> bool

  let extend_env (e : 'v env) (b : bool) : ('v inc) env =
    function
    | Z -> b
    | S v -> e v

  let rec eval : type v. v env -> v formula -> bool =
    fun (e : v env) (f : v formula) ->
      match f with
      | Var v -> e v
      | Bot -> false
      | Not g -> not (eval e g)
      | And (g, h) -> (eval e g) && (eval e h)
      | All g ->
          let e_true  = extend_env e true in
          let e_false = extend_env e false in
          (eval e_true g) && (eval e_false g)

  let is_true (f : empty formula) : bool = eval absurd f
end
