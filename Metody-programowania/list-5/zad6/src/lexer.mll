{
open Parser
}

let white = [' ' '\t']+
let digit = ['0'-'9']
let fract = '.' digit+
let number = '-'? digit+ fract
(*let e = "2.718281828459045"*)

rule read =
    parse
    | white { read lexbuf }
    | "log" { LOG }
    | "**" { EXP }
    | "*." { TIMES }
    | "+." { PLUS }
    | "-." { MINUS }
    | "/." { DIV }
    | "(" { LPAREN }
    | ")" { RPAREN }
    | "e" { FLOAT 2.718281828459045 }
    | number { FLOAT ( float_of_string (Lexing.lexeme lexbuf)) }
    | eof { EOF }
