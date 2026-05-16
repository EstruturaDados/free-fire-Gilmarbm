#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 10

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

/* Protótipos - Vetor */
void inserirItemVetor(Item mochila[], int *total);
void removerItemVetor(Item mochila[], int *total);
void listarItensVetor(Item mochila[], int total);
void buscarItemVetor(Item mochila[], int total, int *comparacoes);
void ordenarVetorPorNome(Item mochila[], int total);

/* Protótipos - Lista Encadeada */
void inserirItemLista(No **inicio);
void removerItemLista(No **inicio);
void listarItensLista(No *inicio);
void buscarItemLista(No *inicio, int *comparacoes);
void liberarLista(No **inicio);

int main() {
    Item mochilaVetor[MAX_ITENS];
    int totalVetor = 0;
    No *mochilaLista = NULL;

    int opcao;
    int comparacoes;

    do {
        printf("\n=========== MOCHILA DE LOOT - NIVEL AVENTUREIRO ===========\n");
        printf("1  - Inserir item no vetor\n");
        printf("2  - Remover item do vetor\n");
        printf("3  - Listar itens do vetor\n");
        printf("4  - Buscar item no vetor\n");
        printf("5  - Ordenar vetor por nome\n");
        printf("6  - Inserir item na lista encadeada\n");
        printf("7  - Remover item da lista encadeada\n");
        printf("8  - Listar itens da lista encadeada\n");
        printf("9  - Buscar item na lista encadeada\n");
        printf("0  - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                inserirItemVetor(mochilaVetor, &totalVetor);
                listarItensVetor(mochilaVetor, totalVetor);
                break;

            case 2:
                removerItemVetor(mochilaVetor, &totalVetor);
                listarItensVetor(mochilaVetor, totalVetor);
                break;

            case 3:
                listarItensVetor(mochilaVetor, totalVetor);
                break;

            case 4:
                comparacoes = 0;
                buscarItemVetor(mochilaVetor, totalVetor, &comparacoes);
                printf("Comparacoes realizadas no vetor: %d\n", comparacoes);
                break;

            case 5:
                ordenarVetorPorNome(mochilaVetor, totalVetor);
                listarItensVetor(mochilaVetor, totalVetor);
                break;

            case 6:
                inserirItemLista(&mochilaLista);
                listarItensLista(mochilaLista);
                break;

            case 7:
                removerItemLista(&mochilaLista);
                listarItensLista(mochilaLista);
                break;

            case 8:
                listarItensLista(mochilaLista);
                break;

            case 9:
                comparacoes = 0;
                buscarItemLista(mochilaLista, &comparacoes);
                printf("Comparacoes realizadas na lista encadeada: %d\n", comparacoes);
                break;

            case 0:
                printf("\nSaindo do sistema...\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while(opcao != 0);

    liberarLista(&mochilaLista);

    return 0;
}

/* ================= FUNCOES DO VETOR ================= */

void inserirItemVetor(Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("\nA mochila do vetor esta cheia!\n");
        return;
    }

    printf("\n--- INSERIR ITEM NO VETOR ---\n");

    printf("Nome do item: ");
    scanf("%s", mochila[*total].nome);

    printf("Tipo do item: ");
    scanf("%s", mochila[*total].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochila[*total].quantidade);

    (*total)++;

    printf("\nItem inserido no vetor com sucesso!\n");
}

void removerItemVetor(Item mochila[], int *total) {
    char nomeRemover[30];
    int posicao = -1;

    if (*total == 0) {
        printf("\nA mochila do vetor esta vazia!\n");
        return;
    }

    printf("\n--- REMOVER ITEM DO VETOR ---\n");
    printf("Digite o nome do item: ");
    scanf("%s", nomeRemover);

    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            posicao = i;
            break;
        }
    }

    if (posicao == -1) {
        printf("\nItem nao encontrado no vetor.\n");
    } else {
        for (int i = posicao; i < *total - 1; i++) {
            mochila[i] = mochila[i + 1];
        }

        (*total)--;
        printf("\nItem removido do vetor com sucesso!\n");
    }
}

