type formula =
| Var of string
| Bot
| Imp of formula * formula

let rec string_of_formula f = 
  match f with
  | Var s -> s
  | Bot -> "⊥"
  | Imp (p, q) -> 
    (let s' =
    (match p with
    | Imp _ -> "(" ^ (string_of_formula p) ^ ")"
    | _ -> string_of_formula p)
    in s' ^ " → " ^ (string_of_formula q))

let pp_print_formula fmtr f =
  Format.pp_print_string fmtr (string_of_formula f)

type theorem =
| Ax   of formula (*formula - jednoczesnie teza i zalozenie*)
| I    of formula * theorem (*formula - zal, theorem - dowod, I wynik w ND*)
| E    of theorem * theorem (*theorem1 - dowod implikacji, theorem2- dowod pierwszego wyrazu, E = wynik w ND*)
| EBot of formula * theorem (*formula - teza, theorem - dowod konczacy sie bot*)
let rec assumptions thm acc =
  match thm with
  | Ax p -> p::acc
  | I (p, thm') -> assumptions thm' acc (*formula to bylo tymczasowe zalozenie i teraz nie jest juz jego czescia wiec nie ma p::acc*)
  | E (thm', thm'') -> assumptions thm' (assumptions thm'' acc) (*założenie jednego dziecka + założenie drugiego*)
  | EBot (p, thm') -> assumptions thm' acc (*po prostu założenia dziecka, DN tego juz jest tezą a nie założeniem więc tego nie dodajemy*)


let rec consequence thm =
  match thm with
  | Ax p -> p
  | I (p, thm') -> Imp (p, consequence thm')  (*tworzymy nową formułe bo teza rodzica nie jest jawnie przekazana jak w Ax*)
  | E (thm', thm'') -> let Imp (_, thm''') = consequence thm' in thm'''  (*fi -> psi i fi | psi*)
  | EBot (p, thm') -> p  

(*let p = Var "p";;
  let q = Var "q";;
  let ax_q = Ax q;;
  let imp_q_p = I (q, ax_p);;
  let imp_p_q_p = I (p, imp_q_p);;*)
let pp_print_theorem fmtr thm =
  let open Format in
  pp_open_hvbox fmtr 2;
  begin match assumptions thm [] with
  | [] -> ()
  | f :: fs ->
    pp_print_formula fmtr f;
    fs |> List.iter (fun f ->
      pp_print_string fmtr ",";
      pp_print_space fmtr ();
      pp_print_formula fmtr f);
    pp_print_space fmtr ()
  end;
  pp_open_hbox fmtr ();
  pp_print_string fmtr "⊢";
  pp_print_space fmtr ();
  pp_print_formula fmtr (consequence thm);
  pp_close_box fmtr ();
  pp_close_box fmtr ()

let by_assumption f = Ax f

let imp_i f thm = I (f, thm)

let imp_e th1 th2 =
  match consequence th1 with
  | Imp (phi, psi) ->
      if consequence th2 = phi then
        E (th1, th2)
      else
        failwith "niezgodne formuły"
  | _ ->
      failwith "oczekuje implikacji"
let bot_e f thm = EBot (f, thm)