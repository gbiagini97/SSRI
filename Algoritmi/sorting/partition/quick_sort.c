// O(n2) time complexity
// O(n) or O(logn) auxiliary space complexity
// In place, not stable

// Divide and Conquer algorithm


// Low is the starting index and high is the ending index of the array
void quick_sort(int array[], int low, int high)
{
    if (low < high)
    {
        // pi is the Partition Index
        int pi = partition(array, low, high);

        // Separately sort elemenets before and after the partition index
        quick_sort(array, low, pi - 1);
        quick_sort(array, pi + 1, high);
    }
}

// This function takes the last element of the subarray as pivot
// Then places the pivot element at its correct position
// Every element smaller than the pivot is placed before it
// Every element bigger than the pivot is placed after it
int partition(int array[], int low, int high) 
{
    int pivot = array[high];
    int i = (low - 1);

    for(int j = low; j <= high - 1; j++)
    {
        if(array[j] < pivot)
        {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i+1], &array[high]);
    return (i+1);
}