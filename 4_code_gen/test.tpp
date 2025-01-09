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


	
inteiro principal()
	flutuante: g[2]
	inteiro: h[1]
	g[0] := 2
	h[0] := 1
	leia(g[1])
	escreva(g[0])
	escreva(h[0])
	escreva(g[1])
	retorna(0)
fim