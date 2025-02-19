#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "errors.h"
#include "semantica.h"
#include "func_table.h"
#include "var_table.h"
#include "arvore_abstrata.h"

extern bool check_key;
extern bool semantic_error;

// Variáveis globais para armazenar o valor de uma expressão
bool expression_is_constant = true;
primitive_type expression_type;
primitive_type expected_type; // Tipo esperado no lado direito de uma atribuição
primitive_type expected_return_type; // Tipo esperado no retorno de uma função
bool func_has_return = false; // Indica se a função tem retorno
int int_value; // Valor constante inteiro da expressão (se for inteiro)
double float_value; // Valor constante flutuante da expressão (se for flutuante)

bool in_factor_node = false;

void analisa_declaracao_variaveis(Node* var, char* scope);
void analisa_expressao(Node* expression, char* scope);
void analisa_corpo(Node* body, char* scope);

void analisa_lista_argumentos(Node* lista_argumentos, char* scope){
    if(lista_argumentos->child_count == 3){
        analisa_lista_argumentos(lista_argumentos->ch[0], scope);
        analisa_expressao(lista_argumentos->ch[2], scope);
    }else{
        if(lista_argumentos->ch[0]->type == NT_VAZIO) return;
        analisa_expressao(lista_argumentos->ch[0], scope);
    }
}

void analisa_numero(Node* numero, char* scope){
    if(numero->ch[0]->type == NT_NUM_INTEIRO){
        expression_type = T_INTEIRO;
        int_value = atoi(numero->ch[0]->ch[0]->label);
    }
    else{
        expression_type = T_FLUTUANTE;
        float_value = atof(numero->ch[0]->ch[0]->label);
    }
}

void analisa_chamada_funcao(Node* chamada_funcao, char* scope){
    expression_is_constant = false;
    // Verificando a quantidade de paramaetros da função
    if(!ft_verifica_chamada_para_principal(chamada_funcao->ch[0]->ch[0]->label, scope))
        return;
    ft_entry* func = ft_verifica_funcao_existe(chamada_funcao->ch[0]->ch[0]->label);
    if(func){
        ft_set_funcao_utilizada(chamada_funcao->ch[0]->ch[0]);
        ft_verifica_quantidade_parametros(func, chamada_funcao->ch[2]);
        expression_type = func->return_type;
    }
    analisa_lista_argumentos(chamada_funcao->ch[2], scope);
}

void analisa_indice(Node* indice, char* scope, vt_entry* entry, int dim){
    if(dim == 0) return;
    if(indice->child_count == 4){
        analisa_indice(indice->ch[0], scope, entry, dim-1);
        analisa_expressao(indice->ch[2], scope);
    }else{
        analisa_expressao(indice->ch[1], scope);
    }

    if(expression_type == T_FLUTUANTE){
        semantic_error = true;
        if(check_key) printf("%s\n", ERR_SEM_ARRAY_INDEX_NOT_INT.cod);
        else
            printf("\033[1;31mLinha %d: %s\033[0m\n", indice->ch[0]->line, ERR_SEM_ARRAY_INDEX_NOT_INT.msg);
    }
    else{
        int dimSize = dim == 1 ? entry->dim_1_size : entry->dim_2_size;
        if(int_value < 0 || int_value >= dimSize){
            semantic_error = true;
            if(check_key) printf("%s\n", ERR_SEM_INDEX_OUT_OF_RANGE.cod);
            else
                printf("\033[1;31mLinha %d: %s\033[0m\n", indice->ch[0]->line, ERR_SEM_INDEX_OUT_OF_RANGE.msg);
        }
    }
}

