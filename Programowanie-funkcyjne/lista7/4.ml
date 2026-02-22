module type Monad = sig
type 'a t
val return : 'a -> 'a t
val bind : 'a t -> ('a -> 'b t) -> 'b t
end 

module M : Monad = struct
  type 'r ans 
  type 'a t = { run : 'r. ('a -> 'r ans) -> 'r ans }
  let return (x : 'a) : 'a t = { run = fun k -> k x }

  let bind (m : 'a t) (f : 'a -> 'b t) : 'b t = { run = fun k -> m.run (fun x -> (f x).run k)}

end

module Err : sig
include Monad
val fail : 'a t
val catch : 'a t -> (unit -> 'a t) -> 'a t
val run : 'a t -> 'a option
end = struct
  type 'r ans = 'r option
  type 'a t = { run : 'r. ('a -> 'r ans) -> 'r ans }

  let return (x : 'a) : 'a t = { run = fun k -> k x }
  let bind (m : 'a t) (f : 'a -> 'b t) : 'b t = { run = fun k -> m.run (fun x -> (f x).run k)}

  let fail : 'a t = {run = fun k -> None}

  let catch (m : 'a t) (a : unit -> 'a t) : 'a t = 
    { run = fun k -> let it = m.run k in 
                      match it with
                      | Some x -> Some x
                      | None -> (a ()).run k}
  let run (m : 'a t) : 'a option = m.run (fun x -> Some x)
end

(*let t5 = catch fail (fun () -> return 42)*)

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

(*let choose x = BT.bind BT.flip (fun sign -> if sign then BT.return (x + 1) else BT.return (x - 1));;*)
(*List.of_seq (BT.run (choose 10));;*)

module St(State : sig type t end) : sig
include Monad
val get : State.t t
val set : State.t -> unit t
val run : State.t -> 'a t -> 'a
end = struct

  type 'r ans = State.t -> 'r * State.t
  type 'a t = { run : 'r. ('a -> 'r ans) -> 'r ans }
  let return (x : 'a) : 'a t = { run = fun k -> k x }

  let bind (m : 'a t) (f : 'a -> 'b t) : 'b t = { run = fun k -> m.run (fun x -> (f x).run k)}

  let get = { run = fun k s -> k s s }
  let set n = {run = fun k s -> k () n }
  let run n m = fst (m.run (fun x s -> (x, s)) n)
  
end

module S = St(struct type t = int end);;

(*let t4 =
  S.bind S.get (fun s ->
  S.bind (S.set (s + 10)) (fun () ->
  S.bind S.get (fun s2 ->
  S.return (s, s2))));;
  
  S.run 1 t4;;*)