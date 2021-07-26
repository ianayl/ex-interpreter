# Old 'LL(1)' Grammar

Abandoned in favor of `LL(2)` because of clumsiness in `LL(1)`

```
<Start>   ::= <Expr>
<Expr>    ::= 'return' <Assign>
          | <Assign>

<Assign>  ::= <Identifier> <Assign'>
          | <Add>
<Assign'> ::= <Add'>
          | <Mul'>
          | <Exp'>
          | '=' <Add>
          | ε

<Add>     ::= <Mul> <Add'>
<Add'>    ::= '+' <Mul> <Add'>
          | '-' <Mul> <Add'>
          | ε 

<Mul>     ::= <Exp> <Mul'>
<Mul'>    ::= '*' <Exp> <Mul'>
          | '/' <Exp> <Mul'>
          | '%' <Exp> <Mul'>
          | ε

<Exp>     ::= <Term> <Exp'>
<Exp'>    ::= '^' <Term> <Exp'>
          | ε

<Term>    ::= <Num>
          | <Identifier>
          | '-' <Term>
          | '(' <Assign> ')'
```
