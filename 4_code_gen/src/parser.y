%{
#include <stdio.h>
#include "tree.h"
#include <stdbool.h>
#include "errors.h"

int yylex();
int yyerror(char* s);
void my_yyerror(const Error* err);

extern bool check_key;
extern char* yytext;

bool success = true;
bool fatal_error = false;
Node* syntax_tree = NULL;

extern int yylineno;
%}

%token<value> NUM_INTEIRO NUM_PONTO_FLUTUANTE NUM_NOTACAO_CIENTIFICA ID
%token MAIS MENOS VEZES DOIS_PONTOS VIRGULA MENOR MAIOR IGUAL DIFERENTE MENOR_IGUAL DIVIDE
%token MAIOR_IGUAL E OU NAO ABRE_PARENTESE FECHA_PARENTESE ABRE_COLCHETE FECHA_COLCHETE 
%token SE ENTAO SENAO FIM REPITA ATE ATRIBUICAO LEIA ESCREVA RETORNA INTEIRO FLUTUANTE

%type<node> programa lista_declaracoes declaracao declaracao_variaveis inicializacao_variaveis 
%type<node> lista_variaveis var indice tipo declaracao_funcao cabecalho lista_parametros 
%type<node> parametro corpo acao se repita atribuicao leia escreva retorna expressao 
%type<node> expressao_logica expressao_simples expressao_aditiva expressao_multiplicativa expressao_unaria 
%type<node> operador_relacional operador_soma operador_logico operador_negacao operador_multiplicacao fator
%type<node> numero chamada_funcao lista_argumentos vazio

%union{
    char value[500];
    struct node* node;
}

%start programa
%define parse.error custom

%%

programa:
    lista_declaracoes {
        $$ = node_create("programa", NT_PROGRAMA);
        node_add_child($$, $1);
        syntax_tree = $$;
    }
    | error { fatal_error = true; }
;

lista_declaracoes:
    lista_declaracoes declaracao {
        $$ = node_create("lista_declaracoes", NT_LISTA_DECLARACOES);
        node_add_children($$, 2, $1, $2);
    }
    | declaracao {
        $$ = node_create("lista_declaracoes", NT_LISTA_DECLARACOES);
        node_add_child($$, $1);
    }
;

declaracao: 
    declaracao_funcao {
        $$ = node_create("declaracao", NT_DECLARACAO);
        node_add_child($$, $1);
    }
    | declaracao_variaveis {
        $$ = node_create("declaracao", NT_DECLARACAO);
        node_add_child($$, $1);
    }
    | inicializacao_variaveis {
        $$ = node_create("declaracao", NT_DECLARACAO);
        node_add_child($$, $1);
    }
;

declaracao_variaveis:
    tipo DOIS_PONTOS lista_variaveis {
        $$ = node_create("declaracao_variaveis", NT_DECLARACAO_VARIAVEIS);
        node_add_children($$, 3, $1, node_create_leaf("DOIS_PONTOS", NT_DOIS_PONTOS, ":", NT_NONE), $3);
    }
;

inicializacao_variaveis:
    atribuicao {
        $$ = node_create("inicializacao_variaveis", NT_INICIALIZACAO_VARIAVEIS);
        node_add_child($$, $1);
    }
;

lista_variaveis:
    lista_variaveis VIRGULA var {
        $$ = node_create("lista_variaveis", NT_LISTA_VARIAVEIS);
        node_add_children($$, 3, $1, node_create_leaf("VIRGULA", NT_VIRGULA,  ",", NT_NONE), $3);
    }
    | var {
        $$ = node_create("lista_variaveis", NT_LISTA_VARIAVEIS);
        node_add_child($$, $1);
    }
;

var:
    ID {
        $$ = node_create("var", NT_VAR);
        node_add_child($$, node_create_leaf("ID", NT_ID, $1, NT_NONE));
    }
    | ID indice {
        $$ = node_create("var", NT_VAR);
        node_add_children($$, 2, node_create_leaf("ID", NT_ID, $1, NT_NONE), $2);
    }
;

