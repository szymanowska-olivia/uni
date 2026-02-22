module SBT(State : sig type t end) : sig
type 'a t
val return : 'a -> 'a t
val bind : 'a t -> ('a -> 'b t) -> 'b t
val fail : 'a t
val flip : bool t
val get : State.t t
val put : State.t -> unit t
val run : State.t -> 'a t -> 'a Seq.t
end = struct
  type 'a t = State.t -> ('a * State.t) Seq.t

  let return x = fun s -> Seq.return (x, s)

  let bind m f = fun s ->
    Seq.flat_map (fun (x, s') -> f x s') (m s)

  let fail = fun _ -> Seq.empty

  let flip = fun s -> List.to_seq [(true, s); (false, s)]

  let get = fun s -> Seq.return (s, s)

  let put s' = fun _ -> Seq.return ((), s')

  let run s m = Seq.map fst (m s)
end

open SBT 

type 'a regexp =
| Eps
| Lit of ('a -> bool)
| Or of 'a regexp * 'a regexp
| Cat of 'a regexp * 'a regexp
| Star of 'a regexp


let rec match_regexp (r : 'a regexp) : ('a list option) SBT.t =
  match r with
  | Eps -> return None

  | Lit f ->
      bind get (fun input ->
      match input with
      | [] -> fail
      | x::xs ->
          if f x then
            bind (put xs) (fun _ -> return (Some xs))
          else
            fail )

  | Or (r1, r2) ->
      bind flip (fun b -> if b then match_regexp r1 else match_regexp r2)

  | Cat (r1, r2) ->
      bind (match_regexp r1) (fun y ->
      match y with
      | Some _ -> match_regexp r2
      | None -> fail)

  | Star reg ->
      bind (match_regexp reg) (fun y ->
      match y with
      | Some xs ->
          (* kontynuujemy tylko gdy faktycznie konsumujemy *)
          (match xs with
          | [] -> return (Some [])
          | _ -> match_regexp (Star reg))
      | None ->
          (* nie pasujemy nic – OK *)
          bind get (fun s -> return (Some s)))
