#include <bits/stdc++.h>
using namespace std;

// 0 BASED INDEXING !!
// node -> i'th index
// left node -> 2*i+1
// right node -> 2*i+2
// parent node -> (i-1)/2

// Steps for heap sort
// 1) Build max heap
// 2) Apply heap sort logic-> Root element(max element) will get swapped with last index of array and that max element
// which is at last node in heap now, will be removed (size--) from the heap and swapped node which is at root will
// be heapified to it's appropriate position. In this way, the values at rootI(which will be maximum) will get swap 
// with last index of unsorted array

void heapifyMax(int i, int n, int arr[])
{
    // store initial node
    int node = i;
    // get left and right nodes
    int leftIndex = 2 * i + 1;
    int rightIndex = 2 * i + 2;

    // put current node at it's right place
    if (leftIndex < n && arr[leftIndex] > arr[node])
    {
        node = leftIndex;
    }
    if (rightIndex < n && arr[rightIndex] > arr[node])
    {
        node = rightIndex;
    }

    // if node changed, then do swap and again put swapped node at it's right place
    // by calling the function again
    /*If the maximum among the three nodes is the parent itself,
   that is Heap property satisfied so stop else call function recursively on Maxvalue node*/
    if (node != i)
    {
        swap(arr[node], arr[i]);
        heapifyMax(node, n, arr);
    }
}

void heapSort(int arr[], int n)
{
    // THIS also works, and is easy toooo
    // 1. Build max heap from given array so that element at 0th index will be maximum
    for (int i = (n / 2) - 1; i >= 0; i--)
    {
        heapifyMax(i, n, arr);
    }

    // 2. go on swapping element at 0th index with i (from back, as last element will get
    // filled from last)
    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        // Call the heapify function on root with reduced size of array to remove the largest element swapped now
        // in this iteration
        // size will go as 'i'. n-1, n-2, n-3, ... 1
        heapifyMax(0, i, arr);
    }

    // OR


    // int size = n;

    // while (size > 0)
    // {
    //     // step1 : swap largest element( at index 0) with last index i.e. last node in binary heap
    //     swap(arr[0], arr[size - 1]);

    //     // remove/delete that max element from heap as we have taken it in 'arr' and heapify the swapped node 
    //     // which is at root.
    //     size--;

    //     // step2: Move swapped node at index 0 (root) to it's appropriate position in max heap
    //     heapifyMax(0, size, arr);

    //     // in this way, the values at rootI(which will be maximum) will get swap with 
    //     // last index of unsorted array
    // }
}

int main()
{
    int arr[6] = {55, 34, 2, 100, 3, 1};
    int n = 6;

    // 1)  Build max heap!!!

    // leaf nodes are already heapified, so ignore them
    // leaf node are from n/2 to n-1
    // for (int i = n / 2 - 1; i >= 0; i--)
    // {
    //     heapifyMax(i, n, arr);
    // }

    // 2) Heap sort logic on max heap array!!

    
    heapSort(arr, n);

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
}
