inteiro: n
flutuante: x, y, z

inteiro fatorial(inteiro: n, flutuante: m)
	{NOTAÇÃO CIENTÍFICA}
	{WARNING: 'm' ESTÁ RECEBENDO VALORES DE TIPOS DIFERENTES}
	m := 5
	
	se n>0 então
		retorna(n)
	senão
		repita 
			flutuante: p
		até n = 0
	fim
	
	z := 1.9 {SEM ERRO, FOI INICIALIZADO}
	z := z+1 {ERRO, ID NAO FOI INICIALIZADO}

	{WARNING DE RETORNO: PASSANDO TIPO DIFERENTE}
	retorna(m)
fim

inteiro principal()
	leia(n)
	escreva(fatorial(1, 1.0)) {TIPOS DOS PARAMETROS DIFERENTES, TESTAR E VER SE ACUSA UM WARNING}
fim

{VERIFICAR SE A VARIÁVEL 'a' ESTÁ NO ESCOPO 'global'}

inteiro: a
flutuante: b

inteiro fatorial2(inteiro: fat, flutuante: fat2, inteiro: fat3)
	{VERIFICAÇÃO DE ATRIBUIÇÃO}

	a := 1
	{WARNING: 'a' = 'inteiro' -> ESTÁ RECEBENDO 'flutuante'}
	
	{SEM WARNING}
	

	{CHAMADA DE FUNÇÃO UMA DENTRO DA OUTRA!}
	escreva(fatorial(fatorial(1, 1.0), 1.0))

	a := fatorial(1, 1.0)

	{WARNING: VARIÁVEL 'b' é 'flutuante' E A FUNÇÃO È 'inteiro'}
	b := fatorial(1, 1.0)

	{CHAMADA DE FUNÇÃO NORMAL}
	fatorial(1, 1.0)
fim

{WARNING}

{WARNING: ID m está recebendo valores incompatíveis: flutuante -> inteiro}
{WARNING: função fatorial está retornando tipos incompatíveis: inteiro -> flutuante}
{WARNING: ID a está recebendo valores incompatíveis: inteiro -> flutuante}
{WARNING: ID b está recebendo valores incompatíveis: flutuante -> inteiro}

{RESULTADO DA TABELA DE SIMBOLOS CORRETA!}

{

Linha 7: Atribuição de tipos diferentes. Número. 5 do tipo inteiro para flutuante
Linha 18: Atribuição de tipos diferentes. Expressão.
Linha 21: Função com tipo de retorno diferente do esperado.
Linha 24: Função com tipo de retorno diferente do esperado. principal
Linha 46: Atribuição de tipos diferentes. Coerção implícita de valor de retorno.
Linha 34: Função com tipo de retorno diferente do esperado. fatorial2
Linha 34: Função declarada e não utilizada. fatorial2
Linha 2: Variável declarada e não inicializada. 'y'
Linha 2: Variável declarada e não inicializada. 'x'
Linha 13: Variável declarada e não inicializada. 'p'
Linha 1: Variável declarada e não utilizada. 'n'
Linha 2: Variável declarada e não utilizada. 'y'
Linha 2: Variável declarada e não utilizada. 'x'
Linha 13: Variável declarada e não utilizada. 'p'
Linha 31: Variável declarada e não utilizada. 'a'
Linha 32: Variável declarada e não utilizada. 'b'
Linha 34: Variável declarada e não utilizada. 'fat'
Linha 34: Variável declarada e não utilizada. 'fat2'
Linha 34: Variável declarada e não utilizada. 'fat3'

}