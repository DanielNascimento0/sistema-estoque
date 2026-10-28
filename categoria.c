#include <stdio.h>
#include <string.h>
#include "categoria.h"
#include "util.h"

#define ARQUIVO_CATEGORIAS "categorias.txt"

void carregar_categorias(Categoria categorias[], int *total) {
    FILE *arquivo;
    *total = 0;
    arquivo = fopen(ARQUIVO_CATEGORIAS, "r");

    if (arquivo == NULL) {
        return;
    }

    while (*total < MAX_CATEGORIAS &&
           fscanf(arquivo, "%d;%29[^\n]\n",
                  &categorias[*total].codigo,
                  categorias[*total].nome) == 2) {
        (*total)++;
    }

    fclose(arquivo);
}

void salvar_categorias(Categoria categorias[], int total) {
    FILE *arquivo = fopen(ARQUIVO_CATEGORIAS, "w");
    int i;

    if (arquivo == NULL) {
        printf("Erro ao salvar categorias.\n");
        return;
    }

    for (i = 0; i < total; i++) {
        fprintf(arquivo, "%d;%s\n", categorias[i].codigo, categorias[i].nome);
    }

    fclose(arquivo);
}

int buscar_categoria_codigo(Categoria categorias[], int total, int codigo) {
    int i;
    for (i = 0; i < total; i++) {
        if (categorias[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void cadastrar_categoria(Categoria categorias[], int *total) {
    Categoria nova;
    int codigo;

    if (*total >= MAX_CATEGORIAS) {
        printf("A lista de categorias esta cheia.\n");
        return;
    }

    codigo = ler_inteiro("Codigo da categoria: ");
    if (codigo <= 0) {
        printf("O codigo deve ser positivo.\n");
        return;
    }

    if (buscar_categoria_codigo(categorias, *total, codigo) != -1) {
        printf("Ja existe uma categoria com esse codigo.\n");
        return;
    }

    nova.codigo = codigo;
    ler_texto("Nome da categoria: ", nova.nome, sizeof(nova.nome));

    categorias[*total] = nova;
    (*total)++;
    printf("Categoria cadastrada com sucesso.\n");
}

void listar_categorias(Categoria categorias[], int total) {
    int i;

    if (total == 0) {
        printf("Nao ha categorias cadastradas.\n");
        return;
    }

    printf("\n--- CATEGORIAS ---\n");
    for (i = 0; i < total; i++) {
        printf("Codigo: %d | Nome: %s\n", categorias[i].codigo, categorias[i].nome);
    }
}

void exibir_categorias(Categoria categorias[], int total) {
    listar_categorias(categorias, total);
}

void menu_categorias(Categoria categorias[], int *total) {
    int opcao;

    do {
        printf("\n===== CATEGORIAS =====\n");
        printf("1 - Cadastrar Categoria\n");
        printf("2 - Listar Categorias\n");
        printf("3 - Voltar\n");
        opcao = ler_inteiro("Escolha: ");

        switch (opcao) {
            case 1:
                cadastrar_categoria(categorias, total);
                break;
            case 2:
                listar_categorias(categorias, *total);
                break;
            case 3:
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 3);
}
