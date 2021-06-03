CFLAGS = -Wall -g

TOKENS_H = src/parser/tokens.c src/parser/tokens.h

FILES = src/parser/parser.c $(TOKENS_H)

build: $(FILES)
	cc $(CFLAGS) -o arith $^

clean:
	rm arith
