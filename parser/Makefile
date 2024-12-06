all:
	flex test.l
	bison -d -t test.y
	gcc -o test test.tab.c lex.yy.c tree.c main.c errors.c -lfl