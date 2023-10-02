->A Heap is a special Tree-based data structure in which the tree is a complete binary tree.
->Binary tree can have at most 2 child to a node
->In complete binary tree, all levels are completely filled except the last level and node always added from the left.

Why complete binary tree?
The fact that a heap is a complete binary tree allows it to be efficiently represented using a simple array.
Also, when we insert a node in heap, it will always get inserted from left (CBT) and can be easily heapified.
By maintaining binary heap as a complete binary gives multiple advantages such as 
1.heap is complete binary tree so height of heap is minimum possible i.e log(size of tree). And insertion, build heap operation depends on height. 
So if height is minimum then their time complexity will be reduced.
2.All the items of complete binary tree stored in contiguous manner in array so random access is possible and it also provide cache friendliness.


Generally, Heaps can be of two types:
Max-Heap: In a Max-Heap the key present at the root node must be greatest among the keys present at all of it’s children. The same property must be recursively true for all sub-trees in that Binary Tree.
Min-Heap: In a Min-Heap the key present at the root node must be minimum among the keys present at all of it’s children. The same property must be recursively true for all sub-trees in that Binary Tree.
Insertion and deletion in Maxheap :
TC - log(n)
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
        // on min heap or max heap
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
Heapify:
it converts an array into heap. Simply it builds heap in O(n)
Each non-leaf node may have one or two children, so on average, there are fewer than two swaps required per node. As we perform heapify operations on the non-leaf 
nodes, we end up performing a constant number of comparisons and swaps for each node.
we only call heapify function for 0 to n/2 - 1
because elements from n/2 to n-1 will be leaf elements and they are in their proper 

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

// Again

Max heap:
void heapify(vector<int>&arr, int index, int n){
    int largest = index;
    int left = 2*index + 1;
    int right = 2*index + 2;
    if(left < n && arr[left] > arr[largest]){
        largest = left;
    }
    if(right<n && arr[right] > arr[largest]){
        largest = right;
    }
    if(largest != index){
        swap(arr[largest],arr[index]);
        heapify(arr,largest,n);
    }
}
int main(){
    for(int i=n/2 - 1; i>=0; i--){
        heapify(arr,i,n);
    }
}

Min heap:
void heapify(vector<int>&arr, int index, int n){
    int smallest = index;
    int left = 2*index + 1;
    int right = 2*index + 2;
    if(left < n && arr[left] < arr[smallest]){
        smallest = left;
    }
    if(right<n && arr[right] < arr[smallest]){
        smallest = right;
    }
    if(smallest != index){
        swap(arr[smallest],arr[index]);
        heapify(arr,smallest,n);
    }
}
vector<int> buildMinHeap(vector<int> &arr)
{
    int n = arr.size();
    for(int i=n/2 - 1; i>=0; i--){
        heapify(arr,i,n);
    }
    return arr;
}
------------------------------------------------------------------------------	
Heap Sort:
Build a max heap: Start by constructing a max heap from the given array. This step ensures that the largest element is at the root of the heap.

Begin from the last non-leaf node (index n/2 - 1) and iterate backwards to the first element (index 0).
For each node, perform the heapify operation to establish the heap property.
After this step, the array will be transformed into a max heap.


Sort the array( heap sort): Perform the sorting process by repeatedly extracting the maximum element from the heap and placing it at the end of the array.

Starting from the last element (index n-1) of the array and moving backwards to the second element (index 1):
1) Swap the first element (root of the heap) with the current element.
2) Reduce the heap size by one.
3) Perform heapify on the root element to restore the heap property.
4) Repeat these steps until all elements have been extracted and placed in their correct positions.
The array is now sorted in ascending order.

The key idea behind Heap Sort is to use the heap data structure to efficiently extract the maximum element and build a sorted array from it. 
By leveraging the properties of the heap, Heap Sort achieves a time complexity of O(n log n), making it an efficient sorting algorithm.

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

    // go on swapping element at 0th index with i (from back, as maximum element will get
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
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapifyMax(i, n, arr);
    }

    // 2) Heap sort logic on max heap array!!
    heapSort(arr, n);

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
}

// Tejyaaaa->

void heapify(vector<int>&arr, int index, int n){
    int largest = index;
    int left = 2*index + 1;
    int right = 2*index + 2;
    if(left < n && arr[left] > arr[largest]){
        largest = left;
    }
    if(right<n && arr[right] > arr[largest]){
        largest = right;
    }
    if(largest != index){
        swap(arr[largest],arr[index]);
        heapify(arr,largest,n);
    }
}
void heapsort(vector<int>&arr, int n){
	int size = n;
	while( size > 0){
		swap(arr[0],arr[size-1]);
		size--;
		heapify(arr,0,size);
	}
}
vector<int> heapSort(vector<int>& arr, int n) {
	for(int i=n/2 - 1; i>=0; i--){
        heapify(arr,i,n);
    }
	heapsort(arr,n);
	return arr;
}
heap implementation:
https://techdose.co.in/heap-implementation-push-pop-code/

Max heap in STL:
priority_queue<int>pq;
pq.push()
pq.pop()
pq.top()

Min heap in STL:
priority_queue<int,vector<int>,greater<int>> pq;

A C++ priority queue is a type of container adapter, specifically designed such that the first element of the queue is either the greatest 
or the smallest of all elements in the queue, and elements are in non-increasing or non-decreasing order (hence we can see that each element 
of the queue has a priority {fixed order}). In C++ STL, the top element is always the greatest by default. We can also change it to the smallest 
element at the top. Priority queues are built on the top of the max heap and use an array or vector as an internal structure. In simple terms, 
STL Priority Queue is the implementation of Heap Data Structure.

