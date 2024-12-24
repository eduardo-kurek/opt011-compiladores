#include "func_table.h"
#include "errors.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

extern bool check_key;

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

    struct func_table_entry* next; // Lista encadeada
} ft_entry;

struct func_table {
    ft_entry* first;
    int entry_count;
};

func_table* ft;

void ft_init(){
    ft = (func_table*)malloc(sizeof(func_table));
    ft->first = NULL;
    ft->entry_count = 0;
}

ft_entry* ft_insere(Node* func_node){
    ft_entry* entry = (ft_entry*)malloc(sizeof(ft_entry));
    entry->name = ft_get_func_name(func_node);
    entry->return_type = ft_get_func_return_type(func_node);
    entry->param_count = ft_get_func_param_count(func_node->ch[2]);
    entry->params = ft_get_func_params(func_node->ch[2]);
    entry->used = false;

    entry->next = ft->first;
    ft->first = entry;
    ft->entry_count++;
    return entry;
}

char* ft_get_func_name(Node* func_node){ 
    return func_node->ch[1]->ch[0]->ch[0]->label;
}

primitive_type ft_get_func_return_type(Node* func_node){
    if(func_node->ch[0]->ch[0]->type == NT_INTEIRO)
        return T_INTEIRO;
    return T_FLUTUANTE;
}

int ft_get_func_param_count(Node* param_list_node){
    if(param_list_node->ch[0]->type == NT_VAZIO) // Função sem parametros
        return 0;
    
    if(param_list_node->type == NT_PARAMETRO) // Caso base
        return 0;

    return 1 + ft_get_func_param_count(param_list_node->ch[0]);
}

param** aux_trata_um_parametro(Node* param_list_node){
    param** params = (param**)malloc(sizeof(param*));
    param* p = (param*)malloc(sizeof(param));
    p->label = param_list_node->ch[0]->ch[2]->ch[0]->label;
    if(param_list_node->ch[0]->ch[0]->ch[0]->type == NT_INTEIRO)
        p->type = T_INTEIRO;
    else
        p->type = T_FLUTUANTE;
    params[0] = p;
    return params;
}

param** aux_trata_varios_parametros(Node* param_list_node, int qtParams){
    param** params = (param**)malloc(qtParams * sizeof(param*));
    Node* current = param_list_node;
    int i = qtParams-1;
    while(true){
        if(current->child_count == 2){
            // RECURSÃO, TEM MAIS DEPOIS
            param* p = (param*)malloc(sizeof(param));
            p->label = current->ch[1]->ch[2]->ch[0]->label;
            if(current->ch[1]->ch[0]->ch[0]->type == NT_INTEIRO)
                p->type = T_INTEIRO;
            else
                p->type = T_FLUTUANTE;
            params[i--] = p;
            current = current->ch[0];
        } else {
            param* p = (param*)malloc(sizeof(param));
            p->label = current->ch[0]->ch[2]->ch[0]->label;
            if(current->ch[0]->ch[0]->ch[0]->type == NT_INTEIRO)
                p->type = T_INTEIRO;
            else
                p->type = T_FLUTUANTE;
            params[i] = p;
            break;
        }
    }
    return params;
}

param** ft_get_func_params(Node* param_list_node){
    int qtParams = ft_get_func_param_count(param_list_node);
    if(qtParams == 0) return NULL;
    if(qtParams == 1) return aux_trata_um_parametro(param_list_node);
    return aux_trata_varios_parametros(param_list_node, qtParams);
}

ft_entry*ft_get_func_by_name(char *name){
    ft_entry* current = ft->first;
    while(current != NULL){
        if(strcmp(current->name, name) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}

void ft_verifica_principal_existe(){
    ft_entry* entry = ft_get_func_by_name("principal");
    if(entry == NULL){
        if(check_key) printf("%s\n", ERR_SEM_MAIN_NOT_DECL.cod);
        else printf("\033[1;31m%s\033[0m\n", ERR_SEM_MAIN_NOT_DECL.msg);
    }
}

void ft_verifica_declarada_nao_chamada(){
    ft_entry* current = ft->first;
    while(current != NULL){
        if(strcmp(current->name, "principal") == 0){
            current = current->next;
            continue;
        }
        if(!current->used){
            if(check_key) printf("%s\n", WAR_SEM_FUNC_DECL_NOT_USED.cod);
            else printf("\033[1;33m%s %s\033[0m\n", WAR_SEM_FUNC_DECL_NOT_USED.msg, current->name);
        }
        current = current->next;
    }
}

void ft_imprime(){
    ft_entry* current = ft->first;
    while(current != NULL){
        printf("-------------------------\n");
        printf("Funcao: %s\n", current->name);
        if(current->return_type == T_INTEIRO)
            printf("Retorno: inteiro\n");
        else
            printf("Retorno: flutuante\n");
        printf("Qtde parametros: %d\n\n", current->param_count);
        for(int i = 0; i < current->param_count; i++){
            printf("Parametro %d:\n", i+1);
            printf("Nome: %s\n", current->params[i]->label);
            if(current->params[i]->type == T_INTEIRO)
                printf("Tipo: inteiro\n");
            else
                printf("Tipo: flutuante\n");
            printf("\n");
        }
        current = current->next;
    }
}

void ft_destroy(){
    ft_entry* current = ft->first;
    while(current != NULL){
        ft_entry* next = current->next;
        for(int i = 0; i < current->param_count; i++)
            free(current->params[i]);
        free(current->params);
        free(current);
        current = next;
    }
    free(ft);
}