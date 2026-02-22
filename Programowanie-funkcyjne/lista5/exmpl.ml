let nth n seq =
  let rec aux i s =
    if i = 1 then match s () with
      | Seq.Nil -> failwith "Stream too short"
      | Seq.Cons (x, _) -> x
    else match s () with
      | Seq.Nil -> failwith "Stream too short"
      | Seq.Cons (_, s') -> aux (i-1) s'
  in
  aux n seq
let first = nth 1 (stream_of_rationals ())
let second = nth 2 (stream_of_rationals ())
let third = nth 3 (stream_of_rationals ())

stream_of_rationals ()|> Seq.take 10 |> List.of_seq;;
