module TermMonad = struct
type symbol = string
type 'v term =
| Var of 'v
| Sym of symbol * 'v term list

let return (x : 'v) : 'v term = Var x

let rec bind (m : 'v term) (f : 'v -> 'u term) : 'u term = 
  match m with
  | Var v -> f v
  | Sym (s, xv) -> Sym (s, List.map (fun v -> bind v f) xv)

let rec map_tree m f =
  match m with
  | Var v -> Var (f v)
  | Sym (s, xv) -> Sym (s, List.map (fun x -> map_tree x f) xv)


end

