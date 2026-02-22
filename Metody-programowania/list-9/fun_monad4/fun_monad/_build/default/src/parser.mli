
(* The type of tokens. *)

type token = 
  | WITH
  | UNIT
  | TIMES
  | THEN
  | SND
  | RPAREN
  | REF
  | PLUS
  | OR
  | NEQ
  | MINUS
  | MATCH
  | LT
  | LPAREN
  | LET
  | LEQ
  | ISPAIR
  | INT of (int)
  | IN
  | IF
  | IDENT of (string)
  | GT
  | GEQ
  | FUNREC
  | FUN
  | FST
  | EQ
  | EOF
  | ELSE
  | DIV
  | DEREF
  | COMMA
  | BOOL of (bool)
  | ASSGN
  | ARR
  | AND

(* This exception is raised by the monolithic API functions. *)

exception Error

(* The monolithic API. *)

val main: (Lexing.lexbuf -> token) -> Lexing.lexbuf -> (Ast.expr)
