#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "util.h"

int ler_inteiro(char mensagem[]) {
    int valor;
    char linha[100];
    char extra;

    while (1) {
        printf("%s", mensagem);
        if (fgets(linha, sizeof(linha), stdin) != NULL &&
            sscanf(linha, " %d %c", &valor, &extra) == 1) {
            return valor;
        }
        printf("Valor invalido. Digite um numero inteiro.\n");
    }
}

float ler_float(char mensagem[]) {
    float valor;
    char linha[100];
    char extra;

    while (1) {
        printf("%s", mensagem);
        if (fgets(linha, sizeof(linha), stdin) != NULL &&
            sscanf(linha, " %f %c", &valor, &extra) == 1) {
            return valor;
        }
        printf("Valor invalido. Digite um numero.\n");
    }
}

void ler_texto(char mensagem[], char texto[], int tamanho) {
    int tamanho_texto;

    while (1) {
        printf("%s", mensagem);
        if (fgets(texto, tamanho, stdin) == NULL) {
            texto[0] = '\0';
            return;
        }

        tamanho_texto = strlen(texto);
        if (tamanho_texto > 0 && texto[tamanho_texto - 1] == '\n') {
            texto[tamanho_texto - 1] = '\0';
        } else {
            int caractere;
            while ((caractere = getchar()) != '\n' && caractere != EOF) {
                /* Limpa o restante da linha. */
            }
        }

        if (texto_preenchido(texto)) {
            return;
        }
        printf("O texto nao pode ficar em branco.\n");
    }
}

int texto_preenchido(char texto[]) {
    int i;
    for (i = 0; texto[i] != '\0'; i++) {
        if (!isspace((unsigned char)texto[i])) {
            return 1;
        }
    }
    return 0;
}

char ler_prateleira(void) {
    char texto[20];
    char letra;

    while (1) {
        ler_texto("Prateleira (A, B, C ou D): ", texto, sizeof(texto));
        letra = (char)toupper((unsigned char)texto[0]);

        if (texto[1] == '\0' &&
            (letra == 'A' || letra == 'B' || letra == 'C' || letra == 'D')) {
            return letra;
        }
        printf("Prateleira invalida. Escolha A, B, C ou D.\n");
    }
}
