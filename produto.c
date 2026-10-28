#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "produto.h"
#include "util.h"

#define ARQUIVO_PRODUTOS "produtos.txt"

void carregar_produtos(Produto produtos[], int *total) {
    FILE *arquivo;
    *total = 0;
    arquivo = fopen(ARQUIVO_PRODUTOS, "r");

    if (arquivo == NULL) {
        return;
    }

    while (*total < MAX_PRODUTOS &&
           fscanf(arquivo, "%d;%49[^;];%c;%f;%d;%d;%d;%d\n",
                  &produtos[*total].codigo,
                  produtos[*total].nome,
                  &produtos[*total].prateleira,
                  &produtos[*total].preco,
                  &produtos[*total].quantidade,
                  &produtos[*total].disponivel,
                  &produtos[*total].categoria_codigo,
                  &produtos[*total].ativo) == 8) {
        (*total)++;
    }

    fclose(arquivo);
}

void salvar_produtos(Produto produtos[], int total) {
    FILE *arquivo = fopen(ARQUIVO_PRODUTOS, "w");
    int i;

    if (arquivo == NULL) {
        printf("Erro ao salvar produtos.\n");
        return;
    }

    for (i = 0; i < total; i++) {
        fprintf(arquivo, "%d;%s;%c;%.2f;%d;%d;%d;%d\n",
                produtos[i].codigo,
                produtos[i].nome,
                produtos[i].prateleira,
                produtos[i].preco,
                produtos[i].quantidade,
                produtos[i].disponivel,
                produtos[i].categoria_codigo,
                produtos[i].ativo);
    }

    fclose(arquivo);
}

