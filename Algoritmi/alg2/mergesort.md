Mergesort

array = [33, 21, 7, 48, 28, 13, 65, 17]

left = 0
right = 7



// Prima esecuzione
left < right ? true
median = 3

mergesort(array, 0, 3)

mergesort(array, 4, 7)

merge(array, 0, 3, 7)


// CHIAMATA_A_MERGESORT (array, 0, 3)
left = 0
right = 3

left < right ? true
median = 1
mergesort(array, 0, 1)
mergesort(array, 2, 3)
merge(array, 0, 1, 3)

// CHIAMATA_A_MERGESORT(array, 0, 1)
left = 0
right = 1

left < right ? true
median = 0
mergesort(array, 0, 0)
mergesort(array, 1, 1)
merge(array, 0, 0, 1)

// CHIAMATA_A_MERGESORT(array, 0, 0)
left = 0
right = 0
left < right ? false
STOP

___

// CHIAMATA_A_MERGE(array, 0, 0, 1)
//sottoarray = [33, 21]

n1 = 1
n2 = 1

L[1], R[1]

L[0] = 33
R[0] = 21

i = 0
j = 0
k = left = 0

L[0] <= R[0] ? false
array[0] = 21
j = 1

k = 1

array[1] = L[i] = L[0] = 33

// sottoarray = [21, 33]

___

// CHIAMATA_A_MERGE(array, 0, 1, 3)
// sottoarray = [21, 33, 7, 48]

n1 = 2
n2 = 2

L[2], R[2]

L[0] = 21
L[1] = 33

R[0] = 7
R[1] = 48

i = 0 
j = 0
k = left = 0

//prima iterazione while
0 < 2 & 0 < 2 ? true
    L[i] = L[0] = 21 <= R[j] = R[0] = 7 ? false
        array[k] = array[0] = R[j] = R[0] = 7
        j = 1
    k = 1

//seconda iterazione while
0 < 2 & 1 < 2 ? true
    L[i] = L[0] = 21 <= R[j] = R[1] = 48 ? true
        array[k] = array[1] = L[i] = L[0] = 21
        i = 1
    k = 2

//terza iterazione while
1 < 2 & 1 < 2 ? true
    L[i] = L[1] = 33 <= R[j] = R[1] = 48 ? true
        array[k] = array[2] = L[i] = L[1] = 33
        i = 2
    k = 3

// il while si ferma perche non soddisfa la prima condizione

// copiamo gli elementi rimanenti del sottoarray R[]
j = 1 < n2 = 2 ? true
    array[k] = array[3] = R[j] = R[1] = 48
    j = 2
    k = 4

// si ferma il while
// termina la procedura merge

// sottoarray = [7, 21, 33, 48]