#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#define MAX_NOME 50
#define MAX_POSICAO 30
#define MAX_JOGADORES 15
#define ARQUIVO_CSV "jogadores.csv"

typedef struct {
    char nome[MAX_NOME];
    int idade;
    char posicao[MAX_POSICAO];
    int ativo; 
} Jogador;

void limparbuffer();
int lerOpcao();
int Cadastrarjogadores(Jogador jogadores[], int total);
void listarjogadores(Jogador jogadores[], int total);
int buscarjogador(Jogador jogadores[], int total);
int apagarjogador(Jogador jogadores[], int total);
void salvarCSV(Jogador jogadores[], int total);
int carregarCSV(Jogador jogadores[]);

int main() {
    setlocale(LC_ALL, "Portuguese");

    int total = 0;
    Jogador jogadores[MAX_JOGADORES];
    int opcao;

    for (int i = 0; i < MAX_JOGADORES; i++) {
        jogadores[i].ativo = 0;
    }

    total = carregarCSV(jogadores);

    do {
        printf("\n------ Sistema De Cadastro De Jogadores ------\n");
        printf("1 - Cadastrar Jogadores\n");
        printf("2 - Listar Jogadores\n");
        printf("3 - Buscar Jogador\n");
        printf("4 - Apagar Jogador\n");
        printf("5 - Sair\n");
        opcao = lerOpcao();

        switch (opcao) {
            case 1:
                total = Cadastrarjogadores(jogadores, total);
                salvarCSV(jogadores, total);
                break;
            case 2:
                listarjogadores(jogadores, total);
                break;
            case 3:
                buscarjogador(jogadores, total);
                break;
            case 4:
                total = apagarjogador(jogadores, total);
                salvarCSV(jogadores, total);
                break;
            case 5:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 5);

    return 0;
}

void limparbuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int lerOpcao() {
    int opcao;
    printf("Escolha uma opção: ");
    while (scanf("%d", &opcao) != 1) {
        printf("Entrada inválida! Digite um número: ");
        limparbuffer();
    }
    limparbuffer();
    return opcao;
}

int Cadastrarjogadores(Jogador jogadores[], int total) {
    if (total >= MAX_JOGADORES) {
        printf("Máximo de jogadores atingido.\n");
        return total;
    }

    printf("\n---- Cadastro de Jogadores ----\n");
    printf("Nome: ");
    fgets(jogadores[total].nome, MAX_NOME, stdin);
    jogadores[total].nome[strcspn(jogadores[total].nome, "\n")] = '\0';

    printf("Idade: ");
    scanf("%d", &jogadores[total].idade);
    limparbuffer();

    printf("Posição: ");
    fgets(jogadores[total].posicao, MAX_POSICAO, stdin);
    jogadores[total].posicao[strcspn(jogadores[total].posicao, "\n")] = '\0';

    jogadores[total].ativo = 1;
    total++;

    printf("Jogador cadastrado com sucesso!\n");
    return total;
}

void listarjogadores(Jogador jogadores[], int total) {
    if (total == 0) {
        printf("Nenhum jogador cadastrado!\n");
        return;
    }

    printf("\n--- Lista de Jogadores ---\n");
    for (int i = 0; i < total; i++) {
        printf("%d | Nome: %s | Idade: %d | Posição: %s\n",
               i + 1, jogadores[i].nome, jogadores[i].idade, jogadores[i].posicao);
    }
}

int buscarjogador(Jogador jogadores[], int total) {
    if (total == 0) {
        printf("Nenhum jogador cadastrado!\n");
        return -1;
    }

    char busca[MAX_NOME];
    printf("Digite o nome que deseja buscar: ");
    fgets(busca, MAX_NOME, stdin);
    busca[strcspn(busca, "\n")] = '\0';

    for (int i = 0; i < total; i++) {
        if (strcasecmp(jogadores[i].nome, busca) == 0) {
            printf("✅ Encontrado: Nome: %s | Idade: %d | Posição: %s\n",
                   jogadores[i].nome, jogadores[i].idade, jogadores[i].posicao);
            return i;
        }
    }

    printf("Nenhum jogador encontrado.\n");
    return -1;
}

int apagarjogador(Jogador jogadores[], int total) {
    if (total == 0) {
        printf("Nenhum jogador cadastrado!\n");
        return total;
    }

    char busca[MAX_NOME];
    printf("Digite o nome que deseja apagar: ");
    fgets(busca, MAX_NOME, stdin);
    busca[strcspn(busca, "\n")] = '\0';

    int indice = -1;
    for (int i = 0; i < total; i++) {
        if (strcasecmp(jogadores[i].nome, busca) == 0) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("Jogador não encontrado.\n");
        return total;
    }

    for (int i = indice; i < total - 1; i++) {
        jogadores[i] = jogadores[i + 1];
    }
    total--;

    printf("Jogador removido com sucesso!\n");
    return total;
}

void salvarCSV(Jogador jogadores[], int total) {
    FILE *fp = fopen(ARQUIVO_CSV, "w");
    if (!fp) {
        printf("Erro ao abrir arquivo para salvar.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        fprintf(fp, "%s,%d,%s\n", jogadores[i].nome, jogadores[i].idade, jogadores[i].posicao);
    }

    fclose(fp);
}


int carregarCSV(Jogador jogadores[]) {
    FILE *fp = fopen(ARQUIVO_CSV, "r");
    if (!fp) {
        return 0; 
    }

    int total = 0;
    while (fscanf(fp, "%49[^,],%d,%29[^\n]\n", jogadores[total].nome, &jogadores[total].idade, jogadores[total].posicao) == 3) {
        jogadores[total].ativo = 1;
        total++;
        if (total >= MAX_JOGADORES) break;
    }

    fclose(fp);
    return total;
}
