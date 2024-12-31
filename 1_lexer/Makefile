CC=g++

all: src/lex.yy.cc
	${CC} src/lex.yy.cc -o tpplex -lfl src/Error.cpp

src/lex.yy.cc: src/tpplex.l
	flex -o src/lex.yy.cc src/tpplex.l

clean:
	rm -rf src/lex.yy.cc tpplex tpplex.exe __pycache__/ .pytest_cache