indice:
    indice ABRE_COLCHETE expressao FECHA_COLCHETE {
        $$ = node_create("indice", NT_INDICE);
        node_add_children($$, 4, 
            $1, node_create_leaf("ABRE_COLCHETE", NT_ABRE_COLCHETE, "[", NT_NONE),
            $3, node_create_leaf("FECHA_COLCHETE", NT_FECHA_COLCHETE, "]", NT_NONE)
        );
    }
    | indice ABRE_COLCHETE FECHA_COLCHETE {
        my_yyerror(&ERR_SYN_INDICE);
        $$ = node_create("indice", NT_INDICE);
        Node* err = node_create("ERR-SYN-INDICE", NT_ERROR);
        node_add_children($$, 4, 
            $1, node_create_leaf("ABRE_COLCHETE", NT_ABRE_COLCHETE, "[", NT_NONE),
            err, node_create_leaf("FECHA_COLCHETE", NT_FECHA_COLCHETE, "]", NT_NONE)
        );
    }
    | ABRE_COLCHETE expressao FECHA_COLCHETE {
        $$ = node_create("indice", NT_INDICE);
        node_add_children($$, 
            3, node_create_leaf("ABRE_COLCHETE", NT_ABRE_COLCHETE, "[", NT_NONE), 
            $2, node_create_leaf("FECHA_COLCHETE", NT_ABRE_COLCHETE, "]", NT_NONE)
        );
    }
    | ABRE_COLCHETE error FECHA_COLCHETE {
        my_yyerror(&ERR_SYN_INDICE);
        Node* err = node_create("ERR-SYN-INDICE", NT_ERROR);
        $$ = node_create("indice", NT_INDICE);
            node_add_children($$, 
            3, node_create_leaf("ABRE_COLCHETE", NT_ABRE_COLCHETE, "[", NT_NONE), 
            err, node_create_leaf("FECHA_COLCHETE", NT_FECHA_COLCHETE, "]", NT_NONE)
        );
    }
;

tipo:
    INTEIRO {
        $$ = node_create("tipo", NT_TIPO);
        node_add_child($$, node_create_leaf("INTEIRO", NT_INTEIRO, "inteiro", NT_NONE));
    }
    | FLUTUANTE {
        $$ = node_create("tipo", NT_TIPO);
        node_add_child($$, node_create_leaf("FLUTUANTE", NT_FLUTUANTE, "flutuante", NT_NONE));
    }
;

declaracao_funcao:
    tipo cabecalho {
        $$ = node_create("declaracao_funcao", NT_DECLARACAO_FUNCAO);
        node_add_children($$, 2, $1, $2);
    }
    | cabecalho {
        $$ = node_create("declaracao_funcao", NT_DECLARACAO_FUNCAO);
        node_add_child($$, $1);
    }
;

cabecalho:
    ID ABRE_PARENTESE lista_parametros FECHA_PARENTESE corpo FIM {
        $$ = node_create("cabecalho", NT_CABECALHO);
        node_add_children($$, 6,
            node_create_leaf("ID", NT_ID, $1, NT_NONE),
            node_create_leaf("ABRE_PARENTESE", NT_ABRE_PARENTESE, "(", NT_NONE),
            $3,
            node_create_leaf("FECHA_PARENTESE", NT_FECHA_PARENTESE, ")", NT_NONE),
            $5,
            node_create_leaf("FIM", NT_FIM, "fim", NT_NONE)
        );
    }
;

lista_parametros:
    lista_parametros VIRGULA parametro {
        $$ = node_create("lista_parametros", NT_LISTA_PARAMETROS);
        node_add_children($$, 2, $1, $3);
    }
    | parametro {
        $$ = node_create("lista_parametros", NT_LISTA_PARAMETROS);
        node_add_child($$, $1);
    }
    | vazio {
        $$ = node_create("lista_parametros", NT_LISTA_PARAMETROS);
        node_add_child($$, $1);
    }
;

