type bop = Add | Sub | Mult | Div | Exp
type pop = Log

type expr = 
    | Float of float
    | Binop of bop * expr * expr
    | Prefop of pop * expr
