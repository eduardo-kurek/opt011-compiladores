#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "errors.h"
#include "semantica.h"
#include "func_table.h"
#include "var_table.h"

extern bool check_key;

void declaracao_funcao(Node* func){
    ft_entry* entry = ft_insere(func);
}

void declaracao_variaveis(Node* var){
    char* scope = "global";
    int qtde_variaveis;
    vt_entry** entries = vt_insere(var, scope, &qtde_variaveis);

    free(entries);
}

void fazer_analise(Node* node){
    if(node->type == NT_NONE) return;

    if(node->type == NT_DECLARACAO_FUNCAO){
        declaracao_funcao(node);
        return;
    }

    if(node->type == NT_DECLARACAO_VARIAVEIS){
        declaracao_variaveis(node);
        return;
    }

    for(int i = 0; i < node->child_count; i++)
        fazer_analise(node->ch[i]);
}

void verifica_principal_existe(){
    ft_entry* entry = ft_get_func_by_name("principal");
    if(entry == NULL){
        if(check_key)
            printf("%s\n", ERR_SEM_MAIN_NOT_DECL.cod);
        else
            printf("\033[1;31m%s\033[0m\n", ERR_SEM_MAIN_NOT_DECL.msg);
    }
}

void analise_semantica(Node* node){
    ft_init();
    vt_init();

    fazer_analise(node);
    verifica_principal_existe();

    //ft_imprime();
    //vt_imprime();

    vt_destroy();
    ft_destroy();
}