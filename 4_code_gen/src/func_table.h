#ifndef FUNC_TABLE_H
#define FUNC_TABLE_H

#include "tree.h"
#include "types.h"
#include <stdbool.h>

struct param{
    char* label;
    primitive_type type;
};

typedef struct func_table_entry {
    primitive_type return_type;
    char* name;
    int param_count;
    param** params;
    bool used;
    int line;

    Value func;
    Type funcType;
    Type* paramTypes;

    struct func_table_entry* next; // Lista encadeada
} ft_entry;

struct func_table {
    ft_entry* first;
    int entry_count;
};

void ft_init();
ft_entry* ft_insere(Node* func_node);
char* ft_get_func_name(Node* func_node);
primitive_type ft_get_func_return_type(Node* func_node);

// Nó deve ser do tipo NT_LISTA_PARAMETRO
int ft_get_func_param_count(Node* param_list_node);
param** ft_get_func_params(Node* param_list_node);

ft_entry* ft_get_func_by_name(char* name);

void ft_set_funcao_utilizada(Node* name);

void ft_verifica_principal_existe();
void ft_verifica_declarada_nao_chamada();
ft_entry* ft_verifica_funcao_existe(char* name);
void ft_verifica_quantidade_parametros(ft_entry* func, Node* lista_argumentos);
bool ft_verifica_chamada_para_principal(char* name, char* scope);

ft_entry* ft_insere_func_llvm(char* name, Type funcType, Type* paramTypes, Value func, int paramsCount, primitive_type returnType);
ft_entry* ft_get_func_llvm(char* name);

void ft_imprime();
void ft_destroy();

#endif