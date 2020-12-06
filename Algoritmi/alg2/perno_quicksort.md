Calcolo del perno su un array

```C
int perno(int[] A, int primo, int ultimo)  {
    int x = A[primo]
    int j = primo
    for (i = primo; i<=ultimo; i++) {
        if(A[i] < x) {
            j++;
            swap(A[i], A[j])
        }
    }
    A[primo] = A[j];
    A[j] = x;
    return j;
}
```


A = [9, 12, 8, 18, 6, 13, 11, 3, 5, 10]
primo = 1
ultimo = 10

x = 9
j = 1

___

Iterazione 1
i = 1

Iterazione 2
i = 2

Iterazione 3
i = 3
j = 2
swap(A[3], A[2])
A = [9, 8, 12, 18, 6, 13, 11, 3, 5, 10]

Iterazione 4
i = 4

Iterazione 5
i = 5
j = 3
swap(A[5], A[3])
A = [9, 8, 6, 18, 12, 13, 11, 3, 5, 10]

Iterazione 6
i = 6

Iterazione 7
i = 7

Iterazione 8
i = 8
j = 4
swap(A[8], A[4])
A = [9, 8, 6, 3, 12, 13, 11, 18, 5, 10]

Iterazione 9
i = 9
j = 5
swap(A[9], A[5])
A = [9, 8, 6, 3, 5, 13, 11, 18, 12, 10]

Iterazione
i = 10

___

A[primo] = A[j] = A[5]
(A[1] = 5)

A[j] = A[5] = x
(A[j] = 9)

A = [5, 8, 6, 3, 9, 13, 11, 18, 12, 10]


return j
(return 5)