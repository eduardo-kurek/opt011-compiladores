#ifndef VAR_TABLE_H
#define VAR_TABLE_H

#include "tree.h"
#include "types.h"
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

    Value ref;
    bool isParam; // Indica se é um parâmetro de uma variavel
    Value dim1Val;
    Value dim2Val;
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
void vt_remove_todos(char* scope);
void vt_imprime();
void vt_destroy();

void vt_verifica_nao_utilizada();
void vt_verifica_inicializada_nao_utilizada();
void vt_verifica_nao_inicializada();

vt_entry* vt_insere_variavel_alocada(char* name, char* scope, 
    Value ref, Value dim1Val, Value dim2Val, var_dimension dim,
    primitive_type type, bool isParam);
vt_entry* vt_obter_variavel_alocada(char* name);

#endif