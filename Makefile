CC = cc
CFLAGS = -Wall -g

LEXER = lexer/tokens lexer/lexer
PARSER = parser/ast_parser/ast parser/ast_parser/ast_parser
EVAL = eval/eval

ROOT = $(shell pwd)

LIBRARIES = $(LEXER) $(PARSER) $(EVAL)

build: libraries
	$(CC) $(CFLAGS) -Iinclude -o arith main.c libraries/*

libraries:
	mkdir libraries
	for lib in $(LIBRARIES); do \
		$(CC) -c $${lib}.c -I$(ROOT)/include; \
	done
	mv *.o $(ROOT)/libraries

clean:
	rm -r libraries
	rm arith
