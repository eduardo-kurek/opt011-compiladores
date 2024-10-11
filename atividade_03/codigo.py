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


tag = input("Digite a tag que deseja buscar: ")
arquivo_txt = 'utfpr-cm.html'
padrao_regex = rf'<{tag}\b.*?>.*?</{tag}>' # O asterisco não pode ser guloso, por isso o ponto de interrogação

buscar_ocorrencias(arquivo_txt, padrao_regex)