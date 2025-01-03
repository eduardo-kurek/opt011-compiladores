inteiro principal()
	flutuante: a, b
	a := 5.5
	b := a + 2
	se a < b || (1 = 1) então
		retorna(a)
	fim
	retorna(a * b)
fim

{inteiro principal()
	flutuante: a, b
	a := 5.5
	b := a + 2

	inteiro: count
	count := 0

	repita
		b := b + 0.3
		count := count + 1
	até a >= b

	retorna(count)
fim}