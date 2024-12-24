#include "semantica.h"
#include <stdio.h>
#include "func_table.h"
#include "var_table.h"

void declaracao_funcao(Node* func){
    ft_entry* entry = ft_insere(func);
}

void declaracao_variaveis(Node* var){
    char* scope = "global";
    int qtde_variaveis;
    vt_insere(var, scope, &qtde_variaveis);
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

void analise_semantica(Node* node){
    ft_init();
    vt_init();

    fazer_analise(node);

    ft_imprime();
    vt_imprime();

    vt_destroy();
    ft_destroy();
}