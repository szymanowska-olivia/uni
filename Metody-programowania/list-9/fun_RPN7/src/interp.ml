open Ast

let to_bop = function
  | "+"  -> Add
  | "-"  -> Sub
  | "*"  -> Mult
  | "/"  -> Div
  | op -> failwith ("Unknown operator: " ^ op)

let is_number s =
  match int_of_string_opt s with
  | Some _ -> true
  | None -> false

  let process_tokens tokens =
    List.fold_left
      (fun acc token ->
        if is_number token then
          Int (int_of_string token) :: acc
        else
          match acc with
          | right :: left :: rest -> 
              let op = to_bop token in
              let new_expr = Binop (op, left, right) in
              new_expr :: rest
          | _ -> failwith "invalid RPN expression"
      )
      []
      tokens
  
let parse (s : string) : expr =
  let tokens = String.split_on_char ' ' s in
  let stack = process_tokens tokens in
  match stack with
  | [result] -> result
  | _ -> failwith "invalid RPN expression"
