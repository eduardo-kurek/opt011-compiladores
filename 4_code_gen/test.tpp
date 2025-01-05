inteiro func(inteiro: a, flutuante: b)
	inteiro: c
	c := a + b
	retorna(a - b * c)
fim

inteiro principal()
	retorna(func(100.5, 90.5))
fim