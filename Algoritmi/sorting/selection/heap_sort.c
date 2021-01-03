// O(nlogn) time complexity
// O(n) total, O(1) auxiliary space complexity
// In place, not stable


// Unlike selection sort, heapsort doesn't do a linear-time scan of the unsorted region
// rather it maintains the unsorted region in a binary heap data structure.



void heapSort(int array[], int length)
{
    // Build heap (rearrange array)
    for (int i=(length/2)-1; i>=0; i--)
    {
        heapify(array, length, i);
    }

    // Extract elements from the heap one by one
    for(int i=length-1; i>0; i--)
    {
        // Move current to the end
        swap(array[0], array[i]);

        // Max heapify the reduced heap
        heapify(array, i, 0);
    }
}

// Heapify a subtree rooted with node i 
void heapify(int array[], int length, int i)
{
    int largest = i;        // Initialize the largest as root
    int left = 2*i + 1;
    int right = 2*i + 2;

    // If left child is larger than root
    if (left < length && array[left] > array[largest])
    {
        largest = left;
    }

    // If right child is larger than root
    if (right < length && array[right] > array[largest])
    {
        largest = right;
    }

    // If largest is not root
    if (largest != i)
    {
        swap(array[i], array[largest]);

        // Recursively heapify the affected sub-tree
        heapify(array, length, largest);
    }
}