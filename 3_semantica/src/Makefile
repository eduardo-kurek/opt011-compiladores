SRCS := $(wildcard *.c)

all:
	flex lexer.l
	bison -d -t parser.y
	gcc -o ../sem ${SRCS} -lfl -g

clean:
	rm -f parser.tab.c parser.tab.h lex.yy.c