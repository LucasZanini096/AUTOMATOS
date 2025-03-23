//
// Created by lucas on 23/03/2025.
//

#include "../include/readData.h"
#include "../include/node.h"
#include <stdarg.h>

// Função para a realização de uma leitura de uma linha de um arquivo
void read_line(FILE *file, int line_index, const char *mask, ...)
{
    if (file == NULL)
    {
        printf("Erro ao ler o arquivo.\n");
        return;
    }

    fseek(file, 0, SEEK_SET);

    char buffer[MAX_LINE_LENGTH];
    int current_line = 1;
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        if (current_line == line_index)
        {
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n')
                buffer[len - 1] = '\0';

            va_list args;
            va_start(args, mask);
            vsscanf(buffer, mask, args);
            va_end(args);
            return;
        }
        current_line++;
    }
    printf("O arquivo tem menos de %d linhas.\n", line_index);
}

//Definição de uma função para realizar a entrada de dados por meio do teclado
void interative_mode(void)
{
    char alfabeto[50];
    int n, num_finais, num_transicoes, num_palavras;
    int i;

    // Leitura do alfabeto
    scanf("%s", alfabeto);

    // Número de estados
    scanf("%d", &n);
    node *graph[n + 1];
    for (i = 0; i <= n; i++)
        graph[i] = NULL;

    // Número de estados finais
    scanf("%d", &num_finais);
    int accept[n + 1];
    memset(accept, 0, sizeof(accept));
    // Utilização da função memset para filtrar um bloco de memória com um valor específico

    // Leitura dos estados finais
    for (i = 0; i < num_finais; i++)
    {
        int final_state;
        scanf("%d", &final_state);
        accept[final_state] = 1;
    }

    // Número de transições
    scanf("%d", &num_transicoes);
    for (i = 0; i < num_transicoes; i++)
    {
        int origem, destino;
        char simbolo;
        scanf("%d %c %d", &origem, &simbolo, &destino);
        graph[origem] = push(graph[origem], simbolo, destino);
    }

    // Número de palavras a serem testadas
    scanf("%d", &num_palavras);
    for (i = 0; i < num_palavras; i++)
    {
        char palavra[100];
        scanf("%s", palavra);
        if (nfa(graph, 0, palavra, accept, 0))
            printf("%s: aceita\n", palavra);
        else
            printf("%s: rejeitada\n", palavra);
    }
}

//Função para realizar a leitura de informações por meio de um arquivo
void file_mode(void)
{
    FILE *file = fopen("in.txt", "r");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Leitura do alfabeto
    char alfabeto[50];
    read_line(file, 1, "%s", alfabeto);

    // Número de estados
    int n;
    read_line(file, 2, "%d", &n);
    node *graph[n + 1];

    for (int i = 0; i <= n; i++)
        graph[i] = NULL;

    int accept[n + 1];
    memset(accept, 0, sizeof(accept));

    // Número de estados finais
    int num_finais;
    read_line(file, 3, "%d", &num_finais);

    char finais_linha[MAX_LINE_LENGTH];
    read_line(file, 4, "%[^\n]", finais_linha);

    char *token = strtok(finais_linha, " ");
    for (int i = 0; i < num_finais && token != NULL; i++)
    {
        int final_state = atoi(token);
        accept[final_state] = 1;
        token = strtok(NULL, " ");
    }

    // Número de transições
    int num_transicoes;
    int num_transicoes_linha = 5;
    read_line(file, num_transicoes_linha, "%d", &num_transicoes);
    for (int i = 1; i <= num_transicoes; i++)
    {
        int origem, destino;
        char simbolo;
        read_line(file, num_transicoes_linha + i, "%d %c %d", &origem, &simbolo, &destino);
        graph[origem] = push(graph[origem], simbolo, destino);
    }

    // Número de palavras a serem testadas
    int num_palavras;
    int num_palavras_linha = num_transicoes_linha + num_transicoes + 1;
    read_line(file, num_palavras_linha, "%d", &num_palavras);
    for (int i = 1; i <= num_palavras; i++)
    {
        char palavra[MAX_LINE_LENGTH];
        read_line(file, num_palavras_linha + i, "%s", &palavra);

        if (nfa(graph, 0, palavra, accept, 0))
            printf("%d: %s OK\n", i, palavra);
        else
            printf("%d: %s not OK\n", i, palavra);
    }
}