parametro: 
    tipo DOIS_PONTOS ID {
        $$ = node_create("parametro", NT_PARAMETRO);
        node_add_children($$, 3,
            $1,
            node_create_leaf("DOIS_PONTOS", NT_DOIS_PONTOS, ":", NT_NONE),
            node_create_leaf("ID", NT_ID, $3, NT_NONE)
        );
    }
    | parametro ABRE_COLCHETE FECHA_COLCHETE {
        $$ = node_create("parametro", NT_PARAMETRO);
        node_add_children($$, 3,
            $1,
            node_create_leaf("ABRE_COLCHETE", NT_ABRE_COLCHETE, "[", NT_NONE),
            node_create_leaf("FECHA_COLCHETE", NT_FECHA_COLCHETE, "]", NT_NONE)
        );
    }
    | error DOIS_PONTOS ID {
        my_yyerror(&ERR_SYN_PARAMETRO);
        Node* err = node_create("ERR_SYN_PARAMETRO", NT_ERROR);
        $$ = node_create("parametro", NT_PARAMETRO);
        node_add_children($$, 3,
            err,
            node_create_leaf("DOIS_PONTOS", NT_DOIS_PONTOS, ":", NT_NONE),
            node_create_leaf("ID", NT_ID, $3, NT_NONE)
        );
    }
    | tipo DOIS_PONTOS error {
        my_yyerror(&ERR_SYN_PARAMETRO);
        Node* err = node_create("ERR_SYN_PARAMETRO", NT_ERROR);
        $$ = node_create("parametro", NT_PARAMETRO);
        node_add_children($$, 3,
            $1,
            node_create_leaf("DOIS_PONTOS", NT_DOIS_PONTOS, ":", NT_NONE),
            err
        );
        yyerrok; yyclearin;
    }
    | error DOIS_PONTOS error {
        my_yyerror(&ERR_SYN_PARAMETRO);
        Node* err = node_create("ERR_SYN_PARAMETRO", NT_ERROR);
        $$ = node_create("parametro", NT_PARAMETRO);
        node_add_children($$, 3,
            err,
            node_create_leaf("DOIS_PONTOS", NT_DOIS_PONTOS, ":", NT_NONE),
            err
        );
        yyerrok; yyclearin;
    }
    | parametro error FECHA_COLCHETE {
        my_yyerror(&ERR_SYN_PARAMETRO);
        Node* err = node_create("ERR_SYN_PARAMETRO", NT_ERROR);
        $$ = node_create("parametro", NT_PARAMETRO);
        node_add_children($$, 3,
            $1,
            err,
            node_create_leaf("FECHA_COLCHETE", NT_FECHA_COLCHETE, "]", NT_NONE)
        );
        yyerrok; yyclearin;
    }
    | parametro ABRE_COLCHETE error {
        my_yyerror(&ERR_SYN_PARAMETRO);
        Node* err = node_create("ERR_SYN_PARAMETRO", NT_ERROR);
        $$ = node_create("parametro", NT_PARAMETRO);
        node_add_children($$, 3,
            $1,
            node_create_leaf("ABRE_COLCHETE", NT_ABRE_COLCHETE, "[", NT_NONE),
            err
        );
        yyerrok; yyclearin;
    }
;

corpo:
    corpo acao {
        $$ = node_create("corpo", NT_CORPO);
        node_add_children($$, 2, $1, $2);
    }
    | vazio {
        $$ = node_create("corpo", NT_CORPO);
        node_add_child($$, $1);
    }
;

acao:
    expressao {
        $$ = node_create("acao", NT_ACAO);
        node_add_child($$, $1);
    }
    | declaracao_variaveis {
        $$ = node_create("acao", NT_ACAO);
        node_add_child($$, $1);
    }
    | se {
        $$ = node_create("acao", NT_ACAO);
        node_add_child($$, $1);
    }
    | repita {
        $$ = node_create("acao", NT_ACAO);
        node_add_child($$, $1);
    }
    | leia {
        $$ = node_create("acao", NT_ACAO);
        node_add_child($$, $1);
    }
    | escreva {
        $$ = node_create("acao", NT_ACAO);
        node_add_child($$, $1);
    }
    | retorna {
        $$ = node_create("acao", NT_ACAO);
        node_add_child($$, $1);
    }
;

