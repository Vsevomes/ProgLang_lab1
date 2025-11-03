grammar Lang;

// -----------------------------
// Parser rules
// -----------------------------
source
    : sourceItem* EOF
    ;

sourceItem
    : funcDef
    ;

funcDef
    : FUNCTION funcSignature statement* END FUNCTION
    ;

funcSignature
    : identifier '(' argList? ')' (AS typeRef)?
    ;

argList
    : argDef (',' argDef)*
    ;

argDef
    : identifier (AS typeRef)?
    ;

typeRef
    : builtinType                          # builtinTypeRef
    | identifier                           # customTypeRef
    | typeRef '(' typeArgList? ')'         # arrayTypeRef
    ;

typeArgList
    : typeRef (',' typeRef)*
    ;

// Statements
statement
    : DIM identifierList AS typeRef ';'?                # varDecl
    | IF expr THEN statement* (ELSE statement*)? END IF # ifStmt
    | WHILE expr statement* WEND                        # whileStmt
    | DO statement* LOOP (WHILE | UNTIL) expr           # doLoopStmt
    | BREAK ';'?                                        # breakStmt
    | expr ';'                                          # exprStmt
    ;

// identifier list like: a, b, c
identifierList
    : identifier (',' identifier)*
    ;

// Expressions with precedence (lowest first)
expr
    : expr OR expr                               # orExpr
    | expr AND expr                              # andExpr
    | expr (EQ | NEQ | LT | GT | LE | GE) expr   # compareExpr
    | expr (ADD | SUB) expr                      # addExpr
    | expr (MUL | DIV | MOD) expr                # mulExpr
    | expr ASSIGN expr                           # assignExpr
    | (NOT | SUB) expr                            # unaryExpr  // unary minus and not
    | primary                                    # primaryExpr
    ;

// Primary expression and call/index chaining
primary
    : atom ( '(' argExprList? ')' )*             // call(s)
    ;

argExprList
    : expr (',' expr)*
    ;

atom
    : '(' expr ')'               // parens
    | identifier                 // variable/place
    | literal                    // literal
    ;

// Literals
literal
    : BOOL
    | STRING
    | CHAR
    | HEX
    | BITS
    | DEC
    ;

// -----------------------------
// Lexer rules
// -----------------------------

// Keywords (case-sensitive). If you want case-insensitive keywords,
// either normalize input to one case before lexing or add variants.
FUNCTION : 'function';
END      : 'end';
IF       : 'if';
THEN     : 'then';
ELSE     : 'else';
WHILE    : 'while';
WEND     : 'wend';
DO       : 'do';
LOOP     : 'loop';
BREAK    : 'break';
DIM      : 'dim';
AS       : 'as';
UNTIL    : 'until';
TRUE     : 'true';
FALSE    : 'false';
RETURN   : 'return'; // reserved if needed

// Combined token for bool literal
BOOL : TRUE | FALSE ;

// Builtin primitive type names
BUILTIN_BOOL  : 'bool';
BUILTIN_BYTE  : 'byte';
BUILTIN_INT   : 'int';
BUILTIN_UINT  : 'uint';
BUILTIN_LONG  : 'long';
BUILTIN_ULONG : 'ulong';
BUILTIN_CHAR  : 'char';
BUILTIN_STRING: 'string';

fragment DIGIT      : [0-9];
fragment HEXDIGIT   : [0-9A-Fa-f];
fragment BIN_DIGIT  : [01];

// numeric/string/char tokens
HEX  : '0' [xX] HEXDIGIT+ ;
BITS : '0' [bB] BIN_DIGIT+ ;
DEC  : DIGIT+ ;

// string with simple escape handling
STRING
    : '"' ( ~["\\\r\n] | '\\' . )* '"'
    ;

// character literal: 'a' or escaped '\n'
CHAR
    : '\'' ( ~['\\\r\n] | '\\' . ) '\''
    ;

// Identifiers: start with letter or underscore, then letters/digits/underscore
identifier
    : Identifier
    ;

Identifier
    : [a-zA-Z_] [a-zA-Z_0-9]*
    ;

// Operators and punctuation
ASSIGN : '=';
EQ     : '==';
NEQ    : '<>' | '!=';
LT     : '<';
GT     : '>';
LE     : '<=';
GE     : '>=';

ADD : '+';
SUB : '-';
MUL : '*';
DIV : '/';
MOD : '%';

AND : 'and';
OR  : 'or';
NOT : 'not';

LPAREN : '(';
RPAREN : ')';
LBRACK : '[';
RBRACK : ']';
COMMA  : ',';
SEMI   : ';';

// Builtin type tokens used inside parser rules
builtinType
    : BUILTIN_BOOL
    | BUILTIN_BYTE
    | BUILTIN_INT
    | BUILTIN_UINT
    | BUILTIN_LONG
    | BUILTIN_ULONG
    | BUILTIN_CHAR
    | BUILTIN_STRING
    ;

// Whitespace and comments
WS
    : [ \t\r\n\u000C]+ -> skip
    ;

// single-line comment
LINE_COMMENT
    : '//' ~[\r\n]* -> skip
    ;

// block comment
BLOCK_COMMENT
    : '/*' .*? '*/' -> skip
    ;
