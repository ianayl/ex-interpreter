# Grammar

Let's do this parser thing right...

## Current grammar of the language:

```
<Start> ::= <Expr>
<Expr>  ::= <Identifier> '=' <Add>
        | 'return' <Add>
        | <Add>
<Add>   ::= <Mul> '+' <Add>
        | <Mul> '-' <Add>
        | <Mul>
<Mul>   ::= <Exp> '*' <Mul>
        | <Exp> '/' <Mul>
        | <Exp> '%' <Mul>
        | <Exp>
<Exp>   ::= <Term> '^' <Exp>
        | <Term>
<Term>  ::= <Num>
        | <Identifier>
        | '-' <Term>
        | '(' <Add> ')'
```

## Left refactored for `LL(1)`:

```
<Start>   ::= <Expr>
<Expr>    ::= 'return' <Assign>
          | <Assign>

<Assign>  ::= <Identifier> <Assign'>
          | <Add>
# I am well aware that this is SCUFFED
# TODO fix this grammar this is atrocious
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