se:
    SE expressao ENTAO corpo FIM{
        $$ = node_create("se", NT_SE);
        node_add_children($$, 5,
            node_create_leaf("SE", NT_SE, "se", NT_NONE), $2,
            node_create_leaf("ENTAO", NT_SE, "entao", NT_NONE), $4,
            node_create_leaf("FIM", NT_FIM, "fim", NT_NONE)
        );
    }
    | SE expressao ENTAO corpo SENAO corpo FIM {
        $$ = node_create("se", NT_SE);
        node_add_children($$, 7,
            node_create_leaf("SE", NT_SE, "se", NT_NONE), $2,
            node_create_leaf("ENTAO", NT_ENTAO, "entao", NT_NONE),$4,
            node_create_leaf("SENAO", NT_SENAO, "senao", NT_NONE), $6,
            node_create_leaf("FIM", NT_FIM, "fim", NT_NONE)
        );
    }
    | error expressao ENTAO corpo FIM {
        my_yyerror(&ERR_SYN_SE);
        Node* err = node_create("ERR_SYN_SE", NT_ERROR);
        $$ = node_create("se", NT_SE);
        node_add_children($$, 5,
            err, $2,
            node_create_leaf("ENTAO", NT_ENTAO, "entao", NT_NONE), $4,
            node_create_leaf("FIM", NT_FIM, "fim", NT_NONE)
        );
        yyerrok;
    }
    | SE expressao error corpo FIM {
        my_yyerror(&ERR_SYN_SE);
        Node* err = node_create("ERR_SYN_SE", NT_ERROR);
        $$ = node_create("se", NT_SE);
        node_add_children($$, 5,
            node_create_leaf("SE", NT_SE, "se", NT_NONE), err,
            node_create_leaf("ENTAO", NT_ENTAO, "entao", NT_NONE), $4,
            node_create_leaf("FIM", NT_FIM, "fim", NT_NONE)
        );
        yyerrok;
    }
    | error expressao ENTAO corpo SENAO corpo FIM {
        my_yyerror(&ERR_SYN_SE);
        Node* err = node_create("ERR_SYN_SE", NT_ERROR);
        $$ = node_create("se", NT_SE);
        node_add_children($$, 7,
            err, $2,
            node_create_leaf("ENTAO", NT_ENTAO, "entao", NT_NONE), $4,
            node_create_leaf("SENAO", NT_ENTAO, "senao", NT_NONE), $6,
            node_create_leaf("FIM", NT_FIM, "fim", NT_NONE)
        );
        yyerrok;
    }
    | SE expressao error corpo SENAO corpo FIM {
        my_yyerror(&ERR_SYN_SE);
        Node* err = node_create("ERR_SYN_SE", NT_ERROR);
        $$ = node_create("se", NT_SE);
        node_add_children($$, 7,
            node_create_leaf("SE", NT_SE, "se", NT_NONE), err,
            node_create_leaf("ENTAO", NT_ENTAO, "entao", NT_NONE), $4,
            node_create_leaf("SENAO", NT_SENAO, "senao", NT_NONE), $6,
            node_create_leaf("FIM", NT_FIM, "fim", NT_NONE)
        );
        yyerrok;
    }
    | SE expressao ENTAO corpo error corpo FIM {
        my_yyerror(&ERR_SYN_SE);
        Node* err = node_create("ERR_SYN_SE", NT_ERROR);
        $$ = node_create("se", NT_SE);
        node_add_children($$, 7,
            node_create_leaf("SE", NT_SE, "se", NT_NONE), $2,
            node_create_leaf("ENTAO", NT_ENTAO, "entao", NT_NONE), $4,
            err, $6,
            node_create_leaf("FIM", NT_FIM, "fim", NT_NONE)
        );
        yyerrok;
    }
    | SE expressao ENTAO corpo SENAO corpo {
        my_yyerror(&ERR_SYN_SE);
        Node* err = node_create("ERR_SYN_SE", NT_ERROR);
        $$ = node_create("se", NT_SE);
        node_add_children($$, 6,
            node_create_leaf("SE", NT_SE, "se", NT_NONE), $2,
            node_create_leaf("ENTAO", NT_ENTAO, "entao", NT_NONE), $4,
            node_create_leaf("SENAO", NT_SENAO, "senao", NT_NONE), $6
        );
        yyerrok;
    }
