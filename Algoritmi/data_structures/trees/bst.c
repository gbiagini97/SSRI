#include<stdio.h>
#include<stdlib.h>


#define true 1
#define false 0

typedef struct node {
    int key;
    struct node *left, *right, *father;
} node;

node* creabinalbero();

int binalberovuoto(node *nodo);

node* binradice(node *nodo);

node* binpadre(node *nodo);

node* cancsottobinalbero(node *nodo);

int legginodo(node *nodo, node *tree) {
    
    return nodo->key;
}

node* scrivinodo(int key, node *nodo, node *tree);


