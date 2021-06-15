# Example Interpreter

A toy programming language meant as a way to learn how to write Interpreters

## Note to self:

- Maybe a CST to AST converter? I think that's how C does things

## Goals:
A basic REPL interpreter that has:

- [ ] Basic lexer... shouldn't be bad... right?
- [ ] A LL(1) Parser (I am fully aware this is very overkill, but this is an exercise in learning not slacking off):
    - [ ] Parse basic arithmetic (numbers, `+*()`, etc.)
    - [ ] Parse extended symbols (`-/^!`)
    - [ ] Parse implicit multiplication? (`Expr Expr = Expr '*' Expr`? Will need to figure out how to parse `Expr Expr` anyways)
    - [ ] Generates concrete syntax trees
    - [ ] Generates abstract syntax trees... Maybe...
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