;

repita:
    REPITA corpo ATE expressao {
        $$ = node_create("repita", NT_REPITA);
        node_add_children($$, 4,
            node_create_leaf("REPITA", NT_REPITA, "repita", NT_NONE), $2,
            node_create_leaf("ATE", NT_ATE, "ate", NT_NONE), $4
        );
    }
    | error corpo ATE expressao {
        my_yyerror(&ERR_SYN_REPITA);
        Node* err = node_create("ERR_SYN_REPITA", NT_ERROR);
        $$ = node_create("repita", NT_REPITA);
        node_add_children($$, 4,
            err, $2,
            node_create_leaf("ATE", NT_ATE, "ate", NT_NONE), $4
        );
        yyerrok;
    }
    | REPITA corpo error expressao {
        my_yyerror(&ERR_SYN_REPITA);
        Node* err = node_create("ERR_SYN_REPITA", NT_ERROR);
        $$ = node_create("repita", NT_REPITA);
        node_add_children($$, 4,
            node_create_leaf("REPITA", NT_REPITA, "repita", NT_NONE), $2,
            err, $4
        );
        yyerrok;
    }
;

atribuicao:
    var ATRIBUICAO expressao {
        $$ = node_create("atribuicao", NT_ATRIBUICAO);
        node_add_children($$, 3, $1, node_create_leaf("ATRIBUICAO", NT_ATRIBUICAO, ":=", NT_NONE), $3);
    }
;

leia:
    LEIA ABRE_PARENTESE var FECHA_PARENTESE {
        $$ = node_create("leia", NT_LEIA);
        node_add_children($$, 4,
            node_create_leaf("LEIA", NT_LEIA, "leia", NT_NONE),
            node_create_leaf("ABRE_PARENTESE", NT_ABRE_PARENTESE, "(", NT_NONE), $3,
            node_create_leaf("FECHA_PARENTESE", NT_FECHA_PARENTESE, ")", NT_NONE)
        );
    }
    | LEIA ABRE_PARENTESE error FECHA_PARENTESE {
        my_yyerror(&ERR_SYN_LEIA);
        Node* err = node_create("ERR_SYN_LEIA", NT_ERROR);
        $$ = node_create("leia", NT_LEIA);
        node_add_children($$, 4,
            node_create_leaf("LEIA", NT_LEIA, "leia", NT_NONE),
            node_create_leaf("ABRE_PARENTESE", NT_ABRE_PARENTESE, "(", NT_NONE), err,
            node_create_leaf("FECHA_PARENTESE", NT_FECHA_PARENTESE, ")", NT_NONE)
        );
        yyerrok;
    }
;

escreva:
    ESCREVA ABRE_PARENTESE expressao FECHA_PARENTESE {
        $$ = node_create("escreva", NT_ESCREVA);
        node_add_children($$, 4,
            node_create_leaf("ESCREVA", NT_ESCREVA, "escreva", NT_NONE),
            node_create_leaf("ABRE_PARENTESE", NT_ABRE_PARENTESE, "(", NT_NONE), $3,
            node_create_leaf("FECHA_PARENTESE", NT_FECHA_PARENTESE, ")", NT_NONE)
        );
    }
;

retorna:
    RETORNA ABRE_PARENTESE expressao FECHA_PARENTESE {
        $$ = node_create("retorna", NT_RETORNA);
        node_add_children($$, 4,
            node_create_leaf("RETORNA", NT_RETORNA, "retorna", NT_NONE),
            node_create_leaf("ABRE_PARENTESE", NT_ABRE_PARENTESE, "(", NT_NONE), $3,
            node_create_leaf("FECHA_PARENTESE", NT_FECHA_PARENTESE, ")", NT_NONE)
        );
    }
;

expressao:
    expressao_logica{
        $$ = node_create("expressao", NT_EXPRESSAO);
        node_add_child($$, $1);
    }
    | atribuicao {
        $$ = node_create("expressao", NT_EXPRESSAO);
        node_add_child($$, $1);
    }
