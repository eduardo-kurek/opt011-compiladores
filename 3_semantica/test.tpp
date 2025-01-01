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

inteiro: var

var := 10
var := 4 + var

inteiro func(inteiro: a, inteiro: b)
	retorna(a + b)
fim

principal(inteiro: a, flutuante: b)
	inteiro: x[10][50], y, z, w[50]
	se (x > 0 + 2 * 1) && (x < 10 || x > 10) então
		retorna(func(func(a:=1, 2), (10 + 2)))
	fim

	repita
		escreva(a+1)
		leia(z)
		z := z + 1
	até (z < 10 || z > 10 + 1 && (x:=1) > func(a+1, b/x[9][49]))
fim