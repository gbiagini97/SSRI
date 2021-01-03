
#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

//Lista bidirezionale circolare
typedef struct head
{
    struct node *first;
} head;

typedef struct node
{
    int key;
    struct node *next, *prev;
} node;

head *crealista()
{
    head *testa = (head *)malloc(sizeof(head));
    return testa;
} // return empty list

int listavuota(head *lista)
{
    if (lista->first == NULL)
        return true;
    else
        return false;
} // checks first element of list

node *primolista(head *lista)
{
    if (lista->first != NULL)
        return lista->first;
}

node *ultimolista(head *lista)
{
    int index = 0;
    node *first = primolista(lista);
    return first->prev;
}

node *inslista(int key, int position, head *lista)
{
    if (position == 0)
    {
        node *newFirstNode = (node *)malloc(sizeof(node)); //alloco nuovo primo nodo
        lista->first = newFirstNode; //la testa avra' come primo nodo il nuovo primo nodo
        newFirstNode->prev = primolista(lista)->prev; // metto come puntatore precedente quello dell'ex primo nodo
        //primolista(lista)->prev = newFirstNode; // l'ex primo nodo avra' come puntatore precedenre il nuovo primo nodo

        newFirstNode->key = key;

        return newFirstNode;
    }
    else
    {
        node *newNode = (node *)malloc(sizeof(node));
        newNode->key = key;

        node *cursor = lista->first;
        for (int i = 0; i < position - 1; i++)
        {
            if (cursor->next != primolista(lista) && cursor->next != NULL)
            {
                node *newNode = (node *)malloc(sizeof(node));
                cursor->next = newNode;
                newNode->prev = cursor;
            }
            cursor = cursor->next;
        }

        node *prev, *next;
        prev = cursor;

        next = cursor->next;

        prev->next = newNode;
        newNode->prev = prev;

        next->prev = newNode;
        newNode->next = next;

        return newNode;
    }
}

void printlista(head *lista) {
    printf("\n");

    node *nodo = primolista(lista); 
    while(nodo != NULL) {
        printf("%d\n", nodo->key);
        nodo = nodo->next;
    }

    printf("\n");
}

int main() {
    head *lista = crealista();

    node *val1 = inslista(0, 0, lista);
    printlista(lista);
    node *val2 = inslista(1, 1, lista);
    printlista(lista);
    node *val3 = inslista(2, 2, lista);
    
    printlista(lista);
    return(0);

}

