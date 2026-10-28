#ifndef CATEGORIA_H
#define CATEGORIA_H

#define MAX_CATEGORIAS 20

typedef struct {
    int codigo;
    char nome[30];
} Categoria;

void carregar_categorias(Categoria categorias[], int *total);
void salvar_categorias(Categoria categorias[], int total);
void menu_categorias(Categoria categorias[], int *total);
void cadastrar_categoria(Categoria categorias[], int *total);
void listar_categorias(Categoria categorias[], int total);
int buscar_categoria_codigo(Categoria categorias[], int total, int codigo);
void exibir_categorias(Categoria categorias[], int total);

#endif
