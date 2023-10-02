#include <bits/stdc++.h>
using namespace std;

// 0 BASED INDEXING !!
// node -> i'th index
// left node -> 2*i+1
// right node -> 2*i+2
// parent node -> (i-1)/2
void heapifyMax(int i, int n, int arr[])
{
    // We will go level-wise from bottom to up and check whether the current node’s
    // left or right children are greater or not. If anyone of them is greater, we
    // will swap
    
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

// USING WHILE LOOP
// while (i < size)
// {
//     // calculate left and right node indexes
//     int node = i;
//     int leftIndex = 2 * i + 1;
//     int rightIndex = 2 * i + 2;

//     // if left node is greater than parent node and right node, swap them
//     // in case of min heap, just reverse the comparisons
//     if (leftIndex < size && arr[leftIndex] > arr[node])
//     {
//         node = leftIndex;
//     }
//     // if right node is greater than parent node and left node, swap them
//     else if (rightIndex < size && arr[rightIndex] > arr[i])
//     {
//         node = rightIndex;
//     }

//     if (node != i)
//     {
//         swap(arr[node], arr[i]);
//         i = node;
//     }
//     else
//         break;
// }

void heapifyMin(int i, int n, int arr[])
{
    // store initial node
    int node = i;
    // get left and right nodes
    int leftIndex = 2 * i + 1;
    int rightIndex = 2 * i + 2;

    // put current node at it's right place
    if (leftIndex < n && arr[leftIndex] < arr[node])
    {
        node = leftIndex;
    }
    // if left is less, then we replace node as left, and in below line node(which is left) is compared
    //  with right !!!!
    if (rightIndex < n && arr[rightIndex] < arr[node])
    {
        node = rightIndex;
    }

    // if node changed, then do swap and again put swapped node at it's right place
    // by calling the function again
    /*If the Minimum among the three nodes is the parent itself,
   that is Heap property satisfied so stop else call function recursively on Minvalue node*/
    if (node != i)
    {
        swap(arr[node], arr[i]);
        heapifyMin(node, n, arr);
    }
}

void increaseKey(int index, int arr[])
{
    while (index > 0)
    {
        int parent = (index - 1) / 2;
        // min heap -> arr[index] < arr[parent]
        // max heap -> arr[index] > arr[parent]
        if (arr[index] > arr[parent])
        {
            swap(arr[parent], arr[index]);
            // Now node has gone at parent position, so again check for heap property for that parent position
            // by setting index as parent
            index = parent;
        }
        // if no more swapping happens, the property of heap order is satisfied!!
        else
            break;
    }
}
int main()
{
    int arr[6] = {55, 34, 2, 100, 3, 1};
    int n = 6;

    // leaf nodes are already heapified, so ignore them
    // leaf node are from n/2 to n-1

    // We will start loop from n/2-1 i.e. (from bottom elements) because we have to
    // also give positions to leaf node as will, and heapify funtion will compare
    // left and right i.e. leaf nodes so it is necessary to start from n/2-1 and go to 0
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapifyMax(i,n, arr);
    }

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
}