vt_entry* analisa_var(Node* var, char* scope){
    char* var_name = var->ch[0]->ch[0]->label;
    vt_entry* entry = vt_existe(var_name, scope);
    if(entry == NULL) entry = vt_existe(var_name, "global");
    if(entry == NULL){
        semantic_error = true;
        if(check_key)
            printf("%s\n", ERR_SEM_VAR_NOT_DECL.cod);
        else
            printf("\033[1;31mLinha %d: %s '%s'\033[0m\n", var->ch[0]->line, ERR_SEM_VAR_NOT_DECL.msg, var_name);
        return NULL;
    }

    if(in_factor_node){
        vt_set_used(var_name, scope);
        expression_is_constant = false;
        expression_type = entry->type;
    }

    if(var->child_count == 2)
        analisa_indice(var->ch[1], scope, entry, (int)entry->dim);
    return entry;
}

void analisa_fator(Node* fator, char* scope){
    in_factor_node = true;
    if(fator->child_count == 1){
        Node* child = fator->ch[0];
        switch (child->type){
            case NT_VAR:
                analisa_var(child, scope);
                vt_set_used(child->ch[0]->ch[0]->label, scope);
                break;

            case NT_CHAMADA_FUNCAO:
                analisa_chamada_funcao(child, scope);
                break;
            
            case NT_NUMERO:
                analisa_numero(child, scope);

            default:
                break;
        }
    }else{
        analisa_expressao(fator->ch[1], scope);
    }
    in_factor_node = false;
}

