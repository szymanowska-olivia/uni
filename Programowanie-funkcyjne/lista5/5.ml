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
      and make prev xs' = 
        match xs' with
        | [] -> failwith "empty"  
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