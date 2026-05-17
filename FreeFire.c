#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade;
} Componente;

/* ===================== PROTOTIPOS ===================== */

void adicionarComponente(Componente vetor[], int *total);
void descartarComponente(Componente vetor[], int *total);
void mostrarComponentes(Componente vetor[], int total);

void bubbleSortNome(Componente vetor[], int tamanho, int *comparacoes);
void insertionSortTipo(Componente vetor[], int tamanho, int *comparacoes);
void selectionSortPrioridade(Componente vetor[], int tamanho, int *comparacoes);

int buscaBinariaPorNome(
    Componente vetor[],
    int tamanho,
    char nomeBusca[],
    int *comparacoes
);

void medirTempo(
    void (*algoritmo)(Componente[], int, int*),
    Componente vetor[],
    int tamanho,
    int *comparacoes
);

void limparBuffer();
void pausarTela();

/* ===================== MAIN ===================== */

int main() {

    Componente mochila[MAX_COMPONENTES];

    int totalComponentes = 0;
    int opcao;
    int criterio;
    int ordenadoPorNome = 0;

    int comparacoes = 0;

    char nomeBusca[30];

    do {

        system("cls");

        printf("=============================================================\n");
        printf("      PLANO DE FUGA - CODIGO DA ILHA (NIVEL MESTRE)\n");
        printf("=============================================================\n\n");

        printf("Itens na Mochila: %d/%d\n",
               totalComponentes,
               MAX_COMPONENTES);

        if (ordenadoPorNome) {
            printf("Status da Ordenacao por Nome: ORDENADO\n\n");
        } else {
            printf("Status da Ordenacao por Nome: NAO ORDENADO\n\n");
        }

        printf("1. Adicionar Componente\n");
        printf("2. Descartar Componente\n");
        printf("3. Listar Componentes (Inventario)\n");
        printf("4. Organizar Mochila (Ordenar Componentes)\n");
        printf("5. Busca Binaria por Componente-Chave (por nome)\n");
        printf("0. ATIVAR TORRE DE FUGA (Sair)\n");

        printf("-------------------------------------------------------------\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        limparBuffer();

        switch(opcao) {

            case 1:

                adicionarComponente(
                    mochila,
                    &totalComponentes
                );

                ordenadoPorNome = 0;

                mostrarComponentes(
                    mochila,
                    totalComponentes
                );

                pausarTela();

                break;

            case 2:

                descartarComponente(
                    mochila,
                    &totalComponentes
                );

                ordenadoPorNome = 0;

                mostrarComponentes(
                    mochila,
                    totalComponentes
                );

                pausarTela();

                break;

            case 3:

                mostrarComponentes(
                    mochila,
                    totalComponentes
                );

                pausarTela();

                break;

            case 4:

                printf("\n--- Estrategia de Organizacao ---\n");

                printf("Como deseja ordenar os componentes?\n\n");

                printf("1. Por Nome (Ordem Alfabetica)\n");
                printf("2. Por Tipo\n");
                printf("3. Por Prioridade de Montagem\n");
                printf("0. Cancelar\n");

                printf("\nEscolha o criterio: ");
                scanf("%d", &criterio);

                limparBuffer();

                comparacoes = 0;

                switch(criterio) {

                    case 1:

                        medirTempo(
                            bubbleSortNome,
                            mochila,
                            totalComponentes,
                            &comparacoes
                        );

                        printf("\nMochila organizada por NOME.\n");

                        ordenadoPorNome = 1;

                        break;

                    case 2:

                        medirTempo(
                            insertionSortTipo,
                            mochila,
                            totalComponentes,
                            &comparacoes
                        );

                        printf("\nMochila organizada por TIPO.\n");

                        ordenadoPorNome = 0;

                        break;

                    case 3:

                        medirTempo(
                            selectionSortPrioridade,
                            mochila,
                            totalComponentes,
                            &comparacoes
                        );

                        printf("\nMochila organizada por PRIORIDADE.\n");

                        ordenadoPorNome = 0;

                        break;

                    case 0:

                        printf("\nOperacao cancelada.\n");

                        break;

                    default:

                        printf("\nOpcao invalida.\n");
                }

                if (criterio >= 1 && criterio <= 3) {

                    printf("Analise de Desempenho: ");
                    printf("Foram necessarias %d comparacoes.\n",
                           comparacoes);

                    mostrarComponentes(
                        mochila,
                        totalComponentes
                    );
                }

                pausarTela();

                break;

            case 5:

                if (!ordenadoPorNome) {

                    printf("\nERRO!\n");
                    printf("A busca binaria exige ");
                    printf("ordenacao por NOME.\n");

                    pausarTela();

                    break;
                }

                printf("\n--- Busca Binaria por Componente-Chave ---\n");

                printf("Nome do componente a buscar: ");

                fgets(nomeBusca, 30, stdin);

                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                comparacoes = 0;

                int posicao;

                posicao = buscaBinariaPorNome(
                    mochila,
                    totalComponentes,
                    nomeBusca,
                    &comparacoes
                );

                if (posicao != -1) {

                    printf("\n--- Componente-Chave Encontrado! ---\n");

                    printf("Nome: %s\n",
                           mochila[posicao].nome);

                    printf("Tipo: %s\n",
                           mochila[posicao].tipo);

                    printf("Qtd: %d\n",
                           mochila[posicao].quantidade);

                    printf("Prio: %d\n",
                           mochila[posicao].prioridade);

                } else {

                    printf("\nComponente nao encontrado.\n");
                }

                printf("\nComparacoes realizadas: %d\n",
                       comparacoes);

                pausarTela();

                break;

            case 0:

                printf("\nATIVANDO TORRE DE FUGA...\n");
                printf("Missao concluida com sucesso!\n");

                break;

            default:

                printf("\nOpcao invalida!\n");

                pausarTela();
        }

    } while(opcao != 0);

    return 0;
}

/* ===================== ADICIONAR ===================== */

void adicionarComponente(
    Componente vetor[],
    int *total
) {

    if (*total >= MAX_COMPONENTES) {

        printf("\nMochila cheia!\n");

        return;
    }

    printf("\n--- ADICIONAR COMPONENTE ---\n");

    printf("Nome: ");
    fgets(vetor[*total].nome, 30, stdin);

    vetor[*total].nome[
        strcspn(vetor[*total].nome, "\n")
    ] = '\0';

    printf("Tipo: ");
    fgets(vetor[*total].tipo, 20, stdin);

    vetor[*total].tipo[
        strcspn(vetor[*total].tipo, "\n")
    ] = '\0';

    printf("Quantidade: ");
    scanf("%d",
          &vetor[*total].quantidade);

    printf("Prioridade (1-10): ");
    scanf("%d",
          &vetor[*total].prioridade);

    limparBuffer();

    printf("\nComponente '%s' adicionado!\n",
           vetor[*total].nome);

    (*total)++;
}

/* ===================== DESCARTAR ===================== */

void descartarComponente(
    Componente vetor[],
    int *total
) {

    char nomeBusca[30];

    int encontrado = -1;

    if (*total == 0) {

        printf("\nInventario vazio.\n");

        return;
    }

    printf("\n--- DESCARTAR COMPONENTE ---\n");

    printf("Nome do componente: ");

    fgets(nomeBusca, 30, stdin);

    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < *total; i++) {

        if (strcmp(vetor[i].nome,
                   nomeBusca) == 0) {

            encontrado = i;

            break;
        }
    }

    if (encontrado == -1) {

        printf("\nComponente nao encontrado.\n");

        return;
    }

    for (int i = encontrado;
         i < *total - 1;
         i++) {

        vetor[i] = vetor[i + 1];
    }

    (*total)--;

    printf("\nComponente removido com sucesso!\n");
}

