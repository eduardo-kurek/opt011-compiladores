
all: compile

compile: main.c
	gcc main.c -lLLVM -I/usr/lib/llvm-18/include -L/usr/lib/llvm-18/lib -o main
	./main
	rm main

dis: meu_modulo.bc
	llvm-dis meu_modulo.bc
	rm meu_modulo.bc

clean:
	rm main *.ll *.bc
