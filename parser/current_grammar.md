# Grammar

Let's do this parser thing right...

## Current grammar of the language:

```
<Start> ::= <Add>
<Add>   ::= <Mul> '+' <Add>
        | <Mul> '-' <Add>
        | <Mul>
<Mul>   ::= <Exp> '*' <Mul>
        | <Exp> '/' <Mul>
        | <Exp>
<Exp>   ::= <Term> '^' <Exp>
        | <Term>
<Term>  ::= <Num>
        | '-' <Term>
        | '(' <Add> ')'
```

## Left refactored for `LL(1)`:

```
<Start> ::= <Add>
<Add>   ::= <Mul> <Add'>
<Add'>  ::= '+' <Mul> <Add'>
        | '-' <Mul> <Add'>
        | ε 

<Mul>  ::= <Exp> <Mul'>
<Mul'> ::= '*' <Exp> <Mul'>
       | '/' <Exp> <Mul'>
       | ε

<Exp>  ::= <Term> <Exp'>
<Exp'> ::= '^' <Term> <Exp'>
       | ε

<Term> ::= <Num>
       | '-' <Term>
       | '(' <Add> ')'
```
