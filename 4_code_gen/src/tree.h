#ifndef TREE_H
#define TREE_H

#include <stdarg.h>
#include "types.h"

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

typedef struct node{
    int id;
    char label[256];
    struct node** ch;
    int child_count;
    int child_max;
    node_type type;
    int line;
} Node;

Node* node_create(const char* label, node_type type);
int node_get_child_count(Node* node);
Node* node_create_leaf(const char* parentLabel, node_type parentType,
     const char* childLabel, node_type childType);
void node_add_child(Node* parent, Node* child);
void node_add_children(Node* parent, int num_children, ...);
void node_destroy(Node* node);

// Cria um novo node e destrói o node passado como argumento
Node* node_create_and_destroy(const char* label, node_type type, Node* destroy);

Node* node_create_add_children_and_destroy(Node* node, Node* destroy, int n_children, int* children);

/**
 * Clona 'node', adiciona os filhos selecionados de 'node' ao novo clone, 
 * destroi 'destroy' e retorna o clone.
 */
Node* node_clone_add_children_and_destroy(Node* node, Node* destroy, int n_children, int* children);

// Sobe o 'i' filho para o lugar do pai
Node* node_raise_child(Node* node, int i);

/**
 * Clona o node e sobe a label do i-ésimo filho para o lugar do pai
 * o tipo do node é mantido
 */
Node* node_clone_and_raise_child(Node* node, int i);

// Retorna uma cópia identica do node
Node* node_clone(Node* node);

Node* node_add_new_child(Node* parent, const char* label);
void node_to_dot(Node* root, const char* filename);
void node_print(Node* node);
const char* node_type_to_string(Node* node);

#endif