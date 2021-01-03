// O(nlogn) time complexity
// O(n) total with O(n) auxiliary, O(1) auxiliary with linked lists
// Not in place, stable

// Divide and Conquer algorithm

// Left and right are the fist and last indexes of the subarray of array to be sorted
void merge_sort(int array[], int left, int right)
{
    if (left < right)
    {
        // Same as (right+left)/2 but avoids overflow for large left and right
        int median = left + (right - left) / 2;

        // Sort first and second halves
        merge_sort(array, left, median);
        merge_sort(array, median+1, right);

        merge(array, left, median, right);
    }
}

// Merges two subarray of array[]
void merge(int array[], int left, int median, int right)
{
    int i, j, k;
    int n1 = median - left + 1;
    int n2 = right - median;

    // Create temp arrays
    int L[n1], R[n2];

    // Copy data to temp arrays
    for (i = 0; i < n1; i++)
        L[i] = array[left+i];
    for (j = 0; j < n2; j++)
        R[j] = array[median+1+j];

    // Merge the temp arrays back into the main array
    i = 0; 
    j = 0; 
    k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j]) 
        {
            array[k] = L[i];
            i++;
        }

        else
        {
            array[k] = R[j];
            j++;
        }

        k++;
    }

    /* Copy the remaining elements of L[], if there are any */
    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[] if there are any
    while (j < n2)
    {
        array[k] = R[j];
        j++;
        k++;
    }
}