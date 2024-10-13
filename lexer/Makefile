CC=gcc

all: lex.yy.c
	${CC} lex.yy.c -o tpplex -lfl

lex.yy.c: tpplex.l
	flex tpplex.l

clean:
	rm -f lex.yy.c tpplex