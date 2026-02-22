let th1 = I (Var "p") (by_assumption (Var "p"));;
let th2 = I (Var "p") (imp_i (Var "q") (by_assumption (Var "p")));;

let th3 = I (Var "p") (imp_i (Var "q") (by_assumption (Var "p")));;

let th4 = 