# Experimental Interpreter

A toy programming language meant as a way to learn how to write Interpreters

Current state of the language: [current_grammar.md](https://github.com/ianayl/ex-interpreter/blob/main/parser/current_grammar.md)

## Note to self:

- Forgot to automatically reallocate the hashmap as load factor got to 0.8: Implement that

- Review `hashmap.c` after implementing garbage collector
    - **Btw:** consider implementing a garbage collector soon
    - Be sure to reconsider hashmap's freeing behavior after

## Goals:
A basic REPL interpreter that has:

- [x] Basic lexer
- [x] A LL(1) Parser
    - [x] Parse basic arithmetic (numbers, `+*()`, etc.)
    - [x] Parse extended symbols (`-/^%`)
    - [x] Generates concrete syntax trees
    - [x] Generates abstract syntax trees
- [x] Evaluates ~~concrete~~ abstract syntax trees
- [ ] Variables
    - [x] Implement a hashmap
    - [ ] Write and parse grammar for variables
- [ ] Functions
    - [ ] Introduce function object type
    - [ ] I _think_ I'm good if I just link AST's to variables
- [ ] Garbage collector
    - Screw reference counting we doing bicolored gc (or maybe tricolored...)
- [ ] Control flows, loops, etc
    - [ ] Introduce booleans
    - [ ] Introduce basic boolean expressions
    - [ ] Introduce if
    - [ ] Introduce while
    - [ ] Introduce for
- [ ] More data types
    - [ ] Consider: integers and bitwise operations
        - Also consider: making integers the default data type again
    - [ ] Introduce structs
    - [ ] Introduce lists
    - [ ] Hashmap exists, might as well make a dictionary too
- [ ] Decent output...?
    - lol seriously what on earth is the vomit I currently have????
