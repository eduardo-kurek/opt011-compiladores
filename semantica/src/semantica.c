#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "errors.h"
#include "semantica.h"
#include "func_table.h"
#include "var_table.h"

extern bool check_key;
extern bool semantic_error;

void declaracao_variaveis(Node* var, char* scope);
void analisa_expressao(Node* expression, char* scope);

void analisa_var(Node* var, char* scope){
    char* var_name = var->ch[0]->ch[0]->label;
    vt_entry* entry = vt_existe(var_name, scope);
    if(entry == NULL){
        semantic_error = true;
        if(check_key)
            printf("%s", ERR_SEM_VAR_NOT_DECL.cod);
        else
            printf("\033[1;31mLinha %d: %s '%s'\033[0m\n", var->ch[0]->line, ERR_SEM_VAR_NOT_DECL.msg, var_name);
    }
}

void analisa_fator(Node* fator, char* scope){
    if(fator->child_count == 1){
        switch (fator->ch[0]->type){
            case NT_VAR:
                analisa_var(fator->ch[0], scope);
                break;
        
            default:
                break;
        }
    }else{
        analisa_expressao(fator->ch[1], scope);
    }
}

void analisa_expressao_unaria(Node* expression, char* scope){
    if(expression->child_count == 1)
        analisa_fator(expression->ch[0], scope);
    else{
        analisa_fator(expression->ch[1], scope);
    }
}

void analisa_expressao_multiplicativa(Node* expression, char* scope){
    if(expression->child_count == 1)
        analisa_expressao_unaria(expression->ch[0], scope);
    else{
        analisa_expressao_multiplicativa(expression->ch[0], scope);
        analisa_expressao_unaria(expression->ch[2], scope);
    }
}

void analisa_expressao_aditiva(Node* expression, char* scope){
    if(expression->child_count == 1)
        analisa_expressao_multiplicativa(expression->ch[0], scope);
    else{
        analisa_expressao_aditiva(expression->ch[0], scope);
        analisa_expressao_multiplicativa(expression->ch[2], scope);
    }
}

void analisa_expressao_simples(Node* expression, char* scope){
    if(expression->child_count == 1)
        analisa_expressao_aditiva(expression->ch[0], scope);
    else{
        analisa_expressao_simples(expression->ch[0], scope);
        analisa_expressao_aditiva(expression->ch[2], scope);
    }
}

void analisa_expressao_logica(Node* expression, char* scope){
    if(expression->child_count == 1)
        analisa_expressao_simples(expression->ch[0], scope);
    else{
        analisa_expressao_logica(expression->ch[0], scope);
        analisa_expressao_simples(expression->ch[2], scope);
    }
}

void analisa_atribuicao(Node* atribuicao, char* scope){
    analisa_var(atribuicao->ch[0], scope);
    analisa_expressao(atribuicao->ch[2], scope);
}


void analisa_expressao(Node* expression, char* scope){
    Node* next = expression->ch[0];
    node_type type = next->type;
    switch (type) {
        case NT_ATRIBUICAO:
            analisa_atribuicao(next, scope);
            break;
        
        case NT_EXPRESSAO_LOGICA:
            analisa_expressao_logica(next, scope);
            break;
    
        default:
            break;
    }
}

void analisa_corpo(Node* body, char* scope){
    if(body->ch[0]->type == NT_VAZIO) return;
    analisa_corpo(body->ch[0], scope);

    Node* action = body->ch[1]->ch[0];
    node_type type = action->type;

    switch(type){
        case NT_DECLARACAO_VARIAVEIS:
            declaracao_variaveis(action, scope);
            break;

        case NT_EXPRESSAO:
            analisa_expressao(action, scope);
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