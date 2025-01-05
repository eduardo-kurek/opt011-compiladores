#include "arvore_abstrata.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node* podar_lista_argumentos(Node* node);
Node* podar_chamada_funcao(Node* node);
Node* podar_numero(Node* node);
Node* podar_operador_logico(Node* node);
Node* podar_operador_relacional(Node* node);
Node* podar_operador_multiplicacao(Node* node);
Node* podar_operador_soma(Node* node);
Node* podar_fator(Node* node);
Node* podar_expressao_unaria(Node* node);
Node* podar_expressao_multiplicativa(Node* node);
Node* podar_expressao_aditiva(Node* node);
Node* podar_expressao_simples(Node* node);
Node* podar_expressao_logica(Node* node);
Node* podar_expressao(Node* node);
Node* podar_retorna(Node* node);
Node* podar_escreva(Node* node);
Node* podar_leia(Node* node);
Node* podar_atribuicao(Node* node);
Node* podar_repita(Node* node);
Node* podar_se(Node* node);
Node* podar_acao(Node* node);
Node* podar_corpo(Node* node);
Node* podar_parametro(Node* node);
Node* podar_lista_parametros(Node* node);
Node* podar_cabecalho(Node* node);
Node* podar_tipo(Node* node);
Node* podar_indice(Node* node);
Node* podar_var(Node* node);
Node* podar_id(Node* node);
Node* podar_lista_variaveis(Node* node);
Node* podar_declaracao_funcao(Node* node);
Node* podar_inicializacao_variaveis(Node* node);
Node* podar_declaracao_variaveis(Node* node);
Node* podar_declaracao(Node* node);
Node* podar_lista_declaracoes(Node* node);
void podar_programa(Node* node);

Node* podar_lista_argumentos(Node* node){
    if(node->child_count == 3){
        node->ch[0] = podar_lista_argumentos(node->ch[0]);
        node->ch[2] = podar_expressao(node->ch[2]);
        return node_create_add_children_and_destroy(node, node, 2, (int[]){0, 2});
    }
    else if(node->ch[0]->type == NT_EXPRESSAO)
        node->ch[0] = podar_expressao(node->ch[0]);
    return node;
}

Node* podar_chamada_funcao(Node* node){
    node->ch[0] = podar_id(node->ch[0]);
    node->ch[2] = podar_lista_argumentos(node->ch[2]);
    return node_create_add_children_and_destroy(node, node, 2, (int[]){0, 2});
}

Node* podar_numero(Node* node){
    node_type type = node->ch[0]->type;
    return node_create_and_destroy(node->ch[0]->ch[0]->label, type, node);
}

Node* podar_operador_soma(Node* node){ return node_raise_child(node, 0); }
Node* podar_operador_logico(Node* node){ return node_raise_child(node, 0); }
Node* podar_operador_relacional(Node* node){ return node_raise_child(node, 0); }
Node* podar_operador_multiplicacao(Node* node){ return node_raise_child(node, 0); }

Node* podar_fator(Node* node){
    switch (node->ch[0]->type) {
        case NT_ABRE_PARENTESE:
            node->ch[1] = podar_expressao(node->ch[1]);
            return node_clone_add_children_and_destroy(node->ch[1], node, 0, NULL);

        case NT_VAR:
            node->ch[0] = podar_var(node->ch[0]);
            return node_raise_child(node, 0);
            break;

        case NT_CHAMADA_FUNCAO:
            node->ch[0] = podar_chamada_funcao(node->ch[0]);
            return node_raise_child(node, 0);
            break;

        case NT_NUMERO:
            node->ch[0] = podar_numero(node->ch[0]);
            return node_create_and_destroy(node->ch[0]->label, node->ch[0]->type, node);

        default:
            break;
    }
}

Node* podar_expressao_unaria(Node* node){
    if(node->child_count == 2){
        node->ch[1] = podar_fator(node->ch[1]);
        if(node->ch[0]->type == NT_MENOS){
            char buff[256];
            if(node->ch[1]->type == NT_NUM_INTEIRO){
                int val = -atoi(node->ch[1]->label);
                sprintf(buff, "%d", val);
            }
            else{
                float val = -atof(node->ch[1]->label);
                sprintf(buff, "%f", val);
            }
            return node_create_and_destroy(buff, NT_NUM_PONTO_FLUTUANTE, node);
        }
        return node_create_and_destroy(node->ch[1]->label, node->ch[1]->type, node);
    }
    else{
        node->ch[0] = podar_fator(node->ch[0]);
        return node_raise_child(node, 0);
    }
}

Node* podar_expressao_multiplicativa(Node* node){
    if(node->child_count == 3){
        node->ch[0] = podar_expressao_multiplicativa(node->ch[0]);
        node->ch[1] = podar_operador_multiplicacao(node->ch[1]);
        node->ch[2] = podar_expressao_unaria(node->ch[2]);
        return node_clone_and_raise_child(node, 1);
    }
    else{
        node->ch[0] = podar_expressao_unaria(node->ch[0]);
        return node_raise_child(node, 0);
    }
}

