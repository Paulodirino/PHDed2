#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 101
#define MAX_NOMES 50000

void imprimeNomes(char *nomes[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s\n", nomes[i]);
    }
    printf("\n");
}

void troca(char *v[], int a, int b) {
    char *tmp = v[a];
    v[a] = v[b];
    v[b] = tmp;
}

void bubbleSort(char *v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(v[j], v[j + 1]) > 0) {
                troca(v, j, j + 1);
            }
        }
    }
}

void insertionSort(char *v[], int n) {
    for (int i = 1; i < n; i++) {
        char *chave = v[i];
        int j = i - 1;
        while (j >= 0 && strcmp(v[j], chave) > 0) {
            v[j + 1] = v[j];
            j = j - 1;
        }
        v[j + 1] = chave;
    }
}

void selectionSort(char *v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            if (strcmp(v[j], v[min_index]) < 0) {
                min_index = j;
            }
        }
        if (min_index != i) {
            troca(v, i, min_index);
        }
    }
}

void lerNomes(char *nomes[], int *num_nomes) {
    FILE *arquivo;
    char linha[MAX_NOME];
    *num_nomes = 0;

    arquivo = fopen("nomes2.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    while (fgets(linha, MAX_NOME, arquivo) != NULL && *num_nomes < MAX_NOMES) {
        linha[strcspn(linha, "\n")] = 0; // Remove o caractere de nova linha
        nomes[*num_nomes] = strdup(linha);
        (*num_nomes)++;
    }

    fclose(arquivo);
}

int main() {
    int opcao;
    int num_nomes;
    char *nomes[MAX_NOMES];

    lerNomes(nomes, &num_nomes);

    do {
        printf("Selecione o algoritmo de ordenacao:\n");
        printf("1. Bubble Sort\n");
        printf("2. Insertion Sort\n");
        printf("3. Selection Sort\n");
        printf("5. Sair\n");

        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                bubbleSort(nomes, num_nomes);
                printf("Nomes ordenados pelo Bubble Sort:\n");
                imprimeNomes(nomes, num_nomes);
                break;
            case 2:
                insertionSort(nomes, num_nomes);
                printf("Nomes ordenados pelo Insertion Sort:\n");
                imprimeNomes(nomes, num_nomes);
                break;
            case 3:
                selectionSort(nomes, num_nomes);
                printf("Nomes ordenados pelo Selection Sort:\n");
                imprimeNomes(nomes, num_nomes);
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 5);

    // Liberando memória alocada
    for (int i = 0; i < num_nomes; i++) {
        free(nomes[i]);
    }

    return 0;
}
