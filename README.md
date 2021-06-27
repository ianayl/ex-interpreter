# Experimental Interpreter

A toy programming language meant as a way to learn how to write Interpreters

Current state of the language: [current_grammar.md](https://github.com/ianayl/ex-interpreter/blob/main/parser/current_grammar.md)

## Note to self:

- You still need to write the function for modulo

## Goals:
A basic REPL interpreter that has:

- [x] Basic lexer
- [x] A LL(1) Parser
    - [x] Parse basic arithmetic (numbers, `+*()`, etc.)
    - [ ] Parse extended symbols (`-/^%`)
    - [ ] ~~Parse implicit multiplication? (`Expr Expr = Expr '*' Expr`? Will need to figure out how to parse `Expr Expr` anyways)~~
    - [x] Generates concrete syntax trees
    - [x] Generates abstract syntax trees
- [x] Evaluates ~~concrete~~ abstract syntax trees
- [ ] Introduce variables
    - [ ] Hashmaps...
- [ ] Introduce functions
    - [ ] More hashmaps...
- [ ] Introduce more complex data types
    - [ ] Introduce floats
    - [ ] Introduce structs?
    - [ ] Introduct lists
- [ ] Decent output...?
