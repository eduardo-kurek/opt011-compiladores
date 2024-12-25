#ifndef VAR_TABLE_H
#define VAR_TABLE_H

#include "tree.h"
#include <stdbool.h>


struct var_table_entry {
    char* name;
    char* scope;
    primitive_type type;
    struct var_table_entry* next;
    var_dimension dim;
    int dim_1_size; // Usado para vetores
    int dim_2_size; // Usado para matrizes
    bool initialized;
    bool used;
    int line;
};

struct var_table {
    vt_entry* first;
    int entry_count;
};

void vt_init();

// Nó deve ser do tipo NT_DECLARACAO_VARIAVEIS
vt_entry** vt_insere(Node* var_declaration_node, char* scope, int* qtde_variaveis);
void vt_set_atribuida(char* name, char* scope);

// Nó deve ser do tipo NT_PARAMETRO
void vt_insere_parametro(char* name, primitive_type type, char* scope, int line);

void vt_set_used(char* name, char* scope);

vt_entry* vt_existe(char* name, char* scope);
void vt_imprime();
void vt_destroy();

void vt_verifica_nao_inicializada();
void vt_verifica_nao_utilizada();

#endif