CC = cc
CFLAGS = -Wall -g

LEXER = lexer/tokens lexer/lexer
PARSER = parser/ast_parser/ast parser/ast_parser/ast_parser
EVAL = eval/hashmap eval/eval eval/object eval/record

ROOT = $(shell pwd)

LIBRARIES = $(LEXER) $(PARSER) $(EVAL)

build: libraries
	$(CC) $(CFLAGS) -Iinclude -lm -o arith main.c libraries/*

libraries:
	mkdir libraries
	for lib in $(LIBRARIES); do \
		$(CC) -g -c $${lib}.c -I$(ROOT)/include; \
	done
	mv *.o $(ROOT)/libraries

clean:
	rm -r libraries
	rm arith
