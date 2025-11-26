#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- Estrutura de Dados ---
/**
 * @brief Define a estrutura para um componente da torre de resgate.
 */
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade; // 1 (mais baixa) a 10 (mais alta)
} Componente;

// --- Protótipos das Funções ---
void cadastrarComponentes(Componente componentes[], int *tamanho);
void mostrarComponentes(Componente componentes[], int tamanho);
long bubbleSortNome(Componente componentes[], int tamanho);
long insertionSortTipo(Componente componentes[], int tamanho);
long selectionSortPrioridade(Componente componentes[], int tamanho);
int buscaBinariaPorNome(Componente componentes[], int tamanho, const char chave[]);
void executarOrdenacao(Componente componentes[], int tamanho, int escolha);
void limparBuffer();
void copiarComponentes(Componente destino[], Componente origem[], int tamanho);
void removerNovaLinha(char *string);

// --- Variáveis Globais para Medição de Desempenho ---
#define MAX_COMPONENTES 20 // Máximo de componentes que podem ser cadastrados

// --- Função Principal (main) ---
int main() {
    Componente componentes[MAX_COMPONENTES]; // Armazena os componentes originais
    Componente componentesParaOperacao[MAX_COMPONENTES]; // Cópia para ordenação/busca
    int tamanho = 0;
    int escolha;
    int ordenadoPorNome = 0; // Flag para busca binária

    printf("### 🚀 Módulo Avançado de Organização de Componentes da Torre de Fuga ###\n\n");

    // 1. Entrada dos Dados
    cadastrarComponentes(componentes, &tamanho);
    if (tamanho == 0) {
        printf("\nNenhum componente cadastrado. Encerrando o programa.\n");
        return 0;
    }

    do {
        // Copia os dados originais para uma nova operação
        copiarComponentes(componentesParaOperacao, componentes, tamanho);

        // 2. Interface Amigável (Menu Interativo)
        printf("\n--- MENU ESTRATÉGICO ---\n");
        printf("1. Ordenar por Nome (Bubble Sort)\n");
        printf("2. Ordenar por Tipo (Insertion Sort)\n");
        printf("3. Ordenar por Prioridade (Selection Sort)\n");
        printf("4. Buscar Componente-Chave (Apenas após ordenação por Nome)\n");
        printf("5. Visualizar Componentes Atuais (Desordenado)\n");
        printf("0. Sair e Montar a Torre\n");
        printf("Escolha sua estratégia (0-5): ");
        if (scanf("%d", &escolha) != 1) {
            escolha = -1; // Sinaliza erro de input
        }
        limparBuffer();
        printf("-------------------------\n");

        ordenadoPorNome = 0; // Reseta o flag antes de cada operação

        switch (escolha) {
            case 1:
            case 2:
            case 3:
                executarOrdenacao(componentesParaOperacao, tamanho, escolha);
                // Se ordenou por nome, habilita a busca
                if (escolha == 1) {
                    ordenadoPorNome = 1;
                }
                break;
            case 4:
                // 4. Busca Binária
                if (ordenadoPorNome) {
                    char chave[30];
                    printf("Informe o NOME do componente-chave a ser buscado: ");
                    if (fgets(chave, sizeof(chave), stdin) != NULL) {
                        removerNovaLinha(chave);
                        int indice = buscaBinariaPorNome(componentesParaOperacao, tamanho, chave);
                        printf("\n--- RESULTADO DA BUSCA BINÁRIA ---\n");
                        if (indice != -1) {
                            printf("Componente-Chave '%s' ENCONTRADO na posição %d.\n", chave, indice + 1);
                            printf("Componente: Nome: %s, Tipo: %s, Prioridade: %d\n", 
                                   componentesParaOperacao[indice].nome, 
                                   componentesParaOperacao[indice].tipo, 
                                   componentesParaOperacao[indice].prioridade);
                        } else {
                            printf("Componente-Chave '%s' NÃO ENCONTRADO. Missão comprometida!\n", chave);
                        }
                    }
                } else {
                    printf("ATENÇÃO: A Busca Binária só é aplicável após ordenar os componentes por NOME (Opção 1).\n");
                }
                break;
            case 5:
                printf("--- COMPONENTES DESORDENADOS ---\n");
                mostrarComponentes(componentes, tamanho);
                break;
            case 0:
                printf("\nTorre de Fuga Montada! Boa sorte na evacuação!\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }

    } while (escolha != 0);

    return 0;
}

// --- Funções de Utilitários ---

/**
 * @brief Remove o caractere de nova linha (\n) lido pelo fgets.
 * @param string A string a ser tratada.
 */
void removerNovaLinha(char *string) {
    size_t len = strlen(string);
    if (len > 0 && string[len - 1] == '\n') {
        string[len - 1] = '\0';
    }
}

/**
 * @brief Limpa o buffer de entrada.
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Copia um array de Componentes para outro.
 * @param destino Array de destino.
 * @param origem Array de origem.
 * @param tamanho Número de elementos a copiar.
 */
void copiarComponentes(Componente destino[], Componente origem[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        destino[i] = origem[i];
    }
}

// --- 2. Entrada dos Dados ---
/**
 * @brief Permite o cadastro de componentes pelo jogador.
 * @param componentes O array de structs onde os dados serão armazenados.
 * @param tamanho Ponteiro para a variável que guarda o número atual de componentes.
 */
void cadastrarComponentes(Componente componentes[], int *tamanho) {
    char input[10];
    int count = 0;
    
    printf("--- CADASTRO DE COMPONENTES ---\n");
    printf("Você pode cadastrar até %d componentes.\n", MAX_COMPONENTES);
    
    while (count < MAX_COMPONENTES) {
        printf("\nComponente %d (ou digite 'fim'):\n", count + 1);
        
        // Pergunta se deseja continuar
        printf("Nome do componente: ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break; 
        }
        removerNovaLinha(input);
        
        if (strcasecmp(input, "fim") == 0) { // strcasecmp para ser case insensitive
            break;
        }
        
        // Armazena o nome
        strncpy(componentes[count].nome, input, 29);
        componentes[count].nome[29] = '\0'; // Garantir terminação

        // Tipo
        printf("Tipo (ex: controle, suporte, propulsão): ");
        if (fgets(componentes[count].tipo, sizeof(componentes[count].tipo), stdin) == NULL) break;
        removerNovaLinha(componentes[count].tipo);

        // Prioridade
        printf("Prioridade (1 a 10): ");
        if (scanf("%d", &componentes[count].prioridade) != 1) {
            printf("Prioridade inválida. Componente não cadastrado.\n");
            limparBuffer();
            continue;
        }
        limparBuffer();

        if (componentes[count].prioridade < 1 || componentes[count].prioridade > 10) {
            printf("A prioridade deve estar entre 1 e 10. Componente não cadastrado.\n");
            continue;
        }

        count++;
    }
    
    *tamanho = count;
    printf("\n%d componentes cadastrados com sucesso.\n", *tamanho);
}

// --- 6. Montagem Final (Exibição) ---
/**
 * @brief Exibe a lista formatada de componentes.
 * @param componentes O array de structs a ser exibido.
 * @param tamanho O número de componentes.
 */
void mostrarComponentes(Componente componentes[], int tamanho) {
    if (tamanho == 0) {
        printf("Nenhum componente para exibir.\n");
        return;
    }
    
    printf("\n| %-30s | %-20s | %-10s |\n", "Nome", "Tipo", "Prioridade");
    printf("|--------------------------------|----------------------|------------|\n");
    for (int i = 0; i < tamanho; i++) {
        printf("| %-30s | %-20s | %-10d |\n", 
               componentes[i].nome, 
               componentes[i].tipo, 
               componentes[i].prioridade);
    }
    printf("|--------------------------------|----------------------|------------|\n");
}

// --- Funções de Ordenação (com Medição de Desempenho) ---

/**
 * @brief Ordena os componentes por NOME usando Bubble Sort.
 * @param componentes O array de structs a ser ordenado.
 * @param tamanho O número de componentes.
 * @return O número total de comparações realizadas.
 */
long bubbleSortNome(Componente componentes[], int tamanho) {
    long comparacoes = 0;
    Componente temp;
    int trocou;

    for (int i = 0; i < tamanho - 1; i++) {
        trocou = 0;
        for (int j = 0; j < tamanho - 1 - i; j++) {
            // Comparação de Strings (Nome)
            comparacoes++;
            if (strcmp(componentes[j].nome, componentes[j + 1].nome) > 0) {
                // Troca
                temp = componentes[j];
                componentes[j] = componentes[j + 1];
                componentes[j + 1] = temp;
                trocou = 1;
            }
        }
        // Otimização: se não houve troca nesta iteração, o array está ordenado
        if (!trocou) break; 
    }
    return comparacoes;
}

/**
 * @brief Ordena os componentes por TIPO usando Insertion Sort.
 * @param componentes O array de structs a ser ordenado.
 * @param tamanho O número de componentes.
 * @return O número total de comparações realizadas.
 */
long insertionSortTipo(Componente componentes[], int tamanho) {
    long comparacoes = 0;
    int i, j;
    Componente atual;

    for (i = 1; i < tamanho; i++) {
        atual = componentes[i];
        j = i - 1;

        // Move os elementos maiores que 'atual.tipo' para a direita
        while (j >= 0) {
            // Comparação de Strings (Tipo)
            comparacoes++;
            if (strcmp(componentes[j].tipo, atual.tipo) > 0) {
                componentes[j + 1] = componentes[j];
                j--;
            } else {
                break; // Parar se encontrou a posição correta
            }
        }
        componentes[j + 1] = atual;
    }
    return comparacoes;
}

/**
 * @brief Ordena os componentes por PRIORIDADE usando Selection Sort.
 * @param componentes O array de structs a ser ordenado.
 * @param tamanho O número de componentes.
 * @return O número total de comparações realizadas.
 */
long selectionSortPrioridade(Componente componentes[], int tamanho) {
    long comparacoes = 0;
    int i, j, min_idx;
    Componente temp;

    for (i = 0; i < tamanho - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < tamanho; j++) {
            // Comparação de Inteiros (Prioridade)
            comparacoes++;
            if (componentes[j].prioridade > componentes[min_idx].prioridade) { 
                // Usamos '>' para ordenar em ordem decrescente (Prioridade 10 é mais alta)
                min_idx = j;
            }
        }

        // Troca o elemento encontrado com o primeiro elemento não ordenado
        if (min_idx != i) {
            temp = componentes[i];
            componentes[i] = componentes[min_idx];
            componentes[min_idx] = temp;
        }
    }
    return comparacoes;
}

// --- 4. Busca Binária ---
/**
 * @brief Realiza a busca binária por NOME (string) em um array *ordenado* de componentes.
 * @param componentes O array de structs (deve estar ordenado por nome).
 * @param tamanho O número de componentes.
 * @param chave O nome do componente a ser buscado.
 * @return O índice do componente encontrado, ou -1 se não for encontrado.
 */
int buscaBinariaPorNome(Componente componentes[], int tamanho, const char chave[]) {
    int esquerda = 0;
    int direita = tamanho - 1;

    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        int comparacao = strcmp(componentes[meio].nome, chave);

        if (comparacao == 0) {
            // Encontrado!
            return meio;
        } else if (comparacao < 0) {
            // Chave está à direita
            esquerda = meio + 1;
        } else {
            // Chave está à esquerda
            direita = meio - 1;
        }
    }
    return -1; // Não encontrado
}

