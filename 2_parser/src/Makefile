all:
	flex lexer.l
	bison -d -t parser.y
	gcc -o ../parser parser.tab.c lex.yy.c tree.c main.c errors.c -lfl -g

clean:
	rm -f parser.tab.c parser.tab.h lex.yy.c tree.dot tree.png ../parser