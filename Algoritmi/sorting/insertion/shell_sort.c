// O(n2) time complexity -> worst case gap sequence
// O(n) total, O(1) auxiliary space complexity
// In place, not stable

// Optimization of the insertion sort

void shellsort(int array[], int length)
{
    int i, j, k, temp;
    for(i = length/2; i > 0; i = i/2)
    {
        for(j = i; j < length; j++)
        {
            for(k = j-i; k >= 0; k = k-i)
            {
                if(array[k+i] >= array[k])
                    break;
                else
                {
                    {
                        temp = array[k];
                        array[k] = array[k+i];
                        array[k+i] = temp;
                    }
                }
            }
        }
    }
}