Node* podar_expressao_aditiva(Node* node){
    if(node->child_count == 3){
        node->ch[0] = podar_expressao_aditiva(node->ch[0]);
        node->ch[1] = podar_operador_soma(node->ch[1]);
        node->ch[2] = podar_expressao_multiplicativa(node->ch[2]);
        return node_clone_and_raise_child(node, 1);
    }
    else{
        node->ch[0] = podar_expressao_multiplicativa(node->ch[0]);
        return node_raise_child(node, 0);
    }
}

Node* podar_expressao_simples(Node* node){
    if(node->child_count == 3){
        node->ch[0] = podar_expressao_simples(node->ch[0]);
        node->ch[1] = podar_operador_relacional(node->ch[1]);
        node->ch[2] = podar_expressao_aditiva(node->ch[2]);
        return node_clone_and_raise_child(node, 1);
    }
    else{
        node->ch[0] = podar_expressao_aditiva(node->ch[0]);
        return node_raise_child(node, 0);
    }
}

Node* podar_expressao_logica(Node* node){
    if(node->child_count == 3){
        node->ch[0] = podar_expressao_logica(node->ch[0]);
        node->ch[1] = podar_operador_logico(node->ch[1]);
        node->ch[2] = podar_expressao_simples(node->ch[2]);
        return node_clone_and_raise_child(node, 1);
    }
    else{
        node->ch[0] = podar_expressao_simples(node->ch[0]);
        return node_raise_child(node, 0);
    }
}

Node* podar_expressao(Node* node){
    if(node->ch[0]->type == NT_EXPRESSAO_LOGICA){
        node->ch[0] = podar_expressao_logica(node->ch[0]);
        return node_raise_child(node, 0);
    }
    else podar_atribuicao(node->ch[0]);
}

Node* podar_retorna(Node* node){
    node->ch[2] = podar_expressao(node->ch[2]);
    return node_create_add_children_and_destroy(node, node, 1, (int[]){2});
}

Node* podar_escreva(Node* node){
    node->ch[2] = podar_expressao(node->ch[2]);
    return node_create_add_children_and_destroy(node, node, 1, (int[]){2});
}

Node* podar_leia(Node* node){
    node->ch[2] = podar_var(node->ch[2]);
    return node_create_add_children_and_destroy(node, node, 1, (int[]){2});
}

Node* podar_atribuicao(Node* node){
    node->ch[0] = podar_var(node->ch[0]);
    node->ch[2] = podar_expressao(node->ch[2]);
    strcpy(node->label, node->ch[1]->ch[0]->label);
    return node_create_add_children_and_destroy(node, node, 2, (int[]){0, 2});
}

Node* podar_repita(Node* node){
    node->ch[1] = podar_corpo(node->ch[1]);
    node->ch[3] = podar_expressao(node->ch[3]);
    return node_create_add_children_and_destroy(node, node, 2, (int[]){1, 3});
}

Node* podar_se(Node* node){
    if(node->child_count == 5){
        node->ch[1] = podar_expressao(node->ch[1]);
        node->ch[3] = podar_corpo(node->ch[3]);
        return node_create_add_children_and_destroy(node, node, 2, (int[]){1, 3});
    }
    else{
        node->ch[1] = podar_expressao(node->ch[1]);
        node->ch[3] = podar_corpo(node->ch[3]);
        node->ch[5] = podar_corpo(node->ch[5]);
        return node_create_add_children_and_destroy(node, node, 3, (int[]){1, 3, 5});
    }
}

Node* podar_acao(Node* node){
    switch (node->ch[0]->type){
        case NT_EXPRESSAO:
            node->ch[0] = podar_expressao(node->ch[0]);
            break;

        case NT_DECLARACAO_VARIAVEIS:
            node->ch[0] = podar_declaracao_variaveis(node->ch[0]);
            break;
        
        case NT_SE:
            node->ch[0] = podar_se(node->ch[0]);
            break;
        
        case NT_REPITA: 
            node->ch[0] = podar_repita(node->ch[0]);
            break;
        
        case NT_LEIA:
            node->ch[0] = podar_leia(node->ch[0]);
            break;

        case NT_ESCREVA:
            node->ch[0] = podar_escreva(node->ch[0]);
            break;
            
        case NT_RETORNA:
            node->ch[0] = podar_retorna(node->ch[0]);
            break;
        
        default:
            break;
    }
    return node;
}

Node* podar_corpo(Node* node){
    if(node->ch[0]->type == NT_CORPO) node->ch[0] = podar_corpo(node->ch[0]);
    else return node_raise_child(node, 0); // Caso base, filho é vazio

    if(node->child_count == 2)
        node->ch[1] = podar_acao(node->ch[1]);

    if(node->ch[0]->type == NT_VAZIO)
        return node_clone_add_children_and_destroy(node->ch[1], node, 0, NULL);

    Node* new = node_create(node->ch[1]->label, node->ch[1]->type);
    node_add_children(new, 2, node_clone(node->ch[0]), node_clone(node->ch[1]->ch[0]));
    node_destroy(node);
    return new;
}

