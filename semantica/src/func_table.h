#ifndef FUNC_TABLE_H
#define FUNC_TABLE_H

#include "tree.h"
#include "types.h"

void ft_init();
ft_entry* ft_insere(Node* func_node);
char* ft_get_func_name(Node* func_node);
primitive_type ft_get_func_return_type(Node* func_node);

// Nó deve ser do tipo NT_LISTA_PARAMETRO
int ft_get_func_param_count(Node* param_list_node);
param** ft_get_func_params(Node* param_list_node);

ft_entry* ft_get_func_by_name(char* name);

void ft_imprime();
void ft_destroy();

#endif