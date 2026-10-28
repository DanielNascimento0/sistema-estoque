#ifndef PRODUTO_H
#define PRODUTO_H

#include "categoria.h"

#define MAX_PRODUTOS 50

typedef struct {
    int codigo;
    char nome[50];
    char prateleira;
    float preco;
    int quantidade;
    int disponivel;
    int categoria_codigo;
    int ativo;
} Produto;

void carregar_produtos(Produto produtos[], int *total);
void salvar_produtos(Produto produtos[], int total);
void cadastrar_produto(Produto produtos[], int *total, Categoria categorias[], int total_categorias);
void listar_produtos(Produto produtos[], int total, Categoria categorias[], int total_categorias);
void pesquisar_produto(Produto produtos[], int total, Categoria categorias[], int total_categorias);
void alterar_estoque(Produto produtos[], int total);
void remover_produto(Produto produtos[], int total);
int buscar_produto_codigo(Produto produtos[], int total, int codigo);
int buscar_produto_nome(Produto produtos[], int total, char nome[]);
void exibir_produto(Produto produto, Categoria categorias[], int total_categorias);

#endif
