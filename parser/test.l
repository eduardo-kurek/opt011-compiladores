%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "test.tab.h"
void showError();
void assignValue();

%}

NUM_INTEIRO [0-9]+
NUM_PONTO_FLUTUANTE [-]?[0-9]+(\.([0-9]+)?)
NUM_NOTACAO_CIENTIFICA [-]?[0-9]+(\.([0-9]+)?)
ID [a-zA-ZáÁãÃàÀéÉíÍóÓõÕ][a-zA-ZáÁãÃàÀéÉíÍóÓõÕ0-9_]*

%%

\{([^{}]|\n)*\} /* IGNORA COMENTÁRIOS */ ;

\+ return MAIS;
- return MENOS;
\* return VEZES;
\/ return DIVIDE;
\: return DOIS_PONTOS;
, return VIRGULA;
\< return MENOR;
> return MAIOR;
= return IGUAL;
\<> return DIFERENTE;
\<= return MENOR_IGUAL;
>= return MAIOR_IGUAL;
&& return E;
"||" return OU;
! return NAO;
\( return ABRE_PARENTESE;
\) return FECHA_PARENTESE;
\[ return ABRE_COLCHETE;
\] return FECHA_COLCHETE;
se return SE;
então return ENTAO;
senão return SENAO;
fim return FIM;
repita return REPITA;
até return ATE;
:= return ATRIBUICAO;
leia return LEIA;
escreva return ESCREVA;
retorna return RETORNA;
inteiro return INTEIRO;
flutuante return FLUTUANTE;
{NUM_INTEIRO} { assignValue(); return NUM_INTEIRO; }
{NUM_PONTO_FLUTUANTE} { assignValue(); return NUM_PONTO_FLUTUANTE; }
{NUM_NOTACAO_CIENTIFICA} { assignValue(); return NUM_NOTACAO_CIENTIFICA; }
{ID} { assignValue(); return ID; }

[ \t] /* IGNORA ESPAÇOS EM BRANCO */
\r\n|\n  /* IGNORA QUEBRAS DE LINHA */
.|ç showError();

%%

void showError(){
    printf("Lex input error\n");
}

void assignValue(){
    if(strlen(yytext) > 500){
        printf("Value %s to long", yytext);
        return;
    }
    strncpy(yylval.value, yytext, strlen(yytext) + 1);
}