typedef struct nodo {
  int valore;
  struct nodo *padre, *primofiglio, *succfratello;
} nodo;

typedef *nodo albero ; 


val somma = 0;
void sommanodo(nodo u, albero *T, int sommaparziale) {
    
    somma += u->val

    if(foglia(u, T)){
        creanodo(u, somma)
        while(u->succfratello != null){
            sommanodo(u->succfratello, *T, somma)
        }
    } else {
        nodo v = u->primofiglio
        sommanodo(v, *T, somma)       
    }
}



/* Si  richiede  di  scrivere  (pseudocodice)  un  algoritmo  che,
dato  un  array  dinnumeri  interi  non  ordinato,
restituisca un albero binario di ricerca bilanciato 
contente gli stessi elementi dell’array.
Osservazione:  usare  l’istruzione  “crea  nodo  x”  per  
creare  un  nodo  corrispondente  ad  un  record  
con  tre campi (key, left, right).
 */

typedef struct nodo {
    int key;
    struct nodo *sx;
    struct nodo *dx;
    int h;
} nodo;

typedef *nodo albero;

int void main() {
    T = albero
    foreach elem in array {
        inserisci(elem, T)
    }
}

albero inserisci(int elem, albero T) {
    if (T == null) {
        creanodo(elem, T)
    } else {
        if (elem < T->key) {
            T->sx = inserisci(elem, T->sx)
            T = Ribilancia-sx(T)
        } 
        else if (elem > T->key) {
            T->dx = inserisci(elem, T->dx)
            T = Ribilancia-dx(T)
        }
        else {
            // elem e' gia' presente
        }
    }

    return T
}


nodo creanodo(int elem, albero T){
    alloca nodo
    nodo->key = elem
    nodo->sx = null
    nodo->dx = null
    nodo->h = 0
    
    return(nodo)
}