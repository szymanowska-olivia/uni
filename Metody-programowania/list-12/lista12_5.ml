type 'v form =
  | Var   of 'v
  | Not   of 'v form
  | And   of 'v form * 'v form
  | Or    of 'v form * 'v form
  | Implikacja  of 'v form * 'v form
  | Rownowaznosc   of 'v form * 'v form


type 'v nnf =
  | NNFLit  of bool * 'v 
  | NNFConj of 'v nnf * 'v nnf
  | NNFDisj of 'v nnf * 'v nnf


let rec elim_imp_i_row = function
  | Var x -> Var x
  | Not f -> Not (elim_imp_i_row f)
  | And(f1,f2) -> And(elim_imp_i_row f1, elim_imp_i_row f2)
  | Or(f1,f2) -> Or(elim_imp_i_row f1,  elim_imp_i_row f2)
  | Implikacja(f1,f2) -> Or(Not (elim_imp_i_row f1), elim_imp_i_row f2)
  | Rownowaznosc(f1,f2)->
      let a = elim_imp_i_row f1 
      and b = elim_imp_i_row f2 in
      And( Or(Not a, b), Or(Not b, a) )


let to_nnf f0 =
  let rec nnf positive f =
    match f with
    | Var x -> NNFLit (not positive, x)
    | Not f' -> nnf (not positive) f'
    | And(f1,f2) ->
        if positive then
          NNFConj(nnf true f1, nnf true f2)
        else
          NNFDisj(nnf false f1, nnf false f2)
    | Or(f1,f2) ->
        if positive then
          NNFDisj(nnf true f1, nnf true f2)
        else
          NNFConj(nnf false f1, nnf false f2)
    | Implikacja _ | Rownowaznosc _ -> failwith "nie powinno ich już tu być"
  in
  nnf true (elim_imp_i_row f0)