module type RandomMonad = sig
  type 'a t
  val return : 'a -> 'a t
  val bind : 'a t -> ('a -> 'b t) -> 'b t
  val random : int t

end

module Shuffle(R : RandomMonad) : sig
  
  val shuffle : 'a list -> 'a list R.t
end = struct
  let (let*) = R.bind
  let shuffle xs =
    let rec it xs =
    match xs with
    | [] -> R.return []
    | x::xs' -> let* ys = (it xs') in (let* t = R.random in (R.return ((t, x)::ys)))
    in let* ys = (it xs) in (R.return(List.map snd (List.sort compare ys)))
end

module RS : sig 
  include RandomMonad
  val run : int -> 'a t -> 'a 

end = struct
  type 'a t = int -> 'a * int

  let return ( x : 'a) : 'a t = fun seed -> (x, seed)
  let bind  (m : 'a t) (f : 'a -> 'b t) = 
    fun seed -> let (res, seed') =  m seed  in f res seed'
  let random (seed : int) = 
    let b = 16807 * (seed mod 127773) - 2836 * (seed / 127773) in 
    if b > 0 then (b, b) else (b, b + 2147483647)

  let run (seed : int) (x : 'a t) = fst (x seed)
end
