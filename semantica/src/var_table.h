#ifndef VAR_TABLE_H
#define VAR_TABLE_H

#include "tree.h"
#include <stdbool.h>

void vt_init();

// Nó deve ser do tipo NT_DECLARACAO_VARIAVEIS
vt_entry** vt_insere(Node* var_declaration_node, char* scope, int* qtde_variaveis);

bool vt_existe(char* name, char* scope);
void vt_imprime();
void vt_destroy();

#endif