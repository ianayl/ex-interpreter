# Grammar

Let's do this parser thing right...

## Current grammar of the language:

```
<Start> ::= <Add>
<Add>   ::= <Mul> '+' <Add>
        | <Mul> '-' <Add>
        | <Mul>
<Mul>   ::= <Term> '*' <Mul>
        | <Term> '/' <Mul>
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

<Mul>  ::= <Term> <Mul'>
<Mul'> ::= '*' <Term> <Mul'>
       | '/' <Term> <Mul'>
       | ε

<Term> ::= <Num>
       | '-' <Term>
       | '(' <Add> ')'
```
