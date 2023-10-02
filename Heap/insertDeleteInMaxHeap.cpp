#include <bits/stdc++.h>
using namespace std;

// MAX HEAP

// 0 BASED INDEXING !!
// node -> i'th index
// left node -> 2*i+1
// right node -> 2*i+2
// parent node -> (i-1)/2

// HEAPIFY WILL PUSH THE NODE FROM TOP TO BOTTOM (at right place).
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

class Heap
{
public:
    int arr[100];
    int size;
    Heap()
    {
        size = 0;
    }

    // Pushes the node from bottom to it's right place by comparing with parent
    void increaseKey(int index)
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

    void insert(int val)
    {
        // Insert the node in heap
        arr[size] = val;
        int index = size;
        // increse the size of array to accept next insertion
        size++;

        // Assign inserted node it's wright position by swapping nodes if greater or lesser, depending
        // on min heap or max heap, Basically, push the element upwards to it's right
        // position
        increaseKey(index);
    }

    void deleteRoot()
    {
        if (size == 0)
        {
            cout << "Nothing to delete!";
            return;
        }

        // step1: put last element into first index
        arr[0] = arr[size - 1];

        // step2: remove last element
        size--;

        // step3: take root to it's correct position, i.e. heapify the root node!!
        heapifyMax(0, size, arr);

        // can be done using hepify too, to bring the root at it’s right position
        // below logic can also be called as heapify
        int i = 0;
        while (i < size)
        {
            // calculate left and right node indexes
            int node = i;
            int leftIndex = 2 * i + 1;
            int rightIndex = 2 * i + 2;

            // if left node is greater than parent node and right node, swap them
            // in case of min heap, just reverse the comparisons
            if (leftIndex < size && arr[leftIndex] > arr[node])
            {
                node = leftIndex;
            }
            // if right node is greater than parent node and left node, swap them
            if (rightIndex < size && arr[rightIndex] > arr[node])
            {
                node = rightIndex;
            }

            if (node != i)
            {
                swap(arr[node], arr[i]);
                i = node;
            }
            else
                break;
        }

        // BELOW IS BIT LENGTHY, BUT EASILY UNDERSTANDABLE WE ARE CHECKING FOR LEFT AND
        // RIGHT AT ONE TIME
        // while (i < size)
        // {
        //     // calculate left and right node indexes
        //     int leftIndex = 2 * i + 1;
        //     int rightIndex = 2 * i + 2;

        //     // if left node is greater than parent node and right node, swap them
        //     // in case of min heap, just reverse the comparisons
        //     if (leftIndex < size && arr[leftIndex] > arr[i] && arr[leftIndex] > arr[rightIndex])
        //     {
        //         swap(arr[leftIndex], arr[i]);
        //         i = leftIndex;
        //     }
        //     // if right node is greater than parent node and left node, swap them
        //     else if (rightIndex < size && arr[rightIndex] > arr[i] && arr[rightIndex] > arr[leftIndex])
        //     {
        //         swap(arr[rightIndex], arr[i]);
        //         i = rightIndex;
        //     }
        //     // else the fall under property, break the loop
        //     else
        //         break;
        // }
    }

    // This function deletes an element at the specified index from the array-based
    // min-heap data structure. It follows a process that involves marking the element
    // as deleted by setting it to INT_MAX, then restoring the heap properties through
    // a combination of "increaseKey" and "deleteRoot" operations.
    void deleteAtIndex(int index)
    {
        // Mark the element at the given index as deleted by assigning it the maximum
        // possible integer value. This is done to preserve the overall structure of
        // the heap while indicating that the element is no longer part of the heap.
        arr[index] = INT_MAX;

        // Restore the heap properties after marking the element as deleted. The
        // "increaseKey" operation is performed on the marked element, allowing it to
        // bubble up to its appropriate position in the heap. It will go to root as it is
        // INT_MAX
        increaseKey(index);

        // After the marked element has been properly positioned by the "increaseKey"
        // operation, perform a "deleteRoot" operation to remove the root (maximum)
        // element of the heap. This operation involves swapping the root with the
        // last leaf node, removing the last leaf node, and then heapifying the heap
        // to maintain its structure.
        deleteRoot();
    }

    void print()
    {
        for (int i = 0; i < size; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    Heap h;
    h.insert(1);
    h.insert(6);
    h.insert(10);
    h.insert(4);
    h.insert(5);
    h.print();
    h.deleteAtIndex(3);
    h.print();

    h.deleteRoot();
    h.print();
    h.deleteRoot();
    h.print();
    return 0;
}