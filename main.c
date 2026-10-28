#include <stdio.h>
#include "produto.h"
#include "categoria.h"
#include "util.h"

int main(void) {
    Produto produtos[MAX_PRODUTOS];
    Categoria categorias[MAX_CATEGORIAS];
    int total_produtos = 0;
    int total_categorias = 0;
    int opcao;

    carregar_categorias(categorias, &total_categorias);
    carregar_produtos(produtos, &total_produtos);

    do {
        printf("\n===== SISTEMA DE ESTOQUE =====\n");
        printf("1 - Cadastrar Produto\n");
        printf("2 - Listar Produtos\n");
        printf("3 - Pesquisar Produto\n");
        printf("4 - Alterar Estoque de um Produto\n");
        printf("5 - Remover Produto\n");
        printf("6 - Categorias\n");
        printf("7 - Sair\n");

        opcao = ler_inteiro("Escolha uma opcao: ");

        switch (opcao) {
            case 1:
                cadastrar_produto(produtos, &total_produtos, categorias, total_categorias);
                break;
            case 2:
                listar_produtos(produtos, total_produtos, categorias, total_categorias);
                break;
            case 3:
                pesquisar_produto(produtos, total_produtos, categorias, total_categorias);
                break;
            case 4:
                alterar_estoque(produtos, total_produtos);
                break;
            case 5:
                remover_produto(produtos, total_produtos);
                break;
            case 6:
                menu_categorias(categorias, &total_categorias);
                break;
            case 7:
                salvar_categorias(categorias, total_categorias);
                salvar_produtos(produtos, total_produtos);
                printf("Dados salvos. Ate mais!\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 7);

    return 0;
}
