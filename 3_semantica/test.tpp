{Aviso: Variável 'a' já declarada anteriormente com o tipo 'inteiro'}
{Aviso: Variável 'b' declarada e inicializada, mas não utilizada}
{Aviso: Variável 'a' declarada e não inicializada}
{Erro: Função 'principal' deveria retornar 'inteiro', mas retorna 'vazio'}

{inteiro: a

a := 10

inteiro func()
	inteiro: b, c[2]
	b := 1
	c[0] := 2
	retorna(b / c[0])
fim

inteiro principal()
	flutuante: b
	inteiro: c

	b := a + 1.0
	c := func() + b
	retorna(c)
fim
}

{inteiro principal()
	inteiro: a, b[2][3]
	a := 10
	b[0][0] := 1 * 2 / (8 - -3) + 4
	retorna(a)
fim}

inteiro func(inteiro: a, flutuante: b)
	retorna(a + b)
fim

inteiro principal()
	func()
fim