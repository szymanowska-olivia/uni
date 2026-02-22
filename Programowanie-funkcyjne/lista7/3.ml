module IM : sig
  type 'a t
  val return : 'a -> 'a t
  val bind : 'a t -> ('a -> 'b t) -> 'b t

end = struct
  type 'a t = 'a

  let return x = x

  let bind x f = f x
end

module IC : sig
  type 'a t
  val return : 'a -> 'a t
  val bind : 'a t -> ('a -> 'b t) -> 'b t

end = struct
  type 'a t = unit -> 'a

  let return x = fun () -> x

  let bind (m : 'a t) (f : 'a -> 'b t) : 'b t = fun () -> f (m ()) ()
  
end