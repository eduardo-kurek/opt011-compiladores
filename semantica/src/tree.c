#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define INITIAL_CHILD_COUNT 5

extern int yylineno;

static const char* node_type_strings[] = {
    "NT_NONE", "NT_PROGRAMA", "NT_LISTA_DECLARACOES", "NT_DECLARACAO", "NT_DECLARACAO_VARIAVEIS",
    "NT_INICIALIZACAO_VARIAVEIS", "NT_LISTA_VARIAVEIS", "NT_VAR", "NT_INDICE", "NT_TIPO",
    "NT_DECLARACAO_FUNCAO", "NT_CABECALHO", "NT_LISTA_PARAMETROS", "NT_PARAMETRO", "NT_CORPO",
    "NT_ACAO", "NT_SE", "NT_REPITA", "NT_ATRIBUICAO", "NT_LEIA",
    "NT_ESCREVA", "NT_RETORNA", "NT_EXPRESSAO", "NT_EXPRESSAO_LOGICA", "NT_EXPRESSAO_SIMPLES",
    "NT_EXPRESSAO_ADITIVA", "NT_EXPRESSAO_MULTIPLICATIVA", "NT_EXPRESSAO_UNARIA", "NT_OPERADOR_RELACIONAL", "NT_OPERADOR_SOMA",
    "NT_OPERADOR_LOGICO", "NT_OPERADOR_NEGACAO", "NT_OPERADOR_MULTIPLICACAO", "NT_FATOR", "NT_NUMERO",
    "NT_CHAMADA_FUNCAO", "NT_LISTA_ARGUMENTOS", "NT_VAZIO", "NT_FIM", "NT_ERROR",
    "NT_NUM_NOTACAO_CIENTIFICA", "NT_INTEIRO", "NT_FLUTUANTE",
    "NT_DIVIDE", "NT_VEZES", "NT_NAO", "NT_OU", "NT_E", "NT_MAIOR", "NT_MENOR",
    "NT_MAIOR_IGUAL", "NT_MENOR_IGUAL", "NT_IGUAL", "NT_DIFERENTE",
    "NT_MAIS", "NT_MENOS", "NT_ABRE_PARENTESE", "NT_FECHA_PARENTESE", "NT_ENTAO", "NT_SENAO", "NT_ATE",
    "NT_NUM_PONTO_FLUTUANTE", "NT_NUM_INTEIRO", "NT_ABRE_COLCHETE", "NT_FECHA_COLCHETE",
    "NT_ID", "NT_VIRGULA", "NT_DOIS_PONTOS"
};

int lastId = 0;

Node* node_create(const char* label, node_type type){
    Node* node = (Node*)malloc(sizeof(Node));
    node->id = lastId++;
    strncpy(node->label, label, sizeof(node->label) - 1);
    node->label[sizeof(node->label) - 1] = '\0';
    node->child_count = 0;
    node->child_max = INITIAL_CHILD_COUNT;
    node->type = type;
    node->line = yylineno;

    Node** children = (Node**)malloc(sizeof(Node*) * INITIAL_CHILD_COUNT);
    node->ch = children;
}

int node_get_child_count(Node* node){
    return node->child_count;
}

void node_adjust_children_length(Node* node){
    if(node->child_count == node->child_max){
        int new_size = node->child_max * 1.5;
        node->ch = (Node**)realloc(node->ch, sizeof(Node*) * new_size);
        node->child_max = new_size;
    }
}

void node_add_child(Node *parent, Node *child){
    node_adjust_children_length(parent);
    parent->ch[parent->child_count++] = child;
}

void node_add_children(Node* parent, int num_children, ...) {
    va_list args;
    va_start(args, num_children);

    for (int i = 0; i < num_children; i++) {
        Node* child = va_arg(args, Node*);
        node_add_child(parent, child);
    }

    va_end(args);
}


Node* node_add_new_child(Node* parent, const char* label){
    Node* child = node_create(label, NT_NONE);
    node_add_child(parent, child);
}

void generate_dot(Node* node, FILE* file){
    if(node == NULL) return;

    fprintf(file, "\t%d [label=\"%s (%s) %d\"];\n", node->id, node->label, node_type_strings[node->type], node->line);
    for(int i = 0; i < node->child_count; i++){
        fprintf(file, "\t%d -> %d;\n", node->id, node->ch[i]->id);
        generate_dot(node->ch[i], file);
    }
}

void node_to_dot(Node* root, const char *filename){
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file");
        return;
    }

    fprintf(file, "digraph Tree {\n");
    fprintf(file, "    node [shape=ellipse];\n");

    if (root != NULL) {
        generate_dot(root, file);
    }

    fprintf(file, "}\n");
    fclose(file);
}

void node_print(Node* node){
    printf("Node: %d\nChild_max: %d\nChild_count: %d\nChildren:", node->id, node->child_max, node->child_count);
    for(int i = 0; i < node->child_count; i++){
        printf("\tId: %d\n", node->ch[i]->id);
    }
}

Node* node_create_leaf(const char *parentLabel, node_type parentType,
     const char *childLabel, node_type childType){
    Node* parent = node_create(parentLabel, parentType);
    Node* child = node_create(childLabel, childType);
    node_add_child(parent, child);
    return parent;
}

const char* node_type_to_string(Node* node){
    return node_type_strings[node->type];
}
