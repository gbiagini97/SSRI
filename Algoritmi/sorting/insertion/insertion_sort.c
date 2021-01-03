// O(n2) time complexity -> inefficient for large lists
// O(n) total, O(1) auxiliary space complexity
// In place, stable

// Very simple algorithm  

void iterativeInsertionSort(int array[], int length)
{
    for (int i = 1; i < length; i++)
    {
        int j = i-1;
        int key = array[i];

        while (j >=0 && key < array[j])
        {
            array[j+1] = array[j];
            j--;
        }

        array[j+1] = key;
    }
}

void recursiveInsertionSort(int array[], int length)
{
    recursiveInsertionSort(array, length-1);

    int j = length-2;
    int key = array[length-1];

    while (j >= 0 && key < array[j])
    {
        array[j+1] = array[j];
        j--;
    }

    array[j+1] = key;
}