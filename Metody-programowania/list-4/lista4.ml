(*zadanie 1*)

module type DICT = sig
  type ('a , 'b ) dict
  val empty : ('a , 'b ) dict
  val insert : 'a -> 'b -> ('a , 'b ) dict -> ('a , 'b ) dict
  val remove : 'a -> ('a , 'b ) dict -> ('a , 'b ) dict
  val find_opt : 'a -> ('a , 'b ) dict -> 'b option
  val find : 'a -> ('a , 'b ) dict -> 'b
  val to_list : ('a , 'b ) dict -> ('a * 'b ) list
  end

  module ListDict : DICT = struct
    type ('a, 'b) dict = ('a * 'b) list
    let empty = []
    let insert key value dict =
      (key, value) :: List.remove_assoc key dict
    let remove key dict = List.remove_assoc key dict

    let find_opt key dict =
      try Some (List.assoc key dict) with Not_found -> None
    
    let find key dict = List.assoc key dict
    
    let to_list dict = dict

  end

  (*zadanie 2*)

  module type KDICT = sig
    type key               
    type 'a dict            
  
    val empty : 'a dict
    val insert : key -> 'a -> 'a dict -> 'a dict
    val remove : key -> 'a dict -> 'a dict
    val find_opt : key -> 'a dict -> 'a option
    val find : key -> 'a dict -> 'a
    val to_list : 'a dict -> (key * 'a) list
  end

  (*zadanie 3*)

module MakeListDict (Ord : Map.OrderedType)
: KDICT = struct

type key = Ord.t
type 'a dict = (key * 'a) list

let empty = []

let insert k v d =
  (k, v) :: List.remove_assoc k d

let remove k d =
  List.remove_assoc k d

let find_opt k d =
  try Some (List.assoc k d) with Not_found -> None

let find k d =
  List.assoc k d

let to_list d = d
end


module CharOrdered : Map.OrderedType = struct
type t = char
let compare = Char.compare
end


module CharListDict = MakeListDict(CharOrdered)



(*poprawiona wersjqa MakeListDist*)
module MakeListDict (Ord : Map.OrderedType)
: KDICT with type key = Ord.t = struct

type key = Ord.t
type 'a dict = (key * 'a) list

let empty = []

let insert k v d =
  (k, v) :: List.remove_assoc k d

let remove k d =
  List.remove_assoc k d

let find_opt k d =
  try Some (List.assoc k d) with Not_found -> None

let find k d =
  List.assoc k d

let to_list d = d
end

(*Zadanie 4*)

module MakeMapDict (Ord : Map.OrderedType)
  : KDICT with type key = Ord.t = struct

  module M = Map.Make(Ord)

  type key = Ord.t
  type 'a dict = 'a M.t  

  let empty = M.empty

  let insert k v d =
    M.add k v d

  let remove k d =
    M.remove k d

  let find_opt k d =
    try Some (M.find k d)
    with Not_found -> None

  let find k d =
    M.find k d

  let to_list d =
    M.bindings d
end

(*Zadanie 5*)

module Freq (D : KDICT) = struct
  let freq (xs : D.key list) : (D.key * int) list =
    let update d x =
      let current_count = match D.find_opt x d with
        | Some n -> n
        | None -> 0
      in
      D.insert x (current_count + 1) d
    in
    let d = List.fold_left update D.empty xs in
    D.to_list d
end

let list_of_string s = String.to_seq s |> List.of_seq

module CharFreq = Freq(CharListDict)

let char_freq (s : string) : (char * int) list =
  CharFreq.freq list_of_string
  (*przykład użycia*)
  