/* ===================== MOSTRAR ===================== */

void mostrarComponentes(
    Componente vetor[],
    int total
) {

    printf("\n--- INVENTARIO ATUAL (%d/%d) ---\n",
           total,
           MAX_COMPONENTES);

    printf("--------------------------------------------------------------------------\n");

    printf("%-20s | %-15s | %-10s | %-10s\n",
           "NOME",
           "TIPO",
           "QUANTIDADE",
           "PRIORIDADE");

    printf("--------------------------------------------------------------------------\n");

    if (total == 0) {

        printf("Inventario vazio.\n");

        return;
    }

    for (int i = 0; i < total; i++) {

        printf("%-20s | %-15s | %-10d | %-10d\n",

               vetor[i].nome,

               vetor[i].tipo,

               vetor[i].quantidade,

               vetor[i].prioridade);
    }

    printf("--------------------------------------------------------------------------\n");
}

/* ===================== BUBBLE SORT ===================== */

void bubbleSortNome(
    Componente vetor[],
    int tamanho,
    int *comparacoes
) {

    Componente auxiliar;

    for (int i = 0; i < tamanho - 1; i++) {

        for (int j = 0; j < tamanho - 1 - i; j++) {

            (*comparacoes)++;

            if (strcmp(vetor[j].nome,
                       vetor[j + 1].nome) > 0) {

                auxiliar = vetor[j];

                vetor[j] = vetor[j + 1];

                vetor[j + 1] = auxiliar;
            }
        }
    }
}

