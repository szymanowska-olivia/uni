
%token <float> FLOAT
%token PLUS
%token MINUS
%token TIMES
%token EXP
%token LOG
%token DIV
%token LPAREN
%token RPAREN
%token EOF

%start <Ast.expr> main


%left PLUS MINUS
%left TIMES DIV 
%right EXP
%right LOG

%%

main:
    | e = expr; EOF { e }
    ;

expr:
    | f = FLOAT { Float f }
    | e1 = expr; PLUS; e2 = expr { Binop(Add, e1, e2) }
    | e1 = expr; MINUS; e2 = expr { Binop(Sub, e1, e2) }
    | e1 = expr; DIV; e2 = expr { Binop(Div, e1, e2) }
    | e1 = expr; TIMES; e2 = expr { Binop(Mult, e1, e2) }
    | e1 = expr; EXP; e2 = expr { Binop(Exp, e1, e2) }  
    | LOG; e1 = expr { Prefop(Log, e1) }  
    | LPAREN; e = expr; RPAREN { e }
    ;