;

expressao_logica:
    expressao_simples {
        $$ = node_create("expressao_logica", NT_EXPRESSAO_LOGICA);
        node_add_child($$, $1);
    }
    | expressao_logica operador_logico expressao_simples {
        $$ = node_create("expressao_logica", NT_EXPRESSAO_LOGICA);
        node_add_children($$, 3, $1, $2, $3);    
    }
;

expressao_simples:
    expressao_aditiva {
        $$ = node_create("expressao_simples", NT_EXPRESSAO_SIMPLES);
        node_add_child($$, $1);
    }
    | expressao_simples operador_relacional expressao_aditiva {
        $$ = node_create("expressao_simples", NT_EXPRESSAO_SIMPLES);
        node_add_children($$, 3, $1, $2, $3);
    }
;

expressao_aditiva:
    expressao_multiplicativa {
        $$ = node_create("expressao_aditiva", NT_EXPRESSAO_ADITIVA);
        node_add_child($$, $1);
    }
    | expressao_aditiva operador_soma expressao_multiplicativa {
        $$ = node_create("expressao_aditiva", NT_EXPRESSAO_ADITIVA);
        node_add_children($$, 3, $1, $2, $3);
    }
;

expressao_multiplicativa:
    expressao_unaria {
        $$ = node_create("expressao_multiplicativa", NT_EXPRESSAO_MULTIPLICATIVA);
        node_add_child($$, $1);
    }
    | expressao_multiplicativa operador_multiplicacao expressao_unaria {
        $$ = node_create("expressao_multiplicativa", NT_EXPRESSAO_MULTIPLICATIVA);
        node_add_children($$, 3, $1, $2, $3);
    }
;

expressao_unaria:
    fator {
        $$ = node_create("expressao_unaria", NT_EXPRESSAO_UNARIA);
        node_add_child($$, $1);
    }
    | operador_soma fator {
        $$ = node_create("expressao_unaria", NT_EXPRESSAO_UNARIA);
        node_add_children($$, 2, $1, $2);
    }
    | operador_negacao fator {
        $$ = node_create("expressao_unaria", NT_EXPRESSAO_UNARIA);
        node_add_children($$, 2, $1, $2);
    }
;

operador_relacional:
    MENOR { $$ = node_create_leaf("MENOR", NT_MENOR, "<", NT_NONE); }
    | MAIOR { $$ = node_create_leaf("MAIOR", NT_MAIOR, ">", NT_NONE); }
    | IGUAL { $$ = node_create_leaf("IGUAL", NT_IGUAL, "=", NT_NONE); }
    | DIFERENTE { $$ = node_create_leaf("DIFERENTE", NT_DIFERENTE, "<>", NT_NONE); }
    | MENOR_IGUAL { $$ = node_create_leaf("MENOR_IGUAL", NT_MENOR_IGUAL, "<=", NT_NONE); }
    | MAIOR_IGUAL { $$ = node_create_leaf("MAIOR_IGUAL", NT_MAIOR_IGUAL, ">=", NT_NONE); }
;

operador_soma:
    MAIS { $$ = node_create_leaf("MAIS", NT_MAIS, "+", NT_NONE); }
    | MENOS { $$ = node_create_leaf("MENOS", NT_MENOS, "-", NT_NONE); }
;

operador_logico:
    E { $$ = node_create_leaf("E", NT_E, "&&", NT_NONE); }
    | OU { $$ = node_create_leaf("OU", NT_OU, "||", NT_NONE); }
;

operador_negacao:
    NAO { $$ = node_create_leaf("NAO", NT_NAO, "!", NT_NONE); }
;

operador_multiplicacao:
    VEZES { $$ = node_create_leaf("VEZES", NT_VEZES, "*", NT_NONE); }
    | DIVIDE { $$ = node_create_leaf("DIVIDE", NT_DIVIDE, "/", NT_NONE); }
;

