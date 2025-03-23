//
// Created by lucas on 23/03/2025.
//

#include "../include/node.h"
#include <stdarg.h>

// Função para adicionar uma aresta na lista de adjacência do autômato
node *push(node *first, char edgetype, int data)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->edgetype = edgetype;
    new_node->data = data;
    new_node->next = first;
    return new_node;
}

// Função recursiva para verificar a aceitação da palavra inserida no autômato
int nfa(node **graph, int current, char *input, int *accept, int start)
{
    if (start == (int)strlen(input))
        return accept[current];

    node *temp = graph[current];
    while (temp != NULL)
    {
        if (input[start] == temp->edgetype)
            if (nfa(graph, temp->data, input, accept, start + 1))
                return 1;
        temp = temp->next;
    }
    return 0;
}
