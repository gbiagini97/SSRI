
#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0


//Lista monodirezionale
typedef struct head {
    struct node *first;
} head;


typedef struct node {
    int key;
    struct node *next;
} node;



head *crealista() {
    head* testa = (head*) malloc(sizeof(head));
    return testa;
} // return empty list


int listavuota(head *lista) {
    if(lista->first == NULL)
        return true;
    else 
        return false;
} // checks first element of list

node *primolista(head *lista) {
    if(lista->first != NULL)
        return lista->first;
}

node *ultimolista(head *lista) {
    int index = 0;
    node *first = primolista(lista);

    while(first->next != NULL) {
        first = first->next;
    }
    return first;
}

node *inslista(int key, int position, head *lista) {
    
    node *nodo = (node*) malloc(sizeof(node));
    nodo->key=key;

    // si rompe se la lista e' vuota
    node *cursor = lista->first;

    for(int i = 0; i < position - 1; i++) {
        if(cursor->next == NULL) {
            node *newNode =  (node*) malloc(sizeof(node));
            cursor->next = newNode;
        }
        cursor = cursor->next;
    }

    nodo->next = cursor->next;
    cursor->next = nodo;
    
    return nodo;
}

head *canclista(int position, head *lista) {

    node *cursor = primolista(lista);
    node *prev;
    node *next;

    if(position == 0) {
        lista->first = cursor->next;
        free(cursor);
    } else {
        int i = 1;
        while(i < position && cursor->next != NULL) {
            cursor = cursor->next;
            i++;
        }

        prev = cursor;
        next = cursor->next->next;
        
        free(cursor->next);
        prev->next = next;

    }

    return lista;
}



void printlista(head *lista) {
    printf("\n\n");

    node *nodo = primolista(lista); 
    while(nodo != NULL) {
        printf("%d\n", nodo->key);
        nodo = nodo->next;
    }

    printf("\n\n");
}

int main() {
    head *lista = crealista();
    

    node *nodo = (node*) malloc(sizeof(node));
    nodo->key = 1;
    lista->first = nodo;
    node *val1 = inslista(2, 2, lista);
    node *val3 = inslista(3, 3, lista);
    node *val2 = inslista(4, 4, lista);

    printlista(lista);
    head *testaee = canclista(0, lista);
    printlista(lista);
    head *testae = canclista(1, lista);


    if (listavuota(lista)) {
        printf("La lista e' vuota\n");
    } else {
        printf("La lista non e' vuota\n");
    }


    printlista(lista);
    return(0);

}

/* 
listavuota(L) = b
post: vero solo se L = Λ
primolista(L) = p
post: p = posizione1
ultimolista(L) = p
post: p = posizionen
succlista(p, L) = q
pre: L = a1, a2, ..., an; p = posi, 1<=i<=n
post: q = posi+1
predlista(p, L) = q
pre: L = a1, a2, ..., an; p = posi, 1<=i<=n
post: q = posi-1
finelista(p, L) = b
pre: L = a1, a2, ..., an; p = posi, 0<=i<=n+1
post: b vero solo se p = pos0 o posn+1
leggilista(p, L) = a
pre: L = a1, a2, ..., an; p = posi, 1<=i<=n
post: a = ai
scrivilista(a, p, L) = L'
pre: L = a1, a2, ..., an; p = posi, 1<=i<=n
post: L' = a1, a2, ..., ai-1, a, ai+1, ..., an
inslista(a, p, L) = L'
pre: L = a1, a2, ..., an; p = posi, 0<=i<=n+1
post:
L' = a1, a2, ..., ai-1, a, ai+1, ..., an se 1<=i<=n;
L' = a1, ..., an, a se i = n + i;
L' = a, a1, ..., an se i = 0
canclista(p, L) = L'
pre: L = a1, a2, ..., an; p = posi, 1<=i<=n
post:L' = a1, a2, ..., ai-1, a, ai+1, ..., an */