// --- Funções de Controle e Desempenho ---

/**
 * @brief Executa o algoritmo de ordenação escolhido e exibe o desempenho.
 * @param componentes O array de structs a ser operado.
 * @param tamanho O número de componentes.
 * @param escolha A opção de ordenação (1, 2 ou 3).
 */
void executarOrdenacao(Componente componentes[], int tamanho, int escolha) {
    long numComparacoes = 0;
    clock_t inicio, fim;
    char *algoritmoNome = "";
    char *criterio = "";

    inicio = clock();
    
    switch (escolha) {
        case 1:
            numComparacoes = bubbleSortNome(componentes, tamanho);
            algoritmoNome = "Bubble Sort";
            criterio = "Nome";
            break;
        case 2:
            numComparacoes = insertionSortTipo(componentes, tamanho);
            algoritmoNome = "Insertion Sort";
            criterio = "Tipo";
            break;
        case 3:
            numComparacoes = selectionSortPrioridade(componentes, tamanho);
            algoritmoNome = "Selection Sort";
            criterio = "Prioridade (Decrescente)";
            break;
        default:
            return;
    }

    fim = clock();
    double tempoExecucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000; // Tempo em milissegundos

    // 5. Medição de Desempenho & 6. Montagem Final (Exibição)
    printf("\n--- RESULTADO DA ORDENAÇÃO ---\n");
    printf("Estratégia Escolhida: %s\n", algoritmoNome);
    printf("Critério de Ordenação: %s\n", criterio);
    
    // Desempenho Educacional
    printf("\n### Desempenho Educacional ###\n");
    printf("Total de Comparações: %ld\n", numComparacoes);
    printf("Tempo de Execução: %.4f milissegundos\n", tempoExecucao);
    
    printf("\nComponentes Ordenados:\n");
    mostrarComponentes(componentes, tamanho);
    printf("-------------------------------\n");
}
