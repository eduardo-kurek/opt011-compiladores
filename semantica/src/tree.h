#ifndef TREE_H
#define TREE_H

#include <stdarg.h>

enum node_type {
    NT_NONE, NT_PROGRAMA, NT_LISTA_DECLARACOES, NT_DECLARACAO, NT_DECLARACAO_VARIAVEIS,
    NT_INICIALIZACAO_VARIAVEIS, NT_LISTA_VARIAVEIS, NT_VAR, NT_INDICE, NT_TIPO,
    NT_DECLARACAO_FUNCAO, NT_CABECALHO, NT_LISTA_PARAMETROS, NT_PARAMETRO, NT_CORPO,
    NT_ACAO, NT_SE, NT_REPITA, NT_ATRIBUICAO, NT_LEIA,
    NT_ESCREVA, NT_RETORNA, NT_EXPRESSAO, NT_EXPRESSAO_LOGICA, NT_EXPRESSAO_SIMPLES,
    NT_EXPRESSAO_ADITIVA, NT_EXPRESSAO_MULTIPLICATIVA, NT_EXPRESSAO_UNARIA, NT_OPERADOR_RELACIONAL, NT_OPERADOR_SOMA,
    NT_OPERADOR_LOGICO, NT_OPERADOR_NEGACAO, NT_OPERADOR_MULTIPLICACAO, NT_FATOR, NT_NUMERO,
    NT_CHAMADA_FUNCAO, NT_LISTA_ARGUMENTOS, NT_VAZIO, NT_FIM, NT_ERROR,
    NT_NUM_NOTACAO_CIENTIFICA, NT_INTEIRO, NT_FLUTUANTE,
    NT_DIVIDE, NT_VEZES, NT_NAO, NT_OU, NT_E, NT_MAIOR, NT_MENOR, 
    NT_MAIOR_IGUAL, NT_MENOR_IGUAL, NT_IGUAL, NT_DIFERENTE,
    NT_MAIS, NT_MENOS, NT_ABRE_PARENTESE, NT_FECHA_PARENTESE, NT_ENTAO, NT_SENAO, NT_ATE,
    NT_NUM_PONTO_FLUTUANTE, NT_NUM_INTEIRO, NT_ABRE_COLCHETE, NT_FECHA_COLCHETE,
    NT_ID, NT_VIRGULA, NT_DOIS_PONTOS
};

typedef enum node_type NodeType;
typedef struct node Node;

Node* node_create(const char* label, NodeType type);
int node_get_child_count(Node* node);
Node* node_create_leaf(const char* parentLabel, NodeType parentType,
     const char* childLabel, NodeType childType);
void node_add_child(Node* parent, Node* child);
void node_add_children(Node* parent, int num_children, ...);
Node* node_add_new_child(Node* parent, const char* label);
void node_to_dot(Node* root, const char* filename);
void node_print(Node* node);

#endif