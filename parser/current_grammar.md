# Grammar

An LL(2) Grammar that heavily abuses left refactoring to avoid left 
recursion[[1]](#1):

```
<Start>   ::= <Expr>
<Expr>    ::= 'return' <Assign>
          ;   Consider separating function declaration to another derivation
          |   'fn' <Identifier> '(' <Param> ')' '=' <Assign>
          |   <Assign>
<Param>   ::= <Identifier> <Param'>
          |   ε 
<Param'>  ::= ',' <Identifier> <Param'>
          |   ε 


; Derivation below might be problematic, consider <Identifier> '=' <Add>
<Assign>  ::= <Identifier> '=' <Assign>
          |   <Add>

<Add>     ::= <Mul> <Add'>
<Add'>    ::= '+' <Mul> <Add'>
          |   '-' <Mul> <Add'>
          |   ε 

<Mul>     ::= <Exp> <Mul'>
<Mul'>    ::= '*' <Exp> <Mul'>
          |   '/' <Exp> <Mul'>
          |   '%' <Exp> <Mul'>
          |   ε

<Exp>     ::= <Term> <Exp'>
<Exp'>    ::= '^' <Term> <Exp'>
          |   ε

<Term>    ::= <Num>
          |   <Identifier>
          |   '-' <Term>
          |   '(' <Assign> ')'
```

___

<a id="1">[1]</a> 
Why left refactoring? What left recursion? If the grammar rule was as, for 
example:
```
<Mul>   ::= <Exp> '*' <Mul>
        |   <Exp> '/' <Mul>
        |   <Exp>
```
You would get trees as such for _i.e._ `3*4/1*2`:
```
            '*'
           /   \
          3    '/'
              /   \
             4    '*'
                 /   \
                1     2
```
Which evaluates to `3*(4/(1*2))=6`. This is wrong because `3*4/1*2=24`. If you 
left refactor, you get trees such as:
```
            <Add>
           /     \
          3      '*'
                /   \
               4    '/'
                   /   \
                  1    '*'
                        |
                        2
```
This is important because it leaves the tree ambiguous: it does not enforce a 
certain operator precedence: it is left to how the evaluator or the parser 
interprets this tree, which lets _i.e._ the parser to choose left or right 
precedence when it formulates the AST.

Note that this is just _my_ understanding: If you know more about this and my
understanding happens to be wrong please open an issue or something and let me
know, thanks in advance!
