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
