#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAMANHO_MOCHILA 10

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

void inserirItem(Item mochila[], int *totalItens);
void removerItem(Item mochila[], int *totalItens);
void listarItens(Item mochila[], int totalItens);
void buscarItem(Item mochila[], int totalItens);

int main() {
    Item mochila[TAMANHO_MOCHILA];
    int totalItens = 0;
    int opcao;

    do {
        printf("\n===== MOCHILA DE LOOT - FREE FIRE =====\n");
        printf("1 - Cadastrar item\n");
        printf("2 - Remover item\n");
        printf("3 - Buscar item\n");
        printf("4 - Listar itens\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                inserirItem(mochila, &totalItens);
                listarItens(mochila, totalItens);
                break;

            case 2:
                removerItem(mochila, &totalItens);
                listarItens(mochila, totalItens);
                break;

            case 3:
                buscarItem(mochila, totalItens);
                break;

            case 4:
                listarItens(mochila, totalItens);
                break;

            case 0:
                printf("\nSaindo da mochila...\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while(opcao != 0);

    return 0;
}

void inserirItem(Item mochila[], int *totalItens) {
    if (*totalItens >= TAMANHO_MOCHILA) {
        printf("\nA mochila esta cheia! Nao e possivel cadastrar mais itens.\n");
        return;
    }

    printf("\n--- CADASTRAR ITEM ---\n");

    printf("Nome do item: ");
    scanf("%s", mochila[*totalItens].nome);

    printf("Tipo do item (arma, municao, cura): ");
    scanf("%s", mochila[*totalItens].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochila[*totalItens].quantidade);

    (*totalItens)++;

    printf("\nItem cadastrado com sucesso!\n");
}

void removerItem(Item mochila[], int *totalItens) {
    char nomeRemover[30];
    int encontrado = -1;

    if (*totalItens == 0) {
        printf("\nA mochila esta vazia! Nao ha itens para remover.\n");
        return;
    }

    printf("\n--- REMOVER ITEM ---\n");
    printf("Digite o nome do item que deseja remover: ");
    scanf("%s", nomeRemover);

    for (int i = 0; i < *totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("\nItem nao encontrado na mochila.\n");
    } else {
        for (int i = encontrado; i < *totalItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }

        (*totalItens)--;

        printf("\nItem removido com sucesso!\n");
    }
}

void listarItens(Item mochila[], int totalItens) {
    printf("\n--- ITENS NA MOCHILA ---\n");

    if (totalItens == 0) {
        printf("A mochila esta vazia.\n");
        return;
    }

    for (int i = 0; i < totalItens; i++) {
        printf("\nItem %d:\n", i + 1);
        printf("Nome: %s\n", mochila[i].nome);
        printf("Tipo: %s\n", mochila[i].tipo);
        printf("Quantidade: %d\n", mochila[i].quantidade);
    }
}

void buscarItem(Item mochila[], int totalItens) {
    char nomeBusca[30];
    int encontrado = -1;

    if (totalItens == 0) {
        printf("\nA mochila esta vazia! Nao ha itens para buscar.\n");
        return;
    }

    printf("\n--- BUSCAR ITEM ---\n");
    printf("Digite o nome do item que deseja buscar: ");
    scanf("%s", nomeBusca);

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("\nItem nao encontrado.\n");
    } else {
        printf("\nItem encontrado!\n");
        printf("Nome: %s\n", mochila[encontrado].nome);
        printf("Tipo: %s\n", mochila[encontrado].tipo);
        printf("Quantidade: %d\n", mochila[encontrado].quantidade);
    }
}