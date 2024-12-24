#include "errors.h"

// Lexer errors
Error ERR_LEX_USE = {"ERR-LEX-USE", "Uso: python tpplex.py file.tpp", 'E'};
Error ERR_LEX_NOT_TPP = {"ERR-LEX-NOT-TPP", "Não é um arquivo .tpp.", 'E'};
Error ERR_LEX_FILE_NOT_EXISTS = {"ERR-LEX-FILE-NOT-EXISTS", "Arquivo .tpp não existe.", 'E'};
Error ERR_LEX_INV_CHAR = {"ERR-LEX-INV-CHAR", "Caracter inválido.", 'E'};

// Parser errors
Error ERR_SYN_USE = {"ERR-SYN-USE", "Uso: ./parser file.tpp [-k]", 'E'};
Error ERR_SYN_NOT_TPP = {"ERR-SYN-NOT-TPP", "Não é um arquivo .tpp.", 'E'};
Error ERR_SYN_FILE_NOT_EXISTS = {"ERR-SYN-FILE-NOT-EXISTS", "Arquivo .tpp não existe.", 'E'};
Error WAR_SYN_GEN_SYNTAX_TREE = {"WAR-SYN-GEN-SYNTAX-TREE", "Generating Syntax Tree Graph.", 'W'};
Error WAR_SYN_NOT_GEN_SYNTAX_TREE = {"WAR-SYN-NOT-GEN-SYNTAX-TREE", "Não foi possível gerar a Árvore Sintática.", 'W'};
Error ERR_SYN_IRRECUPERAVEL = {"ERR-SYN-IRRECUPERAVEL", "Estado irrecuperável.", 'E'};
Error WAR_SYN_ANA_SUCCESS = {"WAR-SYN-ANA-SUCCESS", "Análise Sintática Executada com Sucesso. Gráfico da Árvore foi gerado.", 'W'};
Error ERR_SYN_LISTA_ARGUMENTOS = {"ERR-SYN-LISTA-ARGUMENTOS", "Erro na lista de Argumentos.", 'E'};
Error ERR_SYN_INDICE = {"ERR-SYN-INDICE", "Erro na definicao do indice. Expressao ou indice.", 'E'};
Error ERR_SYN_PARAMETRO = {"ERR-SYN-PARAMETRO", "Erro na definicao do parametro. Expressao ou parametro.", 'E'};
Error ERR_SYN_SE = {"ERR-SYN-SE", "Erro na definicao do comando se. Expressao esperada.", 'E'};
Error ERR_SYN_REPITA = {"ERR-SYN-REPITA", "Erro na definicao do comando repita. Expressao esperada.", 'E'};
Error ERR_SYN_LEIA = {"ERR-SYN-LEIA", "Erro na definicao do comando leia. Identificador esperado.", 'E'};
Error ERR_SYN_EOF_INESPERADO = {"ERR-SYN-EOF-INESPERADO", "Erro inesperado.", 'E'};
Error WAR_SYN_OUTPUT_FILE = {"WAR-SYN-OUTPUT-FILE", "Output file: tree.dot", 'W'};

Error ERR_SEM_MAIN_NOT_DECL = {"ERR-SEM-MAIN-NOT-DECL", "Função principal não declarada.", 'E'};
Error ERR_SEM_CALL_FUNC_NOT_DECL = {"ERR-SEM-CALL-FUNC-NOT-DECL", "Função chamada não declarada.", 'E'};  // TODO
Error ERR_SEM_CALL_FUNC_WITH_FEW_ARGS = {"ERR-SEM-CALL-FUNC-WITH-FEW-ARGS", "Função chamada com poucos argumentos.", 'E'};  // TODO
Error ERR_SEM_CALL_FUNC_WITH_MANY_ARGS = {"ERR-SEM-CALL-FUNC-WITH-MANY-ARGS", "Função chamada com muitos argumentos.", 'E'};  // TODO
Error WAR_SEM_FUNC_DECL_NOT_USED = {"WAR-SEM-FUNC-DECL-NOT-USED", "Função declarada e não utilizada.", 'W'};
Error ERR_SEM_FUNC_RET_TYPE_ERROR = {"ERR-SEM-FUNC-RET-TYPE-ERROR", "Função com tipo de retorno diferente do esperado.", 'E'};  // TODO
Error ERR_SEM_CALL_FUNC_MAIN_NOT_ALLOWED = {"ERR-SEM-CALL-FUNC-MAIN-NOT-ALLOWED", "Função main não pode ser chamada.", 'E'};  // TODO
Error WAR_SEM_CALL_REC_FUNC_MAIN = {"WAR-SEM-CALL-REC-FUNC-MAIN", "Chamada recursiva da função main.", 'W'};  // TODO