void listarItensVetor(Item mochila[], int total) {
    printf("\n--- ITENS NO VETOR ---\n");

    if (total == 0) {
        printf("A mochila do vetor esta vazia.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("\nItem %d\n", i + 1);
        printf("Nome: %s\n", mochila[i].nome);
        printf("Tipo: %s\n", mochila[i].tipo);
        printf("Quantidade: %d\n", mochila[i].quantidade);
    }
}

void buscarItemVetor(Item mochila[], int total, int *comparacoes) {
    char nomeBusca[30];

    if (total == 0) {
        printf("\nA mochila do vetor esta vazia!\n");
        return;
    }

    printf("\n--- BUSCAR ITEM NO VETOR ---\n");
    printf("Digite o nome do item: ");
    scanf("%s", nomeBusca);

    for (int i = 0; i < total; i++) {
        (*comparacoes)++;

        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado no vetor!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            return;
        }
    }

    printf("\nItem nao encontrado no vetor.\n");
}

void ordenarVetorPorNome(Item mochila[], int total) {
    Item auxiliar;

    if (total == 0) {
        printf("\nA mochila do vetor esta vazia!\n");
        return;
    }

    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - 1 - i; j++) {
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                auxiliar = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = auxiliar;
            }
        }
    }

    printf("\nVetor ordenado por nome com sucesso!\n");
}

/* ================= FUNCOES DA LISTA ENCADEADA ================= */

void inserirItemLista(No **inicio) {
    No *novo = (No*) malloc(sizeof(No));

    if (novo == NULL) {
        printf("\nErro ao alocar memoria!\n");
        return;
    }

    printf("\n--- INSERIR ITEM NA LISTA ENCADEADA ---\n");

    printf("Nome do item: ");
    scanf("%s", novo->dados.nome);

    printf("Tipo do item: ");
    scanf("%s", novo->dados.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = *inicio;
    *inicio = novo;

    printf("\nItem inserido na lista encadeada com sucesso!\n");
}

void removerItemLista(No **inicio) {
    char nomeRemover[30];
    No *atual = *inicio;
    No *anterior = NULL;

    if (*inicio == NULL) {
        printf("\nA lista encadeada esta vazia!\n");
        return;
    }

    printf("\n--- REMOVER ITEM DA LISTA ENCADEADA ---\n");
    printf("Digite o nome do item: ");
    scanf("%s", nomeRemover);

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nomeRemover) == 0) {
            if (anterior == NULL) {
                *inicio = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }

            free(atual);
            printf("\nItem removido da lista encadeada com sucesso!\n");
            return;
        }

        anterior = atual;
        atual = atual->proximo;
    }

    printf("\nItem nao encontrado na lista encadeada.\n");
}

void listarItensLista(No *inicio) {
    No *atual = inicio;
    int contador = 1;

    printf("\n--- ITENS NA LISTA ENCADEADA ---\n");

    if (inicio == NULL) {
        printf("A lista encadeada esta vazia.\n");
        return;
    }

    while (atual != NULL) {
        printf("\nItem %d\n", contador);
        printf("Nome: %s\n", atual->dados.nome);
        printf("Tipo: %s\n", atual->dados.tipo);
        printf("Quantidade: %d\n", atual->dados.quantidade);

        atual = atual->proximo;
        contador++;
    }
}

void buscarItemLista(No *inicio, int *comparacoes) {
    char nomeBusca[30];
    No *atual = inicio;

    if (inicio == NULL) {
        printf("\nA lista encadeada esta vazia!\n");
        return;
    }

    printf("\n--- BUSCAR ITEM NA LISTA ENCADEADA ---\n");
    printf("Digite o nome do item: ");
    scanf("%s", nomeBusca);

    while (atual != NULL) {
        (*comparacoes)++;

        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            printf("\nItem encontrado na lista encadeada!\n");
            printf("Nome: %s\n", atual->dados.nome);
            printf("Tipo: %s\n", atual->dados.tipo);
            printf("Quantidade: %d\n", atual->dados.quantidade);
            return;
        }

        atual = atual->proximo;
    }

    printf("\nItem nao encontrado na lista encadeada.\n");
}

void liberarLista(No **inicio) {
    No *atual = *inicio;
    No *proximo;

    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    *inicio = NULL;
}