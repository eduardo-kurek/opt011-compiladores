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

void verifica_func_declarada_nao_chamada(){

}


void analise_semantica(Node* node){
    ft_init();
    vt_init();

    fazer_analise(node);

    ft_verifica_principal_existe();
    ft_verifica_declarada_nao_chamada();

    //ft_imprime();
    //vt_imprime();

    vt_destroy();
    ft_destroy();
}