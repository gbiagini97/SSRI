T = 1101100111
P = 111

KMP(P[], T[], 10, 3)
int i, j, back[]

// chiamata a calcola_back
calcola_back(P[], back[], 3)
int j, h
back[1] = 0

j = 1
h = 0

// prima iterazione while
// P = 111

h == 0 ? true
j = 2
h = 1

P[j] == P[h] ? true
back[j] = back[2] = back[h] = back[1] = 0

// seconda iterazione del while
// P = 111

P[j] == P[h] ? true
j = 3
h = 2

P[j] == P[h] ? true
back[j] = back[3] = back[h] = back[2] = back[1] = 0

// terza iterazione del while
// 111

P[j] == P[h] ? true
j = 4
h = 3

P[j] == P[h] ? false
back[j] = back[4] = 3

// fine while
// fine chiamata a calcola_back
// back = [0, 0, 0, 3]

i = j = 1

// prima iterazione del while
// T = 1101100111
// P = 111
(i <= n && j <= m) = (1 <= 10 && 1 <= 3) ? true
(j == 0 || T[i] == P[j]) = (j == 0 || T[1] == P[1]) ?  true
i = j = 2

// seconda iterazione del while
// T = 1101100111
// P = 111
(i <= n && j <= m) = (2 <= 10 && 2 <= 3) ? true
(j == 0 || T[i] == P[j]) = (j == 0 || T[2] == P[2]) ?  true
i = j = 3

// terza iterazione del while
// T = 1101100111
// P = 111
(i <= n && j <= m) = (3 <= 10 && 3 <= 3) ? true
(j == 0 || T[i] == P[j]) = (j == 0 || T[3] == P[3]) ?  false
i = 3
j = back[j] = back[3] = 0

// quarta iterazione del while
// T = 1101100111
// P = 111
(i <= n && j <= m) = (3 <= 10 && 0 <= 3) ? true
(j == 0 || T[i] == P[j]) = (j == 0 || T[3] == P[0]) ?  false
i = 3
j = back[j] = back[3] = 0



```C
int KMP(char *P, char *T, int n, int m) {
    int i, j, *back;
    /* back viene allocato come vettore */
    calcola_back(P, back, m);

    i = j = 0;

    while(i <= n && j <= m) {
        if(j == 0 || T[i] == P[j]) {
            i++; j++;
        } else
            j = back[j];
    }

    return ((j > m ? i - m : i));
}


void calcola_back(char *P, int *back, int m) {
    int j, h;

    back[0] = 0;
    j = 1;
    h = 0;

    while (j < m) {
        if(h == 0 || P[j] == P[h]) {
            j++; h++;
            back[j] = (P[j] == P[h] ? back[h] : h);
        } else
            h = back[h];
    }
}
```