Node* podar_parametro(Node* node){
    if(node->ch[0]->type == NT_TIPO){
        node->ch[0] = podar_tipo(node->ch[0]);
        node->ch[2] = podar_id(node->ch[2]);
        return node_create_add_children_and_destroy(node, node, 2, (int[]){0, 2});
    }else{
        node->ch[0] = podar_parametro(node->ch[0]);
    }
    return node;
}

Node* podar_lista_parametros(Node* node){
    if(node->child_count == 2){
        node->ch[0] = podar_lista_parametros(node->ch[0]);
        node->ch[1] = podar_parametro(node->ch[1]);
    }
    else if(node->ch[0]->type == NT_PARAMETRO){
        node->ch[0] = podar_parametro(node->ch[0]);
    }
    return node;
}

Node* podar_cabecalho(Node* node){
    node->ch[0] = podar_id(node->ch[0]);
    node->ch[2] = podar_lista_parametros(node->ch[2]);
    node->ch[4] = podar_corpo(node->ch[4]);
    return node_create_add_children_and_destroy(node, node, 3, (int[]){0, 2, 4});
}

Node* podar_tipo(Node* node){
    return node_create_and_destroy(node->ch[0]->label, node->ch[0]->type, node);
}

Node* podar_indice(Node* node){
    if(node->child_count == 4){
        node->ch[0] = podar_indice(node->ch[0]);
        node->ch[2] = podar_expressao(node->ch[2]);
        return node_create_add_children_and_destroy(node, node, 2, (int[]){0, 2});
    }
    else{
        node->ch[1] = podar_expressao(node->ch[1]);
        return node_create_add_children_and_destroy(node, node, 1, (int[]){1});
    }
}

Node* podar_var(Node* node){
    if(node->child_count == 2){
        node->ch[0] = podar_id(node->ch[0]);
        node->ch[1] = podar_indice(node->ch[1]);
        Node* new = node_create(node->ch[0]->label, NT_VAR);
        node_add_child(new, node_clone(node->ch[1]));
        node_destroy(node);
        return new;
    }
    else{
        node->ch[0] = podar_id(node->ch[0]);
        return node_create_and_destroy(node->ch[0]->label, NT_VAR, node);
    }
}

Node* podar_id(Node* node){
    Node* new = node_raise_child(node, 0);
    new->type = NT_ID;
    return new;
}

Node* podar_lista_variaveis(Node* node){
    if(node->child_count == 3){
        node->ch[0] = podar_lista_variaveis(node->ch[0]);
        node->ch[2] = podar_var(node->ch[2]);
        Node* new = node_create(node->label, node->type);
        for(int i = 0; i < node->ch[0]->child_count; i++)
            node_add_child(new, node_clone(node->ch[0]->ch[i]));
        node_add_child(new, node_clone(node->ch[2]));
        node_destroy(node);
        return new;
    }else{
        node->ch[0] = podar_var(node->ch[0]);
        return node;
    }
}

Node* podar_declaracao_funcao(Node* node){
    if(node->child_count == 2){
        node->ch[0] = podar_tipo(node->ch[0]);
        node->ch[1] = podar_cabecalho(node->ch[1]);
    }
    else{
        node->ch[0] = podar_cabecalho(node->ch[0]);
    }
    return node;
}

Node* podar_inicializacao_variaveis(Node* node){
    node->ch[0] = podar_atribuicao(node->ch[0]);
    return node;
}

Node* podar_declaracao_variaveis(Node* node){
    node->ch[0] = podar_tipo(node->ch[0]);
    node->ch[2] = podar_lista_variaveis(node->ch[2]);
    return node_create_add_children_and_destroy(node, node, 2, (int[]){0, 2});
}

Node* podar_declaracao(Node* node){
    switch (node->ch[0]->type){
        case NT_DECLARACAO_VARIAVEIS:
            node->ch[0] = podar_declaracao_variaveis(node->ch[0]);
            break;
        
        case NT_INICIALIZACAO_VARIAVEIS:
            node->ch[0] = podar_inicializacao_variaveis(node->ch[0]);
            break;

        case NT_DECLARACAO_FUNCAO:
            node->ch[0] = podar_declaracao_funcao(node->ch[0]);
            break;
        
        default:
            break;
    }
    return node;
}

Node* podar_lista_declaracoes(Node* node){
    if(node->child_count == 1){
        node->ch[0] = podar_declaracao(node->ch[0]);
        return node_raise_child(node, 0);
    }else{
        node->ch[0] = podar_lista_declaracoes(node->ch[0]);
        node->ch[1] = podar_declaracao(node->ch[1]);
        Node* new = node_create(node->ch[1]->label, node->ch[1]->type);
        node_add_children(new, 2, node_clone(node->ch[0]), node_clone(node->ch[1]->ch[0]));
        node_destroy(node);
        return new;
    }
}

void podar_programa(Node* node){
    node->ch[0] = podar_lista_declaracoes(node->ch[0]);
}
