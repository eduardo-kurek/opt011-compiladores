{Aviso: Variável 'a' já declarada anteriormente com o tipo 'inteiro'}
{Aviso: Variável 'b' declarada e inicializada, mas não utilizada}
{Aviso: Variável 'a' declarada e não inicializada}
{Erro: Função 'principal' deveria retornar 'inteiro', mas retorna 'vazio'}

inteiro: a

a := 10

inteiro func()
	inteiro: b
	b := 1
	retorna(b)
fim

inteiro principal()
	flutuante: b
	inteiro: c

	b := a + 1.0
	c := func() + b
	retorna(c)
fim
