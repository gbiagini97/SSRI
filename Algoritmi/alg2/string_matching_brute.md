```C
// *T testo in cui cercare
// n lunghezza del testo T

// *P pattern da cercare
// m lunghezza del pattern P

// k misura l'avanzare in T della verifica dell'eventuale matching
// i misura la scansione all'interno del testo T
// j misura la scansione all'interno del pattern P

int ricercabruta(char *P, char *T, int n, int m) {
    int i, j, k;
    i = j = k = 1;

    while(i <= n && j <= m) {
        if(T[i] == P[j]) {
            i++; j++;
        } else {
            k++;
            i = k = j = 1;
        }
    }

    return ((j > m ? k : i));
}
```

Nel caso pessimo sono effettuati O(nm) confronti tra caratteri di P e T.

Esempio:
```
P = pattern = un c
m = 4

T = testo = Montresor e' un coglione
n = 24


cerco un k per cui:
P[j] = T[k+j-1]
con j da 1 a m

da 0  al carattere prima di 'u' non trova niente
k = 12
j = 1

appena incontro il carattere 'u'
P[1] = 'u' = T[13+1-1] = 'u' ? true

P[2] = 'n' = T[13+2-1] = 'n' ? true

P[3] = ' ' = T[13+3-1] = ' ' ? true

P[4] = 'c' = T[13+4-1] = 'c' ? true

match effettuato

return k = 13
```