type 'a dllist = 'a dllist_data lazy_t
and 'a dllist_data =
{ prev : 'a dllist
; elem : 'a
; next : 'a dllist
}

let prev l = (Lazy.force l).prev
let elem l = (Lazy.force l).elem
let next l = (Lazy.force l).next
type 'a dllist = 'a dllist_data lazy_t
and 'a dllist_data = {
  prev : 'a dllist;
  elem : 'a;
  next : 'a dllist;
}

let prev l = (Lazy.force l).prev
let next l = (Lazy.force l).next
let elem l = (Lazy.force l).elem

let of_list lst =
  match lst with
  | [] -> failwith "empty list"
  | x :: xs ->
      let rec first = lazy { prev = last; elem = x; next = make first xs }
      and make prev = function
        | [] -> failwith "get yo ass outta here"  
        | [y] -> lazy { prev = prev; elem = y; next = first }  
        | y :: ys ->
            let rec this = lazy { prev = prev; elem = y; next = make this ys } in
            this
      and last = lazy (
        match xs with
        | [] -> Lazy.force first   
        | _ -> Lazy.force (make first xs ) 
      )
      in
      first

let integers =
  let rec first = lazy { prev = makeminus first 0; elem = 0; next = make first 0 }
  and make prev x = 
    let rec this = lazy {prev = prev; elem = x; next = make this (x + 1)} in this
  and makeminus next x =
    let rec this' = lazy {prev = makeminus this' (x - 1); elem = x; next = next } in this'
  in first

let lst = [1;2;3;4];;
let dll = of_list lst;;