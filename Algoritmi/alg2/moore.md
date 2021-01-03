# Algoritmo di Moore

## Definizione
L'algoritmo di Moore fa uso della tecnica greedy per risolvere problemi di scheduling dei programmi.

### Struttura
Step:
1. I programmi sono ordinati in una sequenza S per scadenze crescenti;
2. Si cerca il primo programma p in ritardo;
3. Si elimina il programma p' piu' lungo nella sottosequenza iniziale di S che termina con p;
4. La procedura e' iterata in modo da eseguire per primi i programmi che possono essere terminati entro la loro di scadenza, per poi eseguire tutti quelli scaduti in ordine qualsiasi;

### Complessita'

#### Senza heap modificato O(n<sup>2</sup>)
A seconda della scelta implementativa si puo' ottenere un algoritmo non efficiente che costa O(n<sup>2</sup>): 
* Per tutti i programmi p della sequenza S vengono calcolati gli istanti in cui terminano la loro esecuzione -> O(n);
* Si confrontano gli instanti di terminazione dei programmi con le relative scadenze per determinare il programma p in ritardo e quindi eliminare il programma p'piu' lungo -> O(n);
   * Poiche' la procedura di cancellazione va iterata per O(n) volte -> O(n<sup>2</sup>).

#### Con heap modificato O(nlogn)
Se invece si utilizza una procedura che fa uso di una struttura dati heap modificata affinche' possa trattare programmi e non elementi normali tenendo conto della priorita' per far scendere la complessita' totale a O(nlogn):
* L'ordinamento iniziale costa O(nlogn);
* L'inserimento dei programmi all'interno della coda di priorita' e il relativo controllo di superamento delle scadenze costa O(nlogn) in quanto l'inserimento e la cancellazione richiedono O(logn).


### Pseudocodice
```C
// d = scadenze da rispettare dei programmi
// t = tempi di esecuzione dei programmi
// n = numero di programmi
// r = eventuali ritardi dei programmi

int moore(integer[] d, integer[] t, int n, boolean[] r) {
    PriorityQueue Q = PriorityQueue();
	
    int i;      //indice programma corrente
    int j;      //var di appoggio per programmi con costo elevato
    int k = 0;  //numero dei programmi in ritardo
    int T = 0;  //somma dei tempi di esecuzione dei programmi precedenti
    
    for(i = 0; i < n; i++)
        r[i] = false;
        
	{ ordina il vettore d ed il vettore t per scadenze crescenti }
    
    for(i = 0; i < n; i++) {
		Q.Insert(i, t[i])
        T += t[i]
        
        if (T >= d[i]) {
			// estrae e cancella da Q il programma con tempo di esecuzione maggiore
            j = Q.deleteMax()
            
            T -= t[j]
            r[j] = true
            k++
        }
    } 
    return k
}
```