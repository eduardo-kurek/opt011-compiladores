import re

def buscar_ocorrencias(arquivo, padrao):
    with open(arquivo, 'r', encoding='utf-8') as f:
        conteudo = f.read()

    regex = re.compile(padrao)
    ocorrencias = regex.findall(conteudo)

    if ocorrencias:
        print(f"Ocorrências encontradas ({len(ocorrencias)}):")
        for ocorrencia in ocorrencias:
            print(ocorrencia)
    else:
        print("Nenhuma ocorrência encontrada.")


arquivo_txt = 'e-mails.txt'
padrao_regex = r'[A-Za-z0-9_.]+@[A-Za-z.]+'

buscar_ocorrencias(arquivo_txt, padrao_regex)