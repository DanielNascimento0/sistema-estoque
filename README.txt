SISTEMA DE ESTOQUE - PROJETO FINAL

Arquivos do programa:
- main.c: menu principal
- produto.c / produto.h: cadastro, listagem, pesquisa, estoque e remocao
- categoria.c / categoria.h: cadastro e listagem de categorias
- util.c / util.h: leituras e validacoes genericas
- produtos.txt: criado automaticamente ao sair, guarda produtos
- categorias.txt: criado automaticamente ao sair, guarda categorias

COMO COMPILAR NO TERMINAL

Entre na pasta do projeto e execute:

gcc main.c produto.c categoria.c util.c -o estoque

Para executar:

./estoque

IMPORTANTE
Os arquivos produtos.txt e categorias.txt sao criados ao sair pela opcao 7.
Se ainda nao existirem, o programa inicia com as listas vazias.
O sistema usa nomes de produto exatos na pesquisa por nome.
O codigo e simples e voltado para estudo inicial de C.
