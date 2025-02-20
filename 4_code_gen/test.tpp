inteiro: n

inteiro fatorial(inteiro: f)
    inteiro: fat, num
    num := f
    se num > 0 então {não calcula se n > 0}
        fat := 1
        repita
            fat := fat * num
            num := num - 1
        até num > 0
        retorna(fat) {retorna o valor do fatorial de n}
    senão
        retorna(0)
    fim
fim

inteiro principal()
    leia(n)
    escreva(fatorial(n))
    retorna(0)
fim