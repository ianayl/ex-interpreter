# Experimental Interpreter

A toy programming language meant as a way to learn how to write Interpreters

## Note to self:

## Goals:
A basic REPL interpreter that has:

- [ ] Basic lexer
- [ ] A LL(1) Parser
    - [x] Parse basic arithmetic (numbers, `+*`, etc.)
    - [ ] Parse extended symbols (`()-/^!`)
    - [ ] ~~Parse implicit multiplication? (`Expr Expr = Expr '*' Expr`? Will need to figure out how to parse `Expr Expr` anyways)~~
    - [x] Generates concrete syntax trees
    - [ ] Generates abstract syntax trees
- [ ] Evaluates ~~concrete~~ abstract syntax trees
- [ ] Introduce variables
    - [ ] Hashmaps...
- [ ] Introduce functions
    - [ ] More hashmaps...
- [ ] Introduce more complex data types
    - [ ] Introduce floats
    - [ ] Introduce structs?
    - [ ] Introduct lists
- [ ] Decent output...?
