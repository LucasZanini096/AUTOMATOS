#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar um nó da lista de adjacência
struct node {
    int data;
    struct node* next;
    char edgetype;
};
typedef struct node node;

// Função para adicionar uma aresta na lista de adjacência
node* push(node* first, char edgetype, int data) {
    node* new_node = (node*)malloc(sizeof(node));
    new_node->edgetype = edgetype;
    new_node->data = data;
    new_node->next = first;
    return new_node;
}

// Função recursiva para verificar a aceitação da palavra
int nfa(node** graph, int current, char* input, int* accept, int start) {
    if (start == (int)strlen(input))
        return accept[current];

    node* temp = graph[current];
    while (temp != NULL) {
        if (input[start] == temp->edgetype)
            if (nfa(graph, temp->data, input, accept, start + 1))
                return 1;
        temp = temp->next;
    }
    return 0;
}

// Função principal
int main() {
    char alfabeto[50];
    int n, num_finais, num_transicoes, num_palavras;
    int i, j;

    // Leitura do alfabeto
    scanf("%s", alfabeto);

    // Número de estados
    scanf("%d", &n);
    node* graph[n + 1];
    for (i = 0; i <= n; i++)
        graph[i] = NULL;

    // Número de estados finais
    scanf("%d", &num_finais);
    int accept[n + 1];
    memset(accept, 0, sizeof(accept));
    //Utilização da função memset para filtrar um bloco de memória com um valor específico

    // Leitura dos estados finais
    for (i = 0; i < num_finais; i++) {
        int final_state;
        scanf("%d", &final_state);
        accept[final_state] = 1;
    }

    // Número de transições
    scanf("%d", &num_transicoes);
    for (i = 0; i < num_transicoes; i++) {
        int origem, destino;
        char simbolo;
        scanf("%d %c %d", &origem, &simbolo, &destino);
        graph[origem] = push(graph[origem], simbolo, destino);
    }

    // Número de palavras a serem testadas
    scanf("%d", &num_palavras);
    for (i = 0; i < num_palavras; i++) {
        char palavra[100];
        scanf("%s", palavra);
        if (nfa(graph, 0, palavra, accept, 0))
            printf("%s: aceita\n", palavra);
        else
            printf("%s: rejeitada\n", palavra);
    }

    return 0;
}
