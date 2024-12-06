%{
#include <stdio.h>
#include "tree.h"

int yylex();
int yyerror(char* s);
void adjustConsole();
int handleArguments(int argc, char* argv[]);
void redirectStdin(const char* fileName);

Node* syntax_tree = NULL;
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

%%

programa:
    lista_declaracoes {
        $$ = node_create("programa");
        node_add_child($$, $1);
        syntax_tree = $$;
    }
;

lista_declaracoes:
    lista_declaracoes declaracao {
        $$ = node_create("lista_declaracoes");
        node_add_children($$, 2, $1, $2);
    }
    | declaracao {
        $$ = node_create("lista_declaracoes");
        node_add_child($$, $1);
    }
;

declaracao: 
    declaracao_funcao {
        $$ = node_create("declaracao");
        node_add_child($$, $1);
    }
    | declaracao_variaveis {
        $$ = node_create("declaracao");
        node_add_child($$, $1);
    }
    | inicializacao_variaveis {
        $$ = node_create("declaracao");
        node_add_child($$, $1);
    }
;

declaracao_variaveis:
    tipo DOIS_PONTOS lista_variaveis {
        $$ = node_create("declaracao_variaveis");
        node_add_children($$, 3, $1, node_create_leaf("DOIS_PONTOS", ":"), $3);
    }
;

inicializacao_variaveis:
    atribuicao {
        $$ = node_create("inicializacao_variaveis");
        node_add_child($$, $1);
    }
;

lista_variaveis:
    lista_variaveis VIRGULA var {
        $$ = node_create("lista_variaveis");
        node_add_children($$, 3, $1, node_create_leaf("VIRGULA", ","), $3);
    }
    | var {
        $$ = node_create("lista_variaveis");
        node_add_child($$, $1);
    }
;

var:
    ID {
        $$ = node_create("var");
        node_add_child($$, node_create_leaf("ID", $1));
    }
    | ID indice {
        $$ = node_create("var");
        node_add_children($$, 2, node_create_leaf("ID", $1), $2);
    }
;

indice:
    indice ABRE_COLCHETE expressao FECHA_COLCHETE {
        $$ = node_create("indice");
        node_add_children($$, 4, 
            $1, node_create_leaf("ABRE_COLCHETE", "["),
            $3, node_create_leaf("FECHA_COLCHETE", "]")
        );
    }
    | ABRE_COLCHETE expressao FECHA_COLCHETE {
        $$ = node_create("indice");
        node_add_children($$, 
            3, node_create_leaf("ABRE_COLCHETE", "["), 
            $2, node_create_leaf("FECHA_COLCHETE", "]")
        );
    }
;

tipo:
    INTEIRO {
        $$ = node_create("tipo");
        node_add_child($$, node_create_leaf("INTEIRO", "inteiro"));
    }
    | FLUTUANTE {
        $$ = node_create("tipo");
        node_add_child($$, node_create_leaf("FLUTUANTE", "flutuante"));
    }
;

declaracao_funcao:
    tipo cabecalho {
        $$ = node_create("declaracao_funcao");
        node_add_children($$, 2, $1, $2);
    }
    | cabecalho {
        $$ = node_create("declaracao_funcao");
        node_add_child($$, $1);
    }
;

cabecalho:
    ID ABRE_PARENTESE lista_parametros FECHA_PARENTESE corpo FIM {
        $$ = node_create("cabecalho");
        node_add_children($$, 6,
            node_create_leaf("ID", $1),
            node_create_leaf("ABRE_PARENTESE", "("),
            $3,
            node_create_leaf("FECHA_PARENTESE", ")"),
            $5,
            node_create_leaf("FIM", "fim")
        );
    }
;

lista_parametros:
    lista_parametros VIRGULA parametro {
        $$ = node_create("lista_parametros");
        node_add_children($$, 2, $1, $3);
    }
    | parametro {
        $$ = node_create("lista_parametros");
        node_add_child($$, $1);
    }
    | vazio {
        $$ = node_create("lista_parametros");
        node_add_child($$, $1);
    }
;

parametro: 
    tipo DOIS_PONTOS ID {
        $$ = node_create("parametro");
        node_add_children($$, 3,
            $1,
            node_create_leaf("DOIS_PONTOS", ":"),
            node_create_leaf("ID", $3)
        );
    }
    | parametro ABRE_COLCHETE FECHA_COLCHETE {
        $$ = node_create("parametro");
        node_add_children($$, 3,
            $1,
            node_create_leaf("ABRE_COLCHETE", "["),
            node_create_leaf("FECHA_COLCHETE", "]")
        );
    }
;

corpo:
    corpo acao {
        $$ = node_create("corpo");
        node_add_children($$, 2, $1, $2);
    }
    | vazio {
        $$ = node_create("corpo");
        node_add_child($$, $1);
    }
;

acao:
    expressao {
        $$ = node_create("acao");
        node_add_child($$, $1);
    }
    | declaracao_variaveis {
        $$ = node_create("acao");
        node_add_child($$, $1);
    }
    | se {
        $$ = node_create("acao");
        node_add_child($$, $1);
    }
    | repita {
        $$ = node_create("acao");
        node_add_child($$, $1);
    }
    | leia {
        $$ = node_create("acao");
        node_add_child($$, $1);
    }
    | escreva {
        $$ = node_create("acao");
        node_add_child($$, $1);
    }
    | retorna {
        $$ = node_create("acao");
        node_add_child($$, $1);
    }
;

se:
    SE expressao ENTAO corpo FIM{
        $$ = node_create("se");
        node_add_children($$, 5,
            node_create_leaf("SE", "se"), $2,
            node_create_leaf("ENTAO", "entao"), $4,
            node_create_leaf("FIM", "fim")
        );
    }
    | SE expressao ENTAO corpo SENAO corpo FIM {
        $$ = node_create("se");
        node_add_children($$, 7,
            node_create_leaf("SE", "se"), $2,
            node_create_leaf("ENTAO", "entao"),$4,
            node_create_leaf("SENAO", "senao"), $6,
            node_create_leaf("FIM", "fim")
        );
    }
;

repita:
    REPITA corpo ATE expressao {
        $$ = node_create("repita");
        node_add_children($$, 4,
            node_create_leaf("REPITA", "repita"), $2,
            node_create_leaf("ATE", "ate"), $4
        );
    }
;

atribuicao:
    var ATRIBUICAO expressao {
        $$ = node_create("atribuicao");
        node_add_children($$, 3, $1, node_create_leaf("ATRIBUICAO", ":="), $3);
    }
;

leia:
    LEIA ABRE_PARENTESE var FECHA_PARENTESE {
        $$ = node_create("leia");
        node_add_children($$, 4,
            node_create_leaf("LEIA", "leia"),
            node_create_leaf("ABRE_PARENTESE", "("), $3,
            node_create_leaf("FECHA_PARENTESE", ")")
        );
    }
;

escreva:
    ESCREVA ABRE_PARENTESE expressao FECHA_PARENTESE {
        $$ = node_create("escreva");
        node_add_children($$, 4,
            node_create_leaf("ESCREVA", "escreva"),
            node_create_leaf("ABRE_PARENTESE", "("), $3,
            node_create_leaf("FECHA_PARENTESE", ")")
        );
    }
;

retorna:
    RETORNA ABRE_PARENTESE expressao FECHA_PARENTESE {
        $$ = node_create("retorna");
        node_add_children($$, 4,
            node_create_leaf("RETORNA", "retorna"),
            node_create_leaf("ABRE_PARENTESE", "("), $3,
            node_create_leaf("FECHA_PARENTESE", ")")
        );
    }
;

expressao:
    expressao_logica{
        $$ = node_create("expressao");
        node_add_child($$, $1);
    }
    | atribuicao {
        $$ = node_create("expressao");
        node_add_child($$, $1);
    }
;

expressao_logica:
    expressao_simples {
        $$ = node_create("expressao_logica");
        node_add_child($$, $1);
    }
    | expressao_logica operador_logico expressao_simples {
        $$ = node_create("expressao_logica");
        node_add_children($$, 3, $1, $2, $3);    
    }
;

expressao_simples:
    expressao_aditiva {
        $$ = node_create("expressao_simples");
        node_add_child($$, $1);
    }
    | expressao_simples operador_relacional expressao_aditiva {
        $$ = node_create("expressao_simples");
        node_add_children($$, 3, $1, $2, $3);
    }
;

expressao_aditiva:
    expressao_multiplicativa {
        $$ = node_create("expressao_aditiva");
        node_add_child($$, $1);
    }
    | expressao_aditiva operador_soma expressao_multiplicativa {
        $$ = node_create("expressao_aditiva");
        node_add_children($$, 3, $1, $2, $3);
    }
;

expressao_multiplicativa:
    expressao_unaria {
        $$ = node_create("expressao_multiplicativa");
        node_add_child($$, $1);
    }
    | expressao_multiplicativa operador_multiplicacao expressao_unaria {
        $$ = node_create("expressao_multiplicativa");
        node_add_children($$, 3, $1, $2, $3);
    }
;

expressao_unaria:
    fator {
        $$ = node_create("expressao_unaria");
        node_add_child($$, $1);
    }
    | operador_soma fator {
        $$ = node_create("expressao_unaria");
        node_add_children($$, 2, $1, $2);
    }
    | operador_negacao fator {
        $$ = node_create("expressao_unaria");
        node_add_children($$, 2, $1, $2);
    }
;

operador_relacional:
    MENOR { $$ = node_create_leaf("MENOR", "<"); }
    | MAIOR { $$ = node_create_leaf("MAIOR", ">"); }
    | IGUAL { $$ = node_create_leaf("IGUAL", "="); }
    | DIFERENTE { $$ = node_create_leaf("DIFERENTE", "<>"); }
    | MENOR_IGUAL { $$ = node_create_leaf("MENOR_IGUAL", "<="); }
    | MAIOR_IGUAL { $$ = node_create_leaf("MAIOR_IGUAL", ">="); }
;

operador_soma:
    MAIS { $$ = node_create_leaf("MAIS", "+"); }
    | MENOS { $$ = node_create_leaf("MENOS", "-"); }
;

operador_logico:
    E { $$ = node_create_leaf("E", "&&"); }
    | OU { $$ = node_create_leaf("OU", "||"); }
;

operador_negacao:
    NAO { $$ = node_create_leaf("NAO", "!"); }
;

operador_multiplicacao:
    VEZES { $$ = node_create_leaf("VEZES", "*"); }
    | DIVIDE { $$ = node_create_leaf("DIVIDE", "/"); }
;

fator:
    ABRE_PARENTESE expressao FECHA_PARENTESE {
        $$ = node_create("fator");
        node_add_children($$, 3,
            node_create_leaf("ABRE_PARENTESE", "("), $2,
            node_create_leaf("FECHA_PARENTESE", ")")
        );
    }
    | var {
        $$ = node_create("fator");
        node_add_child($$, $1);
    }
    | chamada_funcao {
        $$ = node_create("fator");
        node_add_child($$, $1);
    }
    | numero {
        $$ = node_create("fator");
        node_add_child($$, $1);
    }
;

numero:
    NUM_INTEIRO {
        $$ = node_create("numero");
        node_add_child($$, node_create_leaf("NUM_INTEIRO", $1));
    }
    | NUM_PONTO_FLUTUANTE {
        $$ = node_create("numero");
        node_add_child($$, node_create_leaf("NUM_PONTO_FLUTUANTE", $1));
    }
    | NUM_NOTACAO_CIENTIFICA {
        $$ = node_create("numero");
        node_add_child($$, node_create_leaf("NUM_NOTACAO_CIENTIFICA", $1));
    }
;

chamada_funcao:
    ID ABRE_PARENTESE lista_argumentos FECHA_PARENTESE {
        $$ = node_create("chamada_funcao");
        node_add_children($$, 4,
            node_create_leaf("ID", $1),
            node_create_leaf("ABRE_PARENTESE", "("),
            $3,
            node_create_leaf("FECHA_PARENTESE", ")")
        );
    }
;

lista_argumentos:
    lista_argumentos VIRGULA expressao {
        $$ = node_create("lista_argumentos");
        node_add_children($$, 3, $1, node_create_leaf("VIRGULA", ","), $3);
    }
    | expressao {
        $$ = node_create("lista_argumentos");
        node_add_child($$, $1);
    }
    | vazio {
        $$ = node_create("lista_argumentos");
        node_add_child($$, $1);
    }
;

vazio: 
    { $$ = node_create("vazio"); }
;

%%

int yyerror(char* s){
    printf("Syntax error on line %s\n", s);
    return 0;
}