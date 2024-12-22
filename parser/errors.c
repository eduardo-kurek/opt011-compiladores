#include "errors.h"

const Error ERR_LEX_USE = {
    "ERR-LEX-USE", "Uso: ./lex -k arquivo.tpp"};

const Error ERR_LEX_NOT_TPP = {
    "ERR-LEX-NOT-TPP", "Arquivo não é um .tpp"
};

const Error ERR_LEX_FILE_NOT_EXISTS = {
    "ERR-LEX-FILE-NOT-EXISTS", "Tpp não existe"
};

const Error ERR_LEX_INV_CHAR = {
    "ERR-LEX-INV-CHAR", "Caractere inválido"
};

const Error ERR_SYN_USE = {
    "ERR-SYN-USE", "Uso: ./parser [-k] arquivo.tpp"
};

ERR-SYN-USE=Uso: python tppparser.py file.tpp
3 ERR-SYN-NOT-TPP=Não éum arquivo .tpp.
4 ERR-SYN-FILE-NOT-EXISTS=Arquivo .tpp não existe.
5 WAR-SYN-GEN-SYNTAX-TREE=Generating Syntax Tree Graph.
6 WAR-SYN-NOT-GEN-SYN-TREE=N\~ao foi poss\'ivel gerar a \'Arvore Sint\'atica.
7 ERR-SYN-IRRECUPERAVEL=Estado irrecuper\'avel.
8 WAR-SYN-ANA-SUCCESS=An\'alise Sint\'atica Executada com Sucesso. Gr\'afico da \'Arvore
foi gerado.
9 ERR-SYN-LISTA-ARGUMENTOS=Erro na lista de Argumentos.
10 ERR-SYN-INDICE=Erro na definicao do indice. Expressao ou indice.
11 ERR-SYN-EOF-INESPERADO=Erro inesperado.
12 WAR-SYN-OUTPUT-FILE=Output file: