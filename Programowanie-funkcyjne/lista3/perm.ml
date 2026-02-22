module type OrderedType = sig
type t
val compare : t -> t -> int
end

module Make (Key : OrderedType) = struct
  module Map = Map.Make(Key)

  type key = Key.t
  type t = key Map.t * key Map.t

  let apply ((f, _) : t) x= 
    match Map.find_opt x f with
    | Some y -> y
    | None -> x

  let id : t = (Map.empty, Map.empty)
  let invert ((f, f') : t) : t = (f', f)

  let swap (x : key) (y : key) : t = 
    let (f, f') = id in (Map.add x y f, Map.add y x f') 

  let compose (f1, f1_inv) (f2, f2_inv) =
  let f = Map.merge (fun k _ _ ->
    let x = apply (f2, f2_inv) k in   
    let y = apply (f1, f1_inv) x in   
    if Key.compare k y = 0 then None   
    else Some y
  ) f1 f2 in
  let f_inv = Map.merge (fun k _ _ ->
    let x = apply (f1_inv, f1) k in   
    let y = apply (f2_inv, f2) x in   
    if Key.compare k y = 0 then None
    else Some y
  ) f1_inv f2_inv in
  (f, f_inv)
   
  let compare (f1, _) (f2, _) =
  Map.compare Key.compare f1 f2

  
end