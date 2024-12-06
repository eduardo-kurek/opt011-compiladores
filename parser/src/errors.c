#include "errors.h"

// Lexer errors
Error ERR_LEX_USE = {"ERR-LEX-USE", "Uso: python tpplex.py file.tpp"};
Error ERR_LEX_NOT_TPP = {"ERR-LEX-NOT-TPP", "Não é um arquivo .tpp."};
Error ERR_LEX_FILE_NOT_EXISTS = {"ERR-LEX-FILE-NOT-EXISTS", "Arquivo .tpp não existe."};
Error ERR_LEX_INV_CHAR = {"ERR-LEX-INV-CHAR", "Caracter inválido."};

// Parser errors
Error ERR_SYN_USE = {"ERR-SYN-USE", "Uso: ./parser file.tpp [-k]"};
Error ERR_SYN_NOT_TPP = {"ERR-SYN-NOT-TPP", "Não é um arquivo .tpp."};
Error ERR_SYN_FILE_NOT_EXISTS = {"ERR-SYN-FILE-NOT-EXISTS", "Arquivo .tpp não existe."};
Error WAR_SYN_GEN_SYNTAX_TREE = {"WAR-SYN-GEN-SYNTAX-TREE", "Generating Syntax Tree Graph."};
Error WAR_SYN_NOT_GEN_SYNTAX_TREE = {"WAR-SYN-NOT-GEN-SYNTAX-TREE", "Não foi possível gerar a Árvore Sintática."};
Error ERR_SYN_IRRECUPERAVEL = {"ERR-SYN-IRRECUPERAVEL", "Estado irrecuperável."};
Error WAR_SYN_ANA_SUCCESS = {"WAR-SYN-ANA-SUCCESS", "Análise Sintática Executada com Sucesso. Gráfico da Árvore foi gerado."};
Error ERR_SYN_LISTA_ARGUMENTOS = {"ERR-SYN-LISTA-ARGUMENTOS", "Erro na lista de Argumentos."};
Error ERR_SYN_INDICE = {"ERR-SYN-INDICE", "Erro na definicao do indice. Expressao ou indice."};
Error ERR_SYN_EOF_INESPERADO = {"ERR-SYN-EOF-INESPERADO", "Erro inesperado."};
Error WAR_SYN_OUTPUT_FILE = {"WAR-SYN-OUTPUT-FILE", "Output file:"};
