let gen_sufiks xs =
  List.fold_right
    (fun x acc ->
       match acc with
       | y::_ -> ((x::y) :: acc)
       | [] -> [[x]])
  xs [[]]
  (*to samo co w drugim ale nie iterujemy po calym akumulatorze
  tylko bierzemy ostatni element*)