int buscar_produto_codigo(Produto produtos[], int total, int codigo) {
    int i;
    for (i = 0; i < total; i++) {
        if (produtos[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

int buscar_produto_nome(Produto produtos[], int total, char nome[]) {
    int i;
    for (i = 0; i < total; i++) {
        if (produtos[i].ativo == 1 && strcmp(produtos[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

void exibir_produto(Produto produto, Categoria categorias[], int total_categorias) {
    int posicao_categoria = buscar_categoria_codigo(categorias, total_categorias,
                                                     produto.categoria_codigo);

    printf("\nCodigo: %d\n", produto.codigo);
    printf("Nome: %s\n", produto.nome);
    printf("Prateleira: %c\n", produto.prateleira);
    printf("Preco unitario: R$ %.2f\n", produto.preco);
    printf("Quantidade em estoque: %d\n", produto.quantidade);
    printf("Disponivel para venda: %s\n", produto.disponivel == 1 ? "Sim" : "Nao");

    if (posicao_categoria != -1) {
        printf("Categoria: %s\n", categorias[posicao_categoria].nome);
    } else {
        printf("Categoria: nao encontrada\n");
    }
}

void cadastrar_produto(Produto produtos[], int *total, Categoria categorias[], int total_categorias) {
    Produto novo;
    int codigo_categoria;

    if (*total >= MAX_PRODUTOS) {
        printf("A lista de produtos esta cheia.\n");
        return;
    }

    novo.codigo = ler_inteiro("Codigo do produto: ");
    if (novo.codigo <= 0) {
        printf("O codigo deve ser positivo.\n");
        return;
    }

    if (buscar_produto_codigo(produtos, *total, novo.codigo) != -1) {
        printf("Ja existe um produto com esse codigo, mesmo que esteja inativo.\n");
        return;
    }

    ler_texto("Nome do produto: ", novo.nome, sizeof(novo.nome));
    novo.prateleira = ler_prateleira();

    novo.preco = ler_float("Preco unitario: R$ ");
    if (novo.preco <= 0) {
        printf("O preco deve ser maior que zero.\n");
        return;
    }

    novo.quantidade = ler_inteiro("Quantidade inicial: ");
    if (novo.quantidade < 0) {
        printf("A quantidade nao pode ser negativa.\n");
        return;
    }

    if (total_categorias == 0) {
        printf("Cadastre uma categoria antes de cadastrar produtos.\n");
        return;
    }

    listar_categorias(categorias, total_categorias);
    codigo_categoria = ler_inteiro("Codigo da categoria do produto: ");
    if (buscar_categoria_codigo(categorias, total_categorias, codigo_categoria) == -1) {
        printf("Essa categoria nao existe. Produto nao cadastrado.\n");
        return;
    }

    novo.categoria_codigo = codigo_categoria;
    novo.disponivel = novo.quantidade > 0 ? 1 : 0;
    novo.ativo = 1;

    produtos[*total] = novo;
    (*total)++;

    printf("\nProduto cadastrado com sucesso!\n");
    exibir_produto(novo, categorias, total_categorias);
}

void listar_produtos(Produto produtos[], int total, Categoria categorias[], int total_categorias) {
    int i;
    int encontrados = 0;

    for (i = 0; i < total; i++) {
        if (produtos[i].ativo == 1) {
            exibir_produto(produtos[i], categorias, total_categorias);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("Nao ha produtos ativos cadastrados.\n");
    }
}

void pesquisar_produto(Produto produtos[], int total, Categoria categorias[], int total_categorias) {
    int opcao;
    int codigo;
    int posicao;
    char nome[50];

    printf("\n--- PESQUISAR PRODUTO ---\n");
    printf("1 - Por codigo\n");
    printf("2 - Por nome\n");
    opcao = ler_inteiro("Escolha: ");

    if (opcao == 1) {
        codigo = ler_inteiro("Digite o codigo: ");
        posicao = buscar_produto_codigo(produtos, total, codigo);

        if (posicao != -1 && produtos[posicao].ativo == 1) {
            exibir_produto(produtos[posicao], categorias, total_categorias);
        } else {
            printf("Produto nao encontrado.\n");
        }
    } else if (opcao == 2) {
        ler_texto("Digite o nome exato: ", nome, sizeof(nome));
        posicao = buscar_produto_nome(produtos, total, nome);

        if (posicao != -1) {
            exibir_produto(produtos[posicao], categorias, total_categorias);
        } else {
            printf("Produto nao encontrado.\n");
        }
    } else {
        printf("Opcao invalida.\n");
    }
}

void alterar_estoque(Produto produtos[], int total) {
    int codigo;
    int posicao;
    int tipo;
    int quantidade;

    codigo = ler_inteiro("Codigo do produto: ");
    posicao = buscar_produto_codigo(produtos, total, codigo);

    if (posicao == -1 || produtos[posicao].ativo == 0) {
        printf("Produto nao encontrado.\n");
        return;
    }

    printf("1 - Entrada de estoque\n");
    printf("2 - Saida de estoque\n");
    tipo = ler_inteiro("Escolha: ");

    if (tipo != 1 && tipo != 2) {
        printf("Opcao invalida.\n");
        return;
    }

    quantidade = ler_inteiro("Quantidade: ");
    if (quantidade <= 0) {
        printf("A quantidade deve ser maior que zero.\n");
        return;
    }

    if (tipo == 1) {
        produtos[posicao].quantidade += quantidade;
    } else {
        if (quantidade > produtos[posicao].quantidade) {
            printf("Estoque insuficiente. Operacao cancelada.\n");
            return;
        }
        produtos[posicao].quantidade -= quantidade;
    }

    produtos[posicao].disponivel = produtos[posicao].quantidade > 0 ? 1 : 0;
    printf("Estoque atualizado. Quantidade atual: %d\n", produtos[posicao].quantidade);
}

void remover_produto(Produto produtos[], int total) {
    int codigo;
    int posicao;

    codigo = ler_inteiro("Codigo do produto que deseja remover: ");
    posicao = buscar_produto_codigo(produtos, total, codigo);

    if (posicao == -1 || produtos[posicao].ativo == 0) {
        printf("Produto nao encontrado.\n");
        return;
    }

    produtos[posicao].ativo = 0;
    printf("Produto removido com sucesso.\n");
}
