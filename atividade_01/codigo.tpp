inteiro: vetor[10]

inteiro escreva_vetor(inteiro: n)
    inteiro: i
    i := 0

    repita
        escreva(vetor[i])
        i := i + 1
    até i = n

    retorna(0)
fim


inteiro preencha_vetor(inteiro: n)
    inteiro: i
    i := 0

    inteiro: j
    j := n

    repita
        vetor[i] := j
        j := j - 1
        i := i + 1
    até i = n

    retorna(0)
fim

inteiro troca(inteiro: k)
    inteiro: aux
    aux := vetor[k]
    vetor[k] := vetor[k+1]
    vetor[k+1] := aux

    retorna(0)
fim

inteiro ordena_vetor(inteiro: n)
    inteiro: i
    i := 0

    inteiro: j
    j := 0

    repita
        repita
            se vetor[j] > vetor[j+1] então
                troca(j)
            fim
            j := j + 1
        até j = n - 1
        i := i + 1
    até i = n

    retorna(0)
fim

inteiro principal()
    preencha_vetor(10)
    escreva_vetor(10)
    orderna_vetor(10)
    escreva_vetor(10)
    retorna(0)
fim