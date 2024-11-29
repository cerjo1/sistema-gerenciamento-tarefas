#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TAREFAS 50
#define MAX_CARACTERES 100

void cadastrarTarefa(char tarefas[MAX_TAREFAS][4][MAX_CARACTERES], int *quantidade) {
    if (*quantidade >= MAX_TAREFAS) {
        printf("Limite de tarefas atingido!\n");
        return;
    }

    printf("Título: ");
    getchar(); // Limpar buffer
    fgets(tarefas[*quantidade][0], MAX_CARACTERES, stdin);
    tarefas[*quantidade][0][strcspn(tarefas[*quantidade][0], "\n")] = '\0';

    printf("Descrição: ");
    fgets(tarefas[*quantidade][1], MAX_CARACTERES, stdin);
    tarefas[*quantidade][1][strcspn(tarefas[*quantidade][1], "\n")] = '\0';

    printf("Prioridade: ");
    fgets(tarefas[*quantidade][2], MAX_CARACTERES, stdin);
    tarefas[*quantidade][2][strcspn(tarefas[*quantidade][2], "\n")] = '\0';

    printf("Status: ");
    fgets(tarefas[*quantidade][3], MAX_CARACTERES, stdin);
    tarefas[*quantidade][3][strcspn(tarefas[*quantidade][3], "\n")] = '\0';

    (*quantidade)++;
    printf("Tarefa cadastrada com sucesso!\n");
}

void listarTarefas(char tarefas[MAX_TAREFAS][4][MAX_CARACTERES], int quantidade) {
    if (quantidade == 0) {
        printf("Nenhuma tarefa cadastrada.\n");
        return;
    }

    for (int i = 0; i < quantidade; i++) {
        printf("\nTarefa %d:\n", i + 1);
        printf("Título: %s\n", tarefas[i][0]);
        printf("Descrição: %s\n", tarefas[i][1]);
        printf("Prioridade: %s\n", tarefas[i][2]);
        printf("Status: %s\n", tarefas[i][3]);
    }
}

void editarTarefa(char tarefas[MAX_TAREFAS][4][MAX_CARACTERES], int indice) {
    printf("Editar Tarefa %d:\n", indice + 1);

    printf("Novo Título: ");
    getchar(); // Limpar buffer
    fgets(tarefas[indice][0], MAX_CARACTERES, stdin);
    tarefas[indice][0][strcspn(tarefas[indice][0], "\n")] = '\0';

    printf("Nova Descrição: ");
    fgets(tarefas[indice][1], MAX_CARACTERES, stdin);
    tarefas[indice][1][strcspn(tarefas[indice][1], "\n")] = '\0';

    printf("Nova Prioridade: ");
    fgets(tarefas[indice][2], MAX_CARACTERES, stdin);
    tarefas[indice][2][strcspn(tarefas[indice][2], "\n")] = '\0';

    printf("Novo Status: ");
    fgets(tarefas[indice][3], MAX_CARACTERES, stdin);
    tarefas[indice][3][strcspn(tarefas[indice][3], "\n")] = '\0';

    printf("Tarefa editada com sucesso!\n");
}

void excluirTarefa(char tarefas[MAX_TAREFAS][4][MAX_CARACTERES], int *quantidade, int indice) {
    if (indice < 0 || indice >= *quantidade) {
        printf("Índice inválido!\n");
        return;
    }

    for (int i = indice; i < *quantidade - 1; i++) {
        for (int j = 0; j < 4; j++) {
            strcpy(tarefas[i][j], tarefas[i + 1][j]);
        }
    }

    (*quantidade)--;
    printf("Tarefa excluída com sucesso!\n");
}

void salvarTarefasEmArquivo(char tarefas[MAX_TAREFAS][4][MAX_CARACTERES], int quantidade) {
    FILE *arquivo = fopen("tarefas.txt", "w");
    if (!arquivo) {
        printf("Erro ao salvar tarefas no arquivo.\n");
        return;
    }

    for (int i = 0; i < quantidade; i++) {
        fprintf(arquivo, "Tarefa %d:\n", i + 1);
        fprintf(arquivo, "Título: %s\n", tarefas[i][0]);
        fprintf(arquivo, "Descrição: %s\n", tarefas[i][1]);
        fprintf(arquivo, "Prioridade: %s\n", tarefas[i][2]);
        fprintf(arquivo, "Status: %s\n\n", tarefas[i][3]);
    }

    fclose(arquivo);
    printf("Tarefas salvas com sucesso em tarefas.txt!\n");
}

int main() {
    char tarefas[MAX_TAREFAS][4][MAX_CARACTERES];
    int quantidade = 0;
    int opcao;

    do {
        printf("\nSistema de Gerenciamento de Tarefas\n");
        printf("1. Adicionar tarefa\n");
        printf("2. Listar tarefas cadastradas\n");
        printf("3. Editar tarefa\n");
        printf("4. Excluir tarefa\n");
        printf("5. Salvar tarefas em arquivo\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarTarefa(tarefas, &quantidade);
                break;
            case 2:
                listarTarefas(tarefas, quantidade);
                break;
            case 3: {
                int indice;
                printf("Digite o índice da tarefa a ser editada: ");
                scanf("%d", &indice);
                if (indice > 0 && indice <= quantidade) {
                    editarTarefa(tarefas, indice - 1);
                } else {
                    printf("Índice inválido!\n");
                }
                break;
            }
            case 4: {
                int indice;
                printf("Digite o índice da tarefa a ser excluída: ");
                scanf("%d", &indice);
                if (indice > 0 && indice <= quantidade) {
                    excluirTarefa(tarefas, &quantidade, indice - 1);
                } else {
                    printf("Índice inválido!\n");
                }
                break;
            }
            case 5:
                salvarTarefasEmArquivo(tarefas, quantidade);
                break;
            case 6:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (opcao != 6);

    return 0;
}
