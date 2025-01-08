{inteiro: g

inteiro principal()
	inteiro: a[3][3], i, j, count
	count := 0
	i := 0
	repita
		j := 0
		repita
			a[i][j] := count + g
			count := count + 1
			j := j + 1
		até j < 3
		i := i + 1
	até i < 3

	i := 0
	repita
		j := 0
		repita
			escreva(a[i][j])
			j := j + 1
		até j < 3
		i := i + 1
	até i < 3

	retorna(0)
fim }

flutuante: g
g := 2.53

teste(flutuante: arg)
	g := g + arg
	escreva(g)
fim
	
inteiro principal() 
	flutuante: g
	g := 1.92
	escreva(g)
	teste(g)
	retorna(0)
fim