#include "var_table.h"
#include "types.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct var_table_entry {
    char* name;
    char* scope;
    primitive_type type;
    struct var_table_entry* next;
    var_dimension dim;
    int dim_1_size; // Usado para vetores
    int dim_2_size; // Usado para matrizes
    bool initialized;
    int line;
};

struct var_table {
    vt_entry* first;
    int entry_count;
};

var_table* vt;

void vt_init(){
    vt = (var_table*)malloc(sizeof(var_table));
    vt->first = NULL;
    vt->entry_count = 0;
}

void vt_set_entry_dimension(Node* var_node, vt_entry* entry){
    if(var_node->child_count == 1){
        entry->dim = SCALAR;
        entry->dim_1_size = -1;
        entry->dim_2_size = -1;
        return;
    }

    if(var_node->ch[1]->child_count == 3){
        entry->dim = VECTOR;
        entry->dim_1_size = atoi(
            var_node->ch[1]->ch[1]->ch[0]->
            ch[0]->ch[0]->ch[0]->ch[0]->
            ch[0]->ch[0]->ch[0]->ch[0]->label
        );
        entry->dim_2_size = -1;
        return;
    }

    entry->dim = MATRIX;
    entry->dim_1_size = atoi(
        var_node->ch[1]->ch[0]->ch[1]->
        ch[0]->ch[0]->ch[0]->ch[0]->
        ch[0]->ch[0]->ch[0]->ch[0]->ch[0]->label
    );

    entry->dim_2_size = atoi(
        var_node->ch[1]->ch[2]->ch[0]->
        ch[0]->ch[0]->ch[0]->ch[0]->
        ch[0]->ch[0]->ch[0]->ch[0]->label
    );

    // brutal
}

vt_entry** aux_insere_uma_variavel(Node* var_declaration_node, char* scope){
    vt_entry** entries = (vt_entry**)malloc(sizeof(vt_entry*));
    vt_entry* entry = (vt_entry*)malloc(sizeof(vt_entry));
    char* label = var_declaration_node->ch[2]->ch[0]->ch[0]->ch[0]->label;
    primitive_type type = var_declaration_node->ch[0]->ch[0]->type;

    entry->name = label;
    entry->scope = scope;
    entry->initialized = false;
    entry->line = var_declaration_node->ch[2]->ch[0]->line;
    if(type == NT_INTEIRO) entry->type = T_INTEIRO;
    else entry->type = T_FLUTUANTE;
    vt_set_entry_dimension(var_declaration_node->ch[2]->ch[0], entry);

    entry->next = vt->first;
    vt->first = entry;
    vt->entry_count++;

    entries[0] = entry;
    return entries;
}

int aux_conta_variaveis(Node* var_declaration_node){
    Node* current = var_declaration_node->ch[2];
    int count = 0;
    while(current){
        count++;
        if(current->child_count == 1) current = NULL;
        else current = current->ch[0];
    }
}

vt_entry** aux_insere_varias_variaveis(Node* var_declaration_node, char* scope, int* qtde_variaveis){
    *qtde_variaveis = aux_conta_variaveis(var_declaration_node);
    vt_entry** entries = (vt_entry**)malloc(sizeof(vt_entry*) * (*qtde_variaveis));
    primitive_type type = (var_declaration_node->ch[0]->ch[0]->type == NT_INTEIRO) ? T_INTEIRO : T_FLUTUANTE;
    int line = var_declaration_node->ch[0]->ch[0]->line;

    Node* current = var_declaration_node->ch[2];
    int i = *qtde_variaveis-1;
    while(current){
        vt_entry* entry = (vt_entry*)malloc(sizeof(vt_entry));
        char* label;

        if(current->child_count == 1){
            label = current->ch[0]->ch[0]->ch[0]->label;
            vt_set_entry_dimension(current->ch[0], entry);
            current = NULL;
        }else{
            label = current->ch[2]->ch[0]->ch[0]->label;
            vt_set_entry_dimension(current->ch[2], entry);
            current = current->ch[0];
        }

        entry->name = label;
        entry->scope = scope;
        entry->type = type;
        entry->initialized = false;
        entry->line = line;

        entry->next = vt->first;
        vt->first = entry;
        vt->entry_count++;

        entries[i--] = entry;
    }

    return entries;
}

vt_entry** vt_insere(Node *var_declaration_node, char *scope, int *qtde_variaveis){    
    if(var_declaration_node->ch[2]->child_count == 1){
        *qtde_variaveis = 1;
        return aux_insere_uma_variavel(var_declaration_node, scope);
    }

    return aux_insere_varias_variaveis(var_declaration_node, scope, qtde_variaveis);
}

bool vt_existe(char *name, char *scope){
    vt_entry* current = vt->first;
    while(current != NULL){
        if(strcmp(current->name, name) == 0 && strcmp(current->scope, scope) == 0)
            return true;
        current = current->next;
    }
    return false;
}

void vt_imprime(){
    vt_entry* current = vt->first;
    while(current != NULL){
        printf("-------------------------\n");
        printf("Nome: %s\n", current->name);
        printf("Escopo: %s\n", current->scope);
        if(current->type == T_INTEIRO)
            printf("Tipo: inteiro\n");
        else
            printf("Tipo: flutuante\n");
        if(current->dim == SCALAR)
            printf("Dimensao: escalar\n");
        else if(current->dim == VECTOR)
            printf("Dimensao: vetor\n");
        else
            printf("Dimensao: matriz\n");
        if(current->dim == VECTOR)
            printf("Tamanho: %d\n", current->dim_1_size);
        else if(current->dim == MATRIX){
            printf("Tamanho 1: %d\n", current->dim_1_size);
            printf("Tamanho 2: %d\n", current->dim_2_size);
        }
        if(current->initialized)
            printf("Inicializada: sim\n");
        else
            printf("Inicializada: nao\n");
        printf("Linha: %d\n", current->line);
        printf("\n");
        current = current->next;
    }
}

void vt_destroy(){
    vt_entry* current = vt->first;
    while(current != NULL){
        vt_entry* next = current->next;
        
        free(current);
        current = next;
    }
    free(vt);
}