fator:
    ABRE_PARENTESE expressao FECHA_PARENTESE {
        $$ = node_create("fator", NT_FATOR);
        node_add_children($$, 3,
            node_create_leaf("ABRE_PARENTESE", NT_ABRE_PARENTESE, "(", NT_NONE), $2,
            node_create_leaf("FECHA_PARENTESE", NT_FECHA_PARENTESE, ")", NT_NONE)
        );
    }
    | var {
        $$ = node_create("fator", NT_FATOR);
        node_add_child($$, $1);
    }
    | chamada_funcao {
        $$ = node_create("fator", NT_FATOR);
        node_add_child($$, $1);
    }
    | numero {
        $$ = node_create("fator", NT_FATOR);
        node_add_child($$, $1);
    }
    | ABRE_PARENTESE error FECHA_PARENTESE {}
;

numero:
    NUM_INTEIRO {
        $$ = node_create("numero", NT_NUMERO);
        node_add_child($$, node_create_leaf("NUM_INTEIRO", NT_NUM_INTEIRO, $1, NT_NONE));
    }
    | NUM_PONTO_FLUTUANTE {
        $$ = node_create("numero", NT_NUMERO);
        node_add_child($$, node_create_leaf("NUM_PONTO_FLUTUANTE", NT_NUM_PONTO_FLUTUANTE, $1, NT_NONE));
    }
    | NUM_NOTACAO_CIENTIFICA {
        $$ = node_create("numero", NT_NUMERO);
        node_add_child($$, node_create_leaf("NUM_NOTACAO_CIENTIFICA", NT_NUM_NOTACAO_CIENTIFICA, $1, NT_NONE));
    }
;

chamada_funcao:
    ID ABRE_PARENTESE lista_argumentos FECHA_PARENTESE {
        $$ = node_create("chamada_funcao", NT_CHAMADA_FUNCAO);
        node_add_children($$, 4,
            node_create_leaf("ID", NT_ID, $1, NT_NONE),
            node_create_leaf("ABRE_PARENTESE", NT_ABRE_PARENTESE, "(", NT_NONE),
            $3,
            node_create_leaf("FECHA_PARENTESE", NT_FECHA_PARENTESE, ")", NT_NONE)
        );
    }
;

lista_argumentos:
    lista_argumentos VIRGULA expressao {
        $$ = node_create("lista_argumentos", NT_LISTA_ARGUMENTOS);
        node_add_children($$, 3, $1, node_create_leaf("VIRGULA", NT_VIRGULA, ",", NT_NONE), $3);
    }
    | expressao {
        $$ = node_create("lista_argumentos", NT_LISTA_ARGUMENTOS);
        node_add_child($$, $1);
    }
    | vazio {
        $$ = node_create("lista_argumentos", NT_LISTA_ARGUMENTOS);
        node_add_child($$, $1);
    }
    | error VIRGULA expressao {
        my_yyerror(&ERR_SYN_LISTA_ARGUMENTOS);
        Node* err = node_create("ERR_SYN_LISTA_ARGUMENTOS", NT_ERROR);
        $$ = node_create("lista_argumentos", NT_LISTA_ARGUMENTOS);
        node_add_children($$, 3, err, node_create_leaf("VIRGULA", NT_VIRGULA, ",", NT_NONE), $3);
        yyerrok;
    }
;

vazio: 
    { $$ = node_create("vazio", NT_VAZIO); }
;

%%

int yyerror(char* s){ }

static int
yyreport_syntax_error (const yypcontext_t *ctx){
    success = false;
    if(ctx->yytoken == 0){ // Se o token que deu erro for EOF
        my_yyerror(&ERR_SYN_EOF_INESPERADO);
    }
    // Senão, não faz nada, pois a regra tratará o erro
}


void my_yyerror(const Error* err){
    if(check_key)
        printf("%s\n", err->cod);
    else{
        if(err->type == 'E')
            printf("\033[1;31mLinha %d: %s %s\033[0m\n", yylineno, err->msg, yytext); // Vermelho
        else if(err->type == 'W')
            printf("\033[1;33m%s\033[0m\n", err->msg); // Amarelo
        else
            printf("Linha %d: %s (%s)\n", yylineno, err->msg, yytext);
    }
}