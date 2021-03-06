# Experimental Interpreter

A toy programming language meant as a way to learn how to write Interpreters

Current state of the language: [current_grammar.md](https://github.com/ianayl/ex-interpreter/blob/main/parser/current_grammar.md)

## Note to self:

- Review `eval.c` and `ast_parser.c`; they're exceptionally scuffed and TODO's are building up lol....

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
- [x] Variables
    - [x] Implement a hashmap
    - [x] Write and parse grammar for variables
- [ ] Interaction
    - [x] Add an interactive shell mode
    - [ ] Add ability to read from file
- [ ] Functions
    - [ ] Introduce function object type: A list of AST's basically
    - [ ] Introduce scoping 
        - [ ] "Scopes" via a parent pointer tree of activation records (each containing it's own heap)
        - [ ] Associating each function call (scope/activation record) with it's own activation record in the parent-pointer tree
- [ ] Garbage collector
    - [ ] Reference counting GC maybe?
    - [ ] Actual, proper bicolored GC (or maybe even tricolored...)
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
