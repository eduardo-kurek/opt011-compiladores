inteiro principal()
	inteiro: a[10], i

	i := 0
	repita
		a[i] := i * 3
		i := i + 1
	até i < 10

	i := 0
	repita
		escreva(a[i])
		i := i + 1
	até i < 10

	retorna(0)
fim 