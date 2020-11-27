Dizionario + implementazione con tabella di hash
problema delle collisioni + gestione
complessita' media operazioni su tabella di hash

numero di nodi/foglie in albero binario -> 2^(h+1) -1 / 2^h
fattore di bilanciamento un un BST
realizzazione grafi tramite matrici nodi-nodi/matrici nodi-archi/liste/vettori di adiacenza
BFS -> CODA
DFS -> PILA
BFS/DFS tipi di archi tree/back/forward/cross
BFS/DFS alberi di copertura 
ordinamento topologico dei grafi diretti aciclici
componenti connesse e fortemente connesse
grado di un nodo -> numero di archi incidenti
insiemi disgiunti (MFSET) -> euristiche
implementazione insiemi disgiunti + costo operazioni


### Tempo di calcolo
Il tempo di calcolo T(n) di un algoritmo e' dato dal costo complessivo delle operazioni elementari in funzione della dimensione n dei dati in input.
Le operazioni elementari sono tutte le operazioni aritmetiche, logiche, di confronto e di assegnamento che possono essere svolte all'interno di un algoritmo.

### Complessita' di un programma
La complessita' computazionale indica la quantita' di risorse richieste per l'esecuzione di un algoritmo in termini di tempo e spazio.
In particolare viene effettuata un'analisi asintotica associata dalla notazione O-grande in funzione delle risorse di tempo e spazio necessarie al crescere della dimensione dell'input.
L'esito di questa analisi e' una classificazione dell'algoritmo in questione.

### Definizione formale notazione O-grande
#### O-grande
f(n) ∈ O(g(n)) per n->∞ g e' un limite asintotico superiore di f (fino ad un fattore costante)

∃ k > 0, ∃ n0 ∀ n > n0 : 0 ≤ | f(n) | ≤ k ⋅ g(n) 

#### Omega
f(n) ∈ Ω(g(n)) per n->∞ g e' un limite asintotico inferiore di f

∃ k > 0, ∃ n0 ∀ n > n0 : f(n) ≥ k ⋅ g(n) ≥ 0

#### Theta
f(n) ∈ Θ(g(n)) per n->∞ g e' limite asintotico superiore ed inferiore di f

∃ k1 > 0, ∃ k2 > 0, ∃ n0 ∀ n > n0 : k1 ⋅ g(n) ≤ f(n) ≤ k2 ⋅ g(n)

#### o-piccolo
f(n) ∈ o(g(n)) per n->∞ g e' limite asintotico superiore stretto di f

∃ k > 0, ∃ n0 ∀ n > n0 : 0 < | f(n) | < k ⋅ g(n)

#### omega-piccolo
f(n) ∈ ω(g(n)) per n->∞ g e' un limite asintotico inferiore stretto di f

∃ k > 0, ∃ n0 ∀ n > n0 : f(n) > k ⋅ g(n) > 0


### Struttura dati Heap
L'Heap binario e' un'implementazione efficiente del tipo di dato coda di priorita' verificando le proprieta':
* Se h e' il livello massimo delle foglie, allora ci sono 2^(h) - 1 nodi di livello minore di h;
* Tutte le foglie di livello h sono addossate a sinistra;
* Ogni nodo diverso dalla radice contiene un elemento della coda di priorita' che soddisfa la relazione d'ordine applicata.

Nel Max-Heap le chiavi di chiascun nodo sono sempre maggiori o uguali a quelle dei figli, con valore massimo nella radice.

Nel Min-Heap le chiavi di ciascun nodo sono sempre minori o uguali a quelle dei figli, con valore minimo nella radice.

Assumendo la struttura dati Min-Heap:
* Ricerca del minimo ∈ Θ(1)
* Rimozione del minimo ∈ Θ(log(n))
* Inserimento ∈ Θ(log(n))
* Decremento di priorita' ∈ Θ(log(n))


### Heapsort
A partire da un array in ingresso si costruisce l'albero binario associato:

```
[3, 7, 1, 8, 2, 5, 9, 4, 6]

                        3
            7                           1
    8               2           5               9
4       6

```

Invoco la procedura heapify per costruire una struttura dati Max-Heap a partire dall'albero binario ottenuto (partendo dall'ultimo nodo padre):

```
Iterazione 1: il nodo 8 verifica le proprieta' di heap

                        3
            7                           1
    8               2           5               9
4       6

Iterazione 2: il nodo 1 viene scambiato con il suo figlio piu' grande (9)

                        3
            7                           9
    8               2           5               1
4       6

Iterazione 3: 7 viene scambiato con il suo figlio piu' grande (8) 

                        3
            8                           9
    7               2           5               1
4       6
-> vengono riverificate le proprieta' di heap nel sottoalbero di 7

Iterazione 4: 3 viene scambiato con il suo figlio piu' grande

                        9
            8                           3
    7               2           5               1
4       6
-> vengono riverificate le proprieta' di heap nel sottoalbero di 3: 3 viene scambiato con il suo figlio piu grande (5)

                        9
            8                           5
    7               2           3               1
4       6

Ora l'albero binario soddisfa le proprieta' di Max-Heap ed e' rappresentato dall'array:
[9, 8, 5, 7, 2, 3, 1, 4, 6]
```

Ordinamento dell'array:

```
Step 1: scambio la radice (9) con l'ultimo elemento dell'array / ultimo figlio (6)

                        6
            8                           5
    7               2           3               1
4       9

[6, 8, 5, 7, 2, 3, 1, 4, 9]

Step 2: rimuovo l'ultimo figlio dalla visualizzazione heap in quanto nell'array l'elemento si trova gia' nella sua posizione ordinata

                        6
            8                           5
    7               2           3               1
4

[6, 8, 5, 7, 2, 3, 1, 4, 9]

Step 3: restauro la condizione di heap 

(scambio 6 con 8)
                        8
            6                           5
    7               2           3               1
4

(scambio 6 con 7)
                        8
            7                           5
    6               2           3               1
4

```

A questo punto basta ripetere gli Step 1-3 per completare l'ordinamento all'interno dell'array rimuovendo dalla visualizzazione dell'heap un nodo alla volta.

Procedura in C:
```C
// O(nlogn) time complexity
// O(n) total, O(1) auxiliary space complexity
// In place, not stable

// Unlike selection sort, heapsort doesn't do a linear-time scan of the unsorted region
// rather it maintains the unsorted region in a binary heap data structure.

void heapSort(int array[], int length)
{
    // Build heap (rearrange array)
    for (int i=(length/2)-1; i>=0; i--)
    {
        heapify(array, length, i);
    }

    // Extract elements from the heap one by one
    for(int i=length-1; i>0; i--)
    {
        // Move current to the end
        swap(array[0], array[i]);

        // Max heapify the reduced heap
        heapify(array, i, 0);
    }
}

// Heapify a subtree rooted with node i 
void heapify(int array[], int length, int i)
{
    int largest = i;        // Initialize the largest as root
    int left = 2*i + 1;
    int right = 2*i + 2;

    // If left child is larger than root
    if (left < length && array[left] > array[largest])
    {
        largest = left;
    }

    // If right child is larger than root
    if (right < length && array[right] > array[largest])
    {
        largest = right;
    }

    // If largest is not root
    if (largest != i)
    {
        swap(array[i], array[largest]);

        // Recursively heapify the affected sub-tree
        heapify(array, length, largest);
    }
}
```

