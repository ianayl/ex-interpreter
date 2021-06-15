# Grammar

Let's do this parser thing right...

## Current grammar of the language:

```
<Start> ::= <Add>
<Add>   ::= <Mul> '+' <Add>
        | <Mul>
<Mul>   ::= <Term> '*' <Mul>
        | <Term>
<Term>  ::= <Num>
        | '-' <Term>
        | '(' <Add> ')'
```

## Left refactored for `LL(1)`:

```
<Start> ::= <Add>
<Add>   ::= <Mul> <Add'>
<Add'>  ::= '+' <Add>
        | ε 

<Mul>  ::= <Term> <Mul'>
<Mul'> ::= '*' <Mul>
       | ε

<Term> ::= <Num>
       | '-' <Term>
       | '(' <Add> ')'
```
