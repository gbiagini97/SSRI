// O(n2) time complexity -> inefficient for large lists
// O(n) total, O(1) auxiliary space complexity
// In place, stable

// It's the basic exchange algorithm

void bubble_sort(int array[], int length)
{
    int i = 0;
    int k = 0;
    int temp;

    for (i = 0; i < length; i++)
    {
        for (j = 0; j < length-i-1; j++)
        {
            if (array[j] > array[j+1])
            {
                temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}