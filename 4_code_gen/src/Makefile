SRCS := $(wildcard *.c)
LLVM_VERSION := 18

all:
	flex lexer.l
	bison -d -t parser.y
	gcc -o ../gen ${SRCS} -lfl -g -lLLVM -I/usr/lib/llvm-${LLVM_VERSION}/include -L/usr/lib/llvm-${LLVM_VERSION}/lib

clean:
	rm -f parser.tab.c parser.tab.h lex.yy.c tree.dot tree.png ../gen