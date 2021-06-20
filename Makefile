CC = cc
CFLAGS = -Wall -g

LEXER = lexer/tokens
CST_PARSER = parser/ast_parser/ast

ROOT = $(shell pwd)

LIBRARIES = $(LEXER) $(CST_PARSER)

build: libraries
	$(CC) $(CFLAGS) -Iinclude -o arith parser/ast_parser/ast_parser.c libraries/*

libraries:
	mkdir libraries
	for lib in $(LIBRARIES); do \
		$(CC) -c $${lib}.c -I$(ROOT)/include; \
	done
	mv *.o $(ROOT)/libraries

clean:
	rm -r libraries
	rm arith