Love babbar problems not taken by striver:
1)	Is tree a Heap
https://practice.geeksforgeeks.org/problems/is-binary-tree-heap/1

2)	Merge two binary Max heaps
https://practice.geeksforgeeks.org/problems/merge-two-binary-max-heap0144/1
 
3)	 Minimum Cost of ropes
https://practice.geeksforgeeks.org/problems/minimum-cost-of-ropes-1587115620/1

4)	Convert BST to Min Heap
https://www.codingninjas.com/studio/problems/convert-bst-to-min-heap_920498
	Get the Inorder of BST
	Copy the inorder tree, in preorder fashion.

5)	K-th Largest Sum Contiguous Subarray
https://practice.geeksforgeeks.org/problems/k-th-largest-sum-contiguous-subarray/1
	Same as kth largest element, instead of pushing element into pq, push each subarray sum.
	T.C -> N^2*logK

6)	Smallest Range Covering Elements from K Lists
https://leetcode.com/problems/smallest-range-covering-elements-from-k-lists/
	Keeping range as max - min + 1, if we get any smaller range, we update it.
	Max and min is the elements from pq.He
	T.C -> T*logK - T is number of elements in entire 2D array

7)	Find Median from Data Stream
https://leetcode.com/problems/find-median-from-data-stream/
	Brute force – Insertion sort taking N*N time. 
	Optimal -> N*logN using min and max heap both , where array is divided hypothetically into max heap and min heap, 
        max heap will store minimum elements and min heap will store maximum elements.

8)	Reorganize String
https://leetcode.com/problems/reorganize-string/description/
	Key as frequency.
	Pop two elements from pq, at a time
	Use max heap, and spread characters with most frequency in ans string.

Aditya Verma questions:
1)	Sort a k sorted array
https://practice.geeksforgeeks.org/problems/nearly-sorted-1587115620/1?utm_source=gfg&utm_medium=article&utm_campaign=bottom_sticky_on_article
Heap sorts the array in Time Complexity of N*log(K)
 
2)	Return k largest elements in an array
https://practice.geeksforgeeks.org/problems/k-largest-elements4206/1?utm_source=gfg&utm_medium=article&utm_campaign=bottom_sticky_on_article
	Just store the queue elements after performing the traversal from kth largest element

3)	Find K Closest Elements
https://leetcode.com/problems/find-k-closest-elements/
	Here we are kipping key as absolute difference!!
	We have to identify, that what should be the key!

4)	Top K Frequent Elements	
https://leetcode.com/problems/top-k-frequent-elements/
	Here we are kipping key as frequency of elements!!

5)	Frequency sort
https://leetcode.com/problems/sort-array-by-increasing-frequency/
	We can use priority queue, by keeping key as a frequency, if there is no such condition that if frequency is same then store them in decreasing/increasing fashion (reverse of how the frequency has to sorted). But if there is some reverse condition when frequency is same, then we need to use vector of pair and sort it using comparator function.

6)	K Closest Points to Origin
https://leetcode.com/problems/k-closest-points-to-origin
	Key as distance of vertex from origin!!

7)	Sum of elements between k1'th and k2'th smallest elements
https://practice.geeksforgeeks.org/problems/sum-of-elements-between-k1th-and-k2th-smallest-elements3133/1?utm_source=gfg&utm_medium=article&utm_campaign=bottom_sticky_on_article
	Find k1th and k2th smallest elements
	Sum up elements between those two elements exclusively


Is Binary Tree Heap
https://practice.geeksforgeeks.org/problems/is-binary-tree-heap/1
Merge two binary Max heaps
https://practice.geeksforgeeks.org/problems/merge-two-binary-max-heap0144/1
Minimum Cost of ropes
https://practice.geeksforgeeks.org/problems/minimum-cost-of-ropes-1587115620/1
Convert BST to Min Heap
https://www.codingninjas.com/studio/problems/convert-bst-to-min-heap_920498?leftPanelTab=1
K-th Largest Sum Subarray
https://www.codingninjas.com/codestudio/problems/k-th-largest-sum-contiguous-subarray_
Find K Closest Elements
https://leetcode.com/problems/find-k-closest-elements/description/
Top K Frequent Elements
https://leetcode.com/problems/top-k-frequent-elements/description/
Sort Array by Increasing Frequency
https://leetcode.com/problems/sort-array-by-increasing-frequency/submissions/980012035/
K Closest Points to Origin
https://leetcode.com/problems/k-closest-points-to-origin/description/
Minimum Cost of ropes
https://practice.geeksforgeeks.org/problems/minimum-cost-of-ropes-1587115620/1
Sum of elements between k1'th and k2'th smallest elements
https://practice.geeksforgeeks.org/problems/sum-of-elements-between-k1th-and-k2th-smallest-elements3133/1
Rearrange string
https://www.codingninjas.com/studio/problems/rearrange-string_982765?leftPanelTab=1&utm_source=youtube&utm_medium=affiliate&utm_campaign=Lovebabbar\
Smallest Range From K Sorted List
https://www.codingninjas.com/studio/problems/smallest-range-from-k-sorted-list_1069356?leftPanelTab=1&utm_source=youtube&utm_medium=affiliate&utm_campaign=Lovebabbar
IPO
https://leetcode.com/problems/ipo/description/
Maximum Frequency Stack
https://leetcode.com/problems/maximum-frequency-stack/description/