void analisa_expressao_unaria(Node* expression, char* scope){
    if(expression->child_count == 1)
        analisa_fator(expression->ch[0], scope);    
    else{
        analisa_fator(expression->ch[1], scope);

        // Mudando o sinal do número se preciso
        if(expression->ch[0]->type == NT_MENOS){
            if(expression_type == T_INTEIRO) int_value = -int_value;
            else float_value = -float_value;
        }
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

bool expressao_eh_unica_constante(Node* expression){
    int count = 0;
    Node* current = expression;
    while(1){
        if(count == 7){
            if(current->type == NT_NUMERO) return true;
            else return false;
        }
        if(current->child_count != 1) return false;
        count++;
        current = current->ch[0];
    }
}

bool expressao_eh_unica_variavel(Node* expression){
    int count = 0;
    Node* current = expression;
    while(1){
        if(count == 7){
            if(current->type == NT_VAR) return true;
            else return false;
        }
        if(current->child_count != 1) return false;
        count++;
        current = current->ch[0];
    }
}

bool expressao_eh_unica_funcao(Node* expression){
    int count = 0;
    Node* current = expression;
    while(1){
        if(count == 7){
            if(current->type == NT_CHAMADA_FUNCAO) return true;
            else return false;
        }
        if(current->child_count != 1) return false;
        count++;
        current = current->ch[0];
    }
}

void analisa_atribuicao(Node* atribuicao, char* scope){
    vt_entry* entry = analisa_var(atribuicao->ch[0], scope);
    if(entry){
        expected_type = entry->type;
        analisa_expressao(atribuicao->ch[2], scope);

        if(expressao_eh_unica_variavel(atribuicao->ch[2])){
            if(expected_type == T_INTEIRO && expression_type == T_FLUTUANTE){
                if(check_key) printf("%s\n", WAR_SEM_IMP_COERC_OF_VAR.cod);
                else
                    printf("\033[1;33mLinha %d: %s %s: '%s' para '%s'\033[0m\n", 
                    atribuicao->ch[0]->line, WAR_SEM_IMP_COERC_OF_VAR.msg, 
                    entry->name, "flutuante", "inteiro");
            }
            else if(expected_type == T_FLUTUANTE && expression_type == T_INTEIRO){
                if(check_key) printf("%s\n", WAR_SEM_IMP_COERC_OF_VAR.cod);
                else 
                    printf("\033[1;33mLinha %d: %s %s: '%s' para '%s'\033[0m\n", 
                    atribuicao->ch[0]->line, WAR_SEM_IMP_COERC_OF_VAR.msg, 
                    entry->name, "inteiro", "flutuante");
            }
        }
        else if (expressao_eh_unica_constante(atribuicao->ch[2])){
            if(expected_type == T_INTEIRO && expression_type == T_FLUTUANTE){
                if(check_key) printf("%s\n", WAR_SEM_IMP_COERC_OF_NUM.cod);
                else
                    printf("\033[1;33mLinha %d: %s %.2f do tipo flutuante para inteiro\033[0m\n", 
                    atribuicao->ch[0]->line, WAR_SEM_IMP_COERC_OF_NUM.msg, float_value);
            }
            else if(expected_type == T_FLUTUANTE && expression_type == T_INTEIRO){
                if(check_key) printf("%s\n", WAR_SEM_IMP_COERC_OF_NUM.cod);
                else 
                    printf("\033[1;33mLinha %d: %s %d do tipo inteiro para flutuante\033[0m\n", 
                    atribuicao->ch[0]->line, WAR_SEM_IMP_COERC_OF_NUM.msg, int_value);
            }
        }
        else if (expressao_eh_unica_funcao(atribuicao->ch[2])){
            if(expression_type == T_FLUTUANTE && expected_type == T_INTEIRO){
                if(check_key) printf("%s\n", WAR_SEM_IMP_COERC_OF_RET_VAL.cod);
                else
                    printf("\033[1;33mLinha %d: %s\033[0m\n", 
                    atribuicao->ch[0]->line, WAR_SEM_IMP_COERC_OF_RET_VAL.msg);
            }
            else if(expression_type == T_INTEIRO && expected_type == T_FLUTUANTE){
                if(check_key)printf("%s\n", WAR_SEM_IMP_COERC_OF_RET_VAL.cod);
                else
                    printf("\033[1;33mLinha %d: %s\033[0m\n", 
                    atribuicao->ch[0]->line, WAR_SEM_IMP_COERC_OF_RET_VAL.msg);
            }
        }
        else{
            if(expression_type == T_FLUTUANTE && expected_type == T_INTEIRO){
                if(check_key) printf("%s\n", WAR_SEM_IMP_COERC_OF_EXP.cod);
                else
                    printf("\033[1;33mLinha %d: %s\033[0m\n", 
                    atribuicao->ch[0]->line, WAR_SEM_IMP_COERC_OF_EXP.msg);
            }
            else if(expression_type == T_INTEIRO && expected_type == T_FLUTUANTE){
                if(check_key)printf("%s\n", WAR_SEM_IMP_COERC_OF_EXP.cod);
                else
                    printf("\033[1;33mLinha %d: %s\033[0m\n", 
                    atribuicao->ch[0]->line, WAR_SEM_IMP_COERC_OF_EXP.msg);
            }
        }
    }else{
        analisa_expressao(atribuicao->ch[2], scope);
    }
    vt_set_atribuida(atribuicao->ch[0]->ch[0]->ch[0]->label, scope);
}

void analisa_retorna(Node* retorna, char* scope){
    func_has_return = true;
    analisa_expressao(retorna->ch[2], scope);
    if(expression_type != expected_return_type){
        semantic_error = true;
        if(check_key) printf("%s\n", ERR_SEM_FUNC_RET_TYPE_ERROR.cod);
        else printf("\033[1;31mLinha %d: %s\033[0m\n", retorna->ch[0]->line, ERR_SEM_FUNC_RET_TYPE_ERROR.msg);
    }
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

        case NT_RETORNA:
            analisa_retorna(action, scope);
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

    func_has_return = false;
    expected_return_type = entry->return_type;
    if(func->child_count == 1)
        analisa_corpo(func->ch[0]->ch[4], entry->name);
    else
        analisa_corpo(func->ch[1]->ch[4], entry->name);

    if(expected_return_type != T_VAZIO && !func_has_return){
        semantic_error = true;
        if(check_key) printf("%s\n", ERR_SEM_FUNC_RET_TYPE_ERROR.cod);
        else printf("\033[1;31mLinha %d: %s %s\033[0m\n", func->ch[0]->line, ERR_SEM_FUNC_RET_TYPE_ERROR.msg, entry->name);
    }
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
    vt_verifica_inicializada_nao_utilizada();

    podar_programa(node);

    vt_destroy();
    ft_destroy();
}