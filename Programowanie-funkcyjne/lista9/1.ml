type _ fin_type =
| Unit : unit fin_type
| Bool : bool fin_type
| Pair : 'a fin_type * 'b fin_type -> ('a * 'b) fin_type

let rec all_values : type a. a fin_type -> a Seq.t =
  fun x ->
    match x with
    | Unit -> Seq.cons () Seq.empty 
    | Bool -> Seq.cons true (Seq.cons false Seq.empty)
    | Pair (y, y') ->
        Seq.flat_map (fun x -> Seq.map (fun y -> (x, y)) (all_values y')) (all_values y)

let exmpl = List.of_seq (all_values (Pair(Unit, Bool)));;