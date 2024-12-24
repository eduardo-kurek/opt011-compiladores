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

extern Error ERR_SEM_MAIN_NOT_DECL;
extern Error ERR_SEM_CALL_FUNC_NOT_DECL;
extern Error ERR_SEM_CALL_FUNC_WITH_FEW_ARGS;
extern Error ERR_SEM_CALL_FUNC_WITH_MANY_ARGS;
extern Error WAR_SEM_FUNC_DECL_NOT_USED;
extern Error ERR_SEM_FUNC_RET_TYPE_ERROR;
extern Error ERR_SEM_CALL_FUNC_MAIN_NOT_ALLOWED;
extern Error WAR_SEM_CALL_REC_FUNC_MAIN;

extern Error ERR_SEM_VAR_NOT_DECL;
extern Error WAR_SEM_VAR_DECL_NOT_INIT;
extern Error WAR_SEM_VAR_DECL_NOT_USED;
extern Error WAR_SEM_VAR_DECL_PREV;

extern Error WAR_SEM_ATR_DIFF_TYPES_IMP_COERC_OF_VAR;
extern Error WAR_SEM_ATR_DIFF_TYPES_IMP_COERC_OF_NUM;
extern Error WAR_SEM_ATR_DIFF_TYPES_IMP_COERC_OF_EXP;
extern Error WAR_SEM_ATR_DIFF_TYPES_IMP_COERC_OF_RET_VAL;

extern Error ERR_SEM_ARRAY_INDEX_NOT_INT;
extern Error ERR_SEM_INDEX_OUT_OF_RANGE;



#endif
