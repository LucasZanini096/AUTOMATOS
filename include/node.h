//
// Created by lucas on 23/03/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef NODE_H
#define NODE_H

struct node
{
    int data;
    struct node *next;
    char edgetype;
};
typedef struct node node;

node *push(node *first, char edgetype, int data);

int nfa(node **graph, int current, char *input, int *accept, int start);


#endif //NODE_H