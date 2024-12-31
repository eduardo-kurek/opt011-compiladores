#ifndef ERRORS_H
#define ERRORS_H

typedef struct error{
    const char* cod;
    const char* msg;
    const char type;
} Error;

// Lexer errors
extern Error ERR_LEX_USE;
extern Error ERR_LEX_NOT_TPP;
extern Error ERR_LEX_FILE_NOT_EXISTS;
extern Error ERR_LEX_INV_CHAR;

// Parser errors
extern Error ERR_SYN_USE;
extern Error ERR_SYN_NOT_TPP;
extern Error ERR_SYN_FILE_NOT_EXISTS;
extern Error WAR_SYN_GEN_SYNTAX_TREE;
extern Error WAR_SYN_NOT_GEN_SYNTAX_TREE;
extern Error ERR_SYN_IRRECUPERAVEL;
extern Error WAR_SYN_ANA_SUCCESS;
extern Error ERR_SYN_LISTA_ARGUMENTOS;
extern Error ERR_SYN_INDICE;
extern Error ERR_SYN_PARAMETRO;
extern Error ERR_SYN_SE;
extern Error ERR_SYN_REPITA;
extern Error ERR_SYN_LEIA;
extern Error ERR_SYN_EOF_INESPERADO;
extern Error WAR_SYN_OUTPUT_FILE;

#endif
