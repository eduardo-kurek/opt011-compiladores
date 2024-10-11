# Atividade: Extração de Links

Faça o download de alguma página da Internet, do portal da UTFPR por exemplo, e realize a extração do conteúdo de uma tag HTML informada pelo usuário.

Podem usar os comandos wget^[https://www.hostinger.com/tutorials/wget-command-examples/] ou curl^[https://flaviocopes.com/http-curl/] para recuperar o código HTML.
$ wget "https://portal.utfpr.edu.br/campus/campomourao" -O utfpr-cm.html
$ curl "https://portal.utfpr.edu.br/campus/campomourao" >> utfpr-cm.html
Envie um arquivo PDF com um relatório da execução da atividade com comandos e conteúdo recuperados.

__Curiosidade: __ O mecanismo de funcionamento dos webcrawlers de buscadores, que recupera uma página e extrai os links referenciados por ela buscando pelas tags <a href="url">Link text or object</a>. Se imaginarmos uma página como um vértice de um grafo e os links como arestas de ligações com outros vértices, a busca em profundidade ou em largura vai ser determinada pela posição de inserção dos links extraídos na lista de links a serem explorados.

# Guia para execução

Executar o comando `py codigo.py`.