/* ===================== INSERTION SORT ===================== */

void insertionSortTipo(
    Componente vetor[],
    int tamanho,
    int *comparacoes
) {

    Componente chave;

    int j;

    for (int i = 1; i < tamanho; i++) {

        chave = vetor[i];

        j = i - 1;

        while (j >= 0 &&
               strcmp(vetor[j].tipo,
                      chave.tipo) > 0) {

            (*comparacoes)++;

            vetor[j + 1] = vetor[j];

            j--;
        }

        vetor[j + 1] = chave;
    }
}

/* ===================== SELECTION SORT ===================== */

void selectionSortPrioridade(
    Componente vetor[],
    int tamanho,
    int *comparacoes
) {

    int menor;

    Componente auxiliar;

    for (int i = 0; i < tamanho - 1; i++) {

        menor = i;

        for (int j = i + 1; j < tamanho; j++) {

            (*comparacoes)++;

            if (vetor[j].prioridade >
                vetor[menor].prioridade) {

                menor = j;
            }
        }

        auxiliar = vetor[i];

        vetor[i] = vetor[menor];

        vetor[menor] = auxiliar;
    }
}

/* ===================== BUSCA BINARIA ===================== */

int buscaBinariaPorNome(
    Componente vetor[],
    int tamanho,
    char nomeBusca[],
    int *comparacoes
) {

    int inicio = 0;
    int fim = tamanho - 1;
    int meio;

    while (inicio <= fim) {

        meio = (inicio + fim) / 2;

        (*comparacoes)++;

        int resultado;

        resultado = strcmp(
            vetor[meio].nome,
            nomeBusca
        );

        if (resultado == 0) {

            return meio;
        }

        if (resultado < 0) {

            inicio = meio + 1;

        } else {

            fim = meio - 1;
        }
    }

    return -1;
}

/* ===================== MEDIR TEMPO ===================== */

void medirTempo(
    void (*algoritmo)(Componente[], int, int*),
    Componente vetor[],
    int tamanho,
    int *comparacoes
) {

    clock_t inicio;
    clock_t fim;

    double tempo;

    inicio = clock();

    algoritmo(
        vetor,
        tamanho,
        comparacoes
    );

    fim = clock();

    tempo = ((double)(fim - inicio))
            / CLOCKS_PER_SEC;

    printf("\nTempo de execucao: %.6f segundos\n",
           tempo);
}

/* ===================== BUFFER ===================== */

void limparBuffer() {

    while(getchar() != '\n');
}

/* ===================== PAUSA ===================== */

void pausarTela() {

    printf("\nPressione Enter para continuar...");
    getchar();
}