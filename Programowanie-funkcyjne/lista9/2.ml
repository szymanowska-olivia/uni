type _ fin_type =
| Empty: empty fin_type
| Unit : unit fin_type
| Bool : bool fin_type
| Pair : 'a fin_type * 'b fin_type -> ('a * 'b) fin_type
| Either : 'a fin_type * 'b fin_type -> ('a,'b) Either.t fin_type
and empty = |

let rec all_values : type a. a fin_type -> a Seq.t =
  fun x ->
    match x with
    | Empty -> Seq.empty
    | Unit -> Seq.cons () Seq.empty 
    | Bool -> Seq.cons true (Seq.cons false Seq.empty)
    | Pair (y, y') ->
        Seq.flat_map (fun x -> Seq.map (fun y -> (x, y)) (all_values y')) (all_values y)
    | Either (l, r) -> Seq.append (Seq.map (fun x -> Either.Left x) (all_values l)) (Seq.map (fun y -> Either.Right y) (all_values r))
let exmpl = List.of_seq (all_values (Pair(Unit, Bool)))
let exmpl' = List.of_seq (all_values (Either(Pair(Bool, Bool), Pair(Unit, Bool))))
let exmpl'' = List.of_seq (all_values (Either(Pair(Bool, Bool), Pair(Empty, Bool))))