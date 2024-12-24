#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "errors.h"
#include "semantica.h"
#include "func_table.h"
#include "var_table.h"

extern bool check_key;

void declaracao_variaveis(Node* var, char* scope);

void analisa_corpo(Node* body, char* scope){
    if(body->ch[0]->type == NT_VAZIO) return;
    analisa_corpo(body->ch[0], scope);

    Node* action = body->ch[1]->ch[0];
    node_type type = action->type;

    switch(type){
        case NT_DECLARACAO_VARIAVEIS:
            declaracao_variaveis(action, scope);
            break;
    
        default:
            break;
    }
}

void declaracao_funcao(Node* func){
    ft_entry* entry = ft_insere(func);
    for(int i = 0; i < entry->param_count; i++){
        vt_insere_parametro(entry->params[i]->label, entry->params[i]->type, entry->name, entry->line);
    }

    analisa_corpo(func->ch[1]->ch[4], entry->name);

    vt_remove_todas_variaveis_escopo(entry->name);
}

void declaracao_variaveis(Node* var, char* scope){
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
        declaracao_variaveis(node, "global");
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