CC = cc
CFLAGS = -Wall -g

LEXER = lexer/tokens
CST_PARSER = parser/cst_parser/cst

ROOT = $(shell pwd)

LIBRARIES = $(LEXER) $(CST_PARSER)

build: libraries
	$(CC) $(CFLAGS) -Iinclude -o arith parser/cst_parser/cst_parser.c libraries/*

libraries:
	mkdir libraries
	for lib in $(LIBRARIES); do \
		$(CC) -c $${lib}.c -I$(ROOT)/include; \
	done
	mv *.o $(ROOT)/libraries

clean:
	rm -r libraries
	rm arith
