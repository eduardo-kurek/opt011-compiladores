#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "errors.h"
#include "semantica.h"
#include "func_table.h"
#include "var_table.h"

extern bool check_key;
extern bool semantic_error;

void analisa_declaracao_variaveis(Node* var, char* scope);
void analisa_expressao(Node* expression, char* scope);
void analisa_corpo(Node* body, char* scope);

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
                vt_set_used(fator->ch[0]->ch[0]->ch[0]->label, scope);
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
    vt_set_atribuida(atribuicao->ch[0]->ch[0]->ch[0]->label, scope);
}

void analisa_escreva(Node* escreva, char* scope){
    analisa_expressao(escreva->ch[2], scope);
}

void analisa_leia(Node* leia, char* scope){
    analisa_var(leia->ch[2], scope);
    vt_set_atribuida(leia->ch[2]->ch[0]->ch[0]->label, scope);
}

void analisa_repita(Node* repita, char* scope){
    analisa_corpo(repita->ch[1], scope);
    analisa_expressao(repita->ch[3], scope);
}

void analisa_se(Node* se, char* scope){
    analisa_expressao(se->ch[1], scope);
    analisa_corpo(se->ch[3], scope);
    if(se->child_count == 7)
        analisa_corpo(se->ch[5], scope); // Corpo do senão
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
            analisa_declaracao_variaveis(action, scope);
            break;

        case NT_EXPRESSAO:
            analisa_expressao(action, scope);
            break;
        
        case NT_SE:
            analisa_se(action, scope);
            break;

        case NT_REPITA:
            analisa_repita(action, scope);
            break;

        case NT_LEIA:
            analisa_leia(action, scope);
            break;

        case NT_ESCREVA:
            analisa_escreva(action, scope);
            break;

        default:
            break;
    }
}

void analisa_cabecalho(Node* cabecalho, char* scope){
    char* func_name = cabecalho->ch[1]->ch[0]->ch[0]->label;
    ft_entry* entry = ft_get_func_by_name(func_name);
    entry->used = true;
}

void analisa_declaracao_funcao(Node* func){
    ft_entry* entry = ft_insere(func);
    for(int i = 0; i < entry->param_count; i++){
        vt_insere_parametro(entry->params[i]->label, entry->params[i]->type, entry->name, entry->line);
    }

    if(func->child_count == 1)
        analisa_corpo(func->ch[0]->ch[4], entry->name);
    else
        analisa_corpo(func->ch[1]->ch[4], entry->name);

}

void analisa_inicializacao_variaveis(Node* var_init, char* scope){
    analisa_atribuicao(var_init->ch[0], scope);
}

void analisa_declaracao_variaveis(Node* var_declaration, char* scope){
    int qtde_variaveis;
    vt_insere(var_declaration, scope, &qtde_variaveis);
}

void analisa_declaracao(Node* declaration, char* scope){
    switch (declaration->ch[0]->type){
        case NT_DECLARACAO_VARIAVEIS:
            analisa_declaracao_variaveis(declaration->ch[0], scope);
            break;
        
        case NT_INICIALIZACAO_VARIAVEIS:
            analisa_inicializacao_variaveis(declaration->ch[0], scope);
            break;

        case NT_DECLARACAO_FUNCAO:
            analisa_declaracao_funcao(declaration->ch[0]);
            break;
    
        default:
            break;
    }
}

void analisa_lista_declaracoes(Node* declaration_list, char* scope){
    if(declaration_list->child_count == 2){
        analisa_lista_declaracoes(declaration_list->ch[0], scope);
        analisa_declaracao(declaration_list->ch[1], scope);
    }else{
        analisa_declaracao(declaration_list->ch[0], scope);
    }
}

void analisa_programa(Node* program){
    analisa_lista_declaracoes(program->ch[0], "global");
}

void analise_semantica(Node* node){
    ft_init();
    vt_init();

    analisa_programa(node);

    ft_verifica_principal_existe();
    ft_verifica_declarada_nao_chamada();
    vt_verifica_nao_inicializada();
    vt_verifica_nao_utilizada();

    //ft_imprime();
    //vt_imprime();

    vt_destroy();
    ft_destroy();
}