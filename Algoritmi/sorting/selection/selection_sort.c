// O(n2) time complexity -> inefficient for large lists
// O(1) auxiliary space complexity
// In place, not stable

// Overall very simple algorithm that works well when auxiliary memory is limited

int selectionSort(int array[], int length) 
{
    int i, j;
    int tmp;
    int min;

    for (i = 0; i < length-1; i++)
    {
        min = i; // current minimum

        for (j = i+1; j < length; j++) 
        {
            if (array[j] < array[min]) 
            {
                min = j; // new minimum
            }
        }

        // swap elements in the array
        tmp = array[i];
        array[i] = array[min];
        array[min] = tmp;
    }

    return 0;
}