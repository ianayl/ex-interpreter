CC = cc
CFLAGS = -Wall -g

LEXER = lexer/tokens
PARSER = parser/ast_parser/ast

ROOT = $(shell pwd)

LIBRARIES = $(LEXER) $(PARSER)

build: libraries
	$(CC) $(CFLAGS) -Iinclude -o arith lexer/lexer.c libraries/*

libraries:
	mkdir libraries
	for lib in $(LIBRARIES); do \
		$(CC) -c $${lib}.c -I$(ROOT)/include; \
	done
	mv *.o $(ROOT)/libraries

clean:
	rm -r libraries
	rm arith
