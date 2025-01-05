#include "func_table.h"
#include "errors.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

extern bool check_key;
extern bool semantic_error;
extern int yylineno;

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
    if(func_node->child_count == 1){
        entry->param_count = ft_get_func_param_count(func_node->ch[0]->ch[2]);
        entry->params = ft_get_func_params(func_node->ch[0]->ch[2]);
    }else{
        entry->param_count = ft_get_func_param_count(func_node->ch[1]->ch[2]);
        entry->params = ft_get_func_params(func_node->ch[1]->ch[2]);
    }
    entry->used = false;
    entry->line = func_node->ch[0]->line;

    entry->next = ft->first;
    ft->first = entry;
    ft->entry_count++;
    return entry;
}

char* ft_get_func_name(Node* func_node){ 
    if(func_node->child_count == 1) return func_node->ch[0]->ch[0]->ch[0]->label;
    else return func_node->ch[1]->ch[0]->ch[0]->label;
}

primitive_type ft_get_func_return_type(Node* func_node){
    if(func_node->child_count == 1) return T_VAZIO;
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

ft_entry* ft_get_func_by_name(char *name){
    ft_entry* current = ft->first;
    while(current != NULL){
        if(strcmp(current->name, name) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}

void ft_set_funcao_utilizada(Node *name){
    ft_entry* entry = ft_get_func_by_name(name->label);
    entry->used = true;
}

void ft_verifica_principal_existe(){
    ft_entry* entry = ft_get_func_by_name("principal");
    if(entry == NULL){
        semantic_error = true;
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
            else printf("\033[1;33mLinha %d: %s %s\033[0m\n", current->line, WAR_SEM_FUNC_DECL_NOT_USED.msg, current->name);
        }
        current = current->next;
    }
}

ft_entry* ft_verifica_funcao_existe(char* name){
    if(strcmp(name, "principal") == 0){
        semantic_error = true;
        if(check_key) printf("%s\n", ERR_SEM_CALL_FUNC_MAIN_NOT_ALLOWED.cod);
        else printf("\033[1;31mLinha %d: %s\033[0m\n", yylineno, ERR_SEM_CALL_FUNC_MAIN_NOT_ALLOWED.msg);
        return NULL;
    }
    ft_entry* func = ft_get_func_by_name(name);
    if(func == NULL){
        semantic_error = true;
        if(check_key) printf("%s\n", ERR_SEM_CALL_FUNC_NOT_DECL.cod);
        else printf("\033[1;31mLinha %d: %s %s\033[0m\n", yylineno, ERR_SEM_CALL_FUNC_NOT_DECL.msg, name);
        return NULL;
    }
    return func;
}

int conta_argumentos(Node* lista_argumentos){
    if(lista_argumentos->ch[0]->type == NT_VAZIO) return 0;
    if(lista_argumentos->child_count == 1) return 1;

    int qtArgs = 1;
    Node* current = lista_argumentos;
    while(1){
        if(current->child_count == 3) current = current->ch[0];
        else break;
        qtArgs++;
    }
    return qtArgs;
}

void ft_verifica_quantidade_parametros(ft_entry *func, Node *lista_argumentos){
    int qtArgs = conta_argumentos(lista_argumentos);
    if(qtArgs < func->param_count){
        semantic_error = true;
        if(check_key) printf("%s\n", ERR_SEM_CALL_FUNC_WITH_FEW_ARGS.cod);
        else printf("\033[1;31mLinha %d: %s %s\033[0m\n", yylineno, ERR_SEM_CALL_FUNC_WITH_FEW_ARGS.msg, func->name);
    } else if(qtArgs > func->param_count){
        semantic_error = true;
        if(check_key) printf("%s\n", ERR_SEM_CALL_FUNC_WITH_MANY_ARGS.cod);
        else printf("\033[1;31mLinha %d: %s %s\033[0m\n", yylineno, ERR_SEM_CALL_FUNC_WITH_MANY_ARGS.msg, func->name);
    }
}

bool ft_verifica_chamada_para_principal(char *name, char* scope){
    bool isPrincipal = strcmp(name, "principal") == 0;
    if(isPrincipal){
        if(strcmp(scope, "principal") == 0){
            if(check_key) printf("%s\n", WAR_SEM_CALL_REC_FUNC_MAIN.cod);
            else printf("\033[1;33mLinha %d: %s\033[0m\n", yylineno, WAR_SEM_CALL_REC_FUNC_MAIN.msg);
        } else {
            semantic_error = true;
            if(check_key) printf("%s\n", ERR_SEM_CALL_FUNC_MAIN_NOT_ALLOWED.cod);
            else printf("\033[1;31mLinha %d: %s\033[0m\n", yylineno, ERR_SEM_CALL_FUNC_MAIN_NOT_ALLOWED.msg);
        }
        return false;
    }
    return true;
}

void ft_imprime(){
    ft_entry* current = ft->first;
    while(current != NULL){
        printf("-------------------------\n");
        printf("Funcao: %s\n", current->name);
        if(current->return_type == T_INTEIRO)
            printf("Retorno: inteiro\n");
        else if (current->return_type == T_FLUTUANTE)
            printf("Retorno: flutuante\n");
        else
            printf("Retorno: vazio\n");
        printf("Qtde parametros: %d\n\n", current->param_count);
        for(int i = 0; i < current->param_count; i++){
            printf("Parametro %d:\n", i+1);
            printf("Nome: %s\n", current->params[i]->label);
            if(current->params[i]->type == T_INTEIRO)
                printf("Tipo: inteiro\n");
            else
                printf("Tipo: flutuante\n");
            printf("Linha: %d\n", current->line);
            printf("\n");
        }
        current = current->next;
    }
}

void ft_destroy(){
    ft_entry* current = ft->first;
    while(current != NULL){
        ft_entry* next = current->next;
        if(current->params != NULL){
            for(int i = 0; i < current->param_count; i++)
                free(current->params[i]);
            free(current->params);
        }
        free(current);
        current = next;
    }
    free(ft);
}

ft_entry* ft_insere_func_llvm(char* name, Type funcType, Type* paramTypes, Value func, int paramsCount){
    ft_entry* entry = (ft_entry*)malloc(sizeof(ft_entry));
    entry->name = name;
    entry->param_count = paramsCount;
    entry->params = NULL;
    entry->used = false;
    entry->line = 0;
    entry->func = func;
    entry->funcType = funcType;
    entry->paramTypes = paramTypes;

    entry->next = ft->first;
    ft->first = entry;
    ft->entry_count++;

    return entry;
}

ft_entry* ft_get_func_llvm(char* name){
    ft_entry* current = ft->first;
    while(current != NULL){
        if(strcmp(current->name, name) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}
