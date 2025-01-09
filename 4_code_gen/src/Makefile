SRCS := $(wildcard *.c)
LLVM_VERSION := 18
LLVM_PATH = /usr/lib/llvm-${LLVM_VERSION}

all:
	flex lexer.l
	bison -d -t parser.y
	gcc -o ../gen ${SRCS} -lfl -g -lLLVM -I${LLVM_PATH}/include -L${LLVM_PATH}/lib

clean:
	rm -f parser.tab.c parser.tab.h lex.yy.c tree.dot tree.png ../gen