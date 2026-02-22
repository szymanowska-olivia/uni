module QBF = struct
type var = string
type formula =
| Var of var (* zmienne zdaniowe *)
| Bot (* spójnik fałszu (⊥) *)
| Not of formula (* negacja (¬φ) *)
| And of formula * formula (* koniunkcja (φ ∧ ψ) *)
| All of var * formula (* kwantyfikacja uniwersalna (∀p.φ) *)

type env = var -> bool
let rec eval (e : env) (f : formula) : bool =
  match f with
  | Var v -> e v
  | Bot -> false
  | Not f' -> not (eval e f')
  | And (g, h) -> (eval e g) && (eval e h)
  | All (v, f') -> (eval (fun x -> if x = v then true else e x) f') && (eval (fun x -> if x = v then false else e x) f')

let is_true (f : formula) : bool = eval (fun _ -> true) f  
let t1 = All ("p", Var "p")

(*(∀p.¬∀q.¬(¬(p ∧ q) ∧ ¬(¬p ∧ ¬q))*)
let t2 = All("p", Not(All("q", Not(And(Not(And(Var "p", Var "q")), Not(And(Not(Var "p"), Not(Var "q"))))))))

end
