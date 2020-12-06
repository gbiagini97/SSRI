```

A = [1, 5, 7, 8, 13, 17, 21, 27, 33, 37, 40, 42]
k = 13

Ricerca binaria
calcolo di m = floor[(i+j) / 2]


chiamata 1
i = 1
j = 12
m = 6
A[m] = 17


chiamata 2
i = 1
j = 5
m = 3
A[m] = 7

chiamata 3
i = 4
j = 5
m = 4
A[m] = 8

chiamata 4
i = 5
j = 5
m = 5
A[m] = 13 TROVATO

___

A = [1, 5, 7, 8, 13, 17, 21, 27, 33, 37, 40, 42]
k = 13

Interpolazione
calcolo di m = i + floor[(k - A[i]) * (j - i)/(A[j] - A[i]) ]

chiamata 1
i = 1
j = 12
m   = 1 + floor[(13 - 1) * (12 - 1) / (42 - 1)] 
    = 1 + floor[12 * 11 / 41]
    = 1 + 3
    = 4
A[m] = 8

chiamata 2
i = 5
j = 12
m   = 5 + floor[(13 - 13) * (12 - 5) / (42 - 13)]
    = 5 + floor(0)
    = 5
A[5] = 13 TROVATO

```