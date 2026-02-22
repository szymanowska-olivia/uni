
module type Monad = sig
type 'a t
val return : 'a -> 'a t
val bind : 'a t -> ('a -> 'b t) -> 'b t
end 

module BT : sig
include Monad
val fail : 'a t
val flip : bool t
val run : 'a t -> 'a Seq.t
end = struct

  type 'r ans = 'r Seq.t
  type 'a t = { run : 'r. ('a -> 'r ans) -> 'r ans }
  let return (x : 'a) : 'a t = { run = fun k -> k x }

  let bind (m : 'a t) (f : 'a -> 'b t) : 'b t = { run = fun k -> m.run (fun x -> (f x).run k)}

  let fail : 'a t = {run = fun k -> Seq.empty}
  
  let flip = { run = fun k -> Seq.append (k true) (k false)}
  let run (m : 'a t) : 'a Seq.t = m.run (fun x -> List.to_seq [x])

end

open BT 

type 'a regexp =
| Eps
| Lit of ('a -> bool)
| Or of 'a regexp * 'a regexp
| Cat of 'a regexp * 'a regexp
| Star of 'a regexp

let rec match_regexp (r : 'a regexp) (input : 'a list) : ('a list) option BT.t =
  match r with
  | Eps -> BT.return None
  | Lit f -> 
    begin
    match input with
    | [] -> BT.fail
    | x::xs -> if f x then BT.return (Some xs) else BT.fail
    end
  | Or (r1, r2) ->
      BT.bind BT.flip 
      (fun b -> if b then match_regexp r1 input else match_regexp r2 input)  
  | Cat (r1, r2) -> BT.bind (match_regexp r1 input) (fun y -> match y with 
                                                             | Some xs -> match_regexp r2 xs 
                                                             | None -> BT.fail)
  | Star reg -> 
  BT.bind (match_regexp reg input) (fun y -> match y with 
                                            | Some xs -> 
                                              begin
                                                match xs with 
                                                | [] -> BT.return (Some [])
                                                | _ -> match_regexp (Star reg) xs
                                              end
                                            | None -> BT.return (Some input))