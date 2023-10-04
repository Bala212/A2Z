1) Selection sort

#Select minimums and swap!!

void selectionSort(vector<int>&arr) {
    int n = arr.size();
    // loop from 0 to n-2, as we do n-1 iterations bcoz last element will be already
    // sorted!!
    for(int i = 0;i<=n-2;i++){
        // find minimum value index from  i to n-1.
        int mini = i;
        for(int j = i;j<=n-1;j++){
            if(arr[j] < arr[mini]) mini = j;
        }
        // swap arr[i] and arr[mini]
        int temp = arr[i];
        arr[i] = arr[mini];
        arr[mini] = temp;		
    }
}

No, selection sort is NOT STABLE. A sorting algorithm is considered stable if it 
maintains the relative order of elements with equal values. In other words, 
if two elements have the same value and appear in a particular order in the 
input, a stable sorting algorithm will ensure that they remain in the same 
order in the output.

However, in selection sort, when searching for the minimum element to swap with 
the current position, there is no consideration for the relative order of elements 
with equal values. As a result, if there are multiple occurrences of the same value 
in the list, their relative order may change after the sorting process.

The key idea behind selection sort is that it progressively selects the smallest 
elements and places them in the correct order, one by one, until the entire list 
is sorted. Although simple, selection sort has a time complexity of O(n^2), which 
makes it less efficient compared to more advanced sorting algorithms like merge 
sort or quicksort. However, its simplicity makes it easy to understand and 
implement, especially for small lists or educational purposes.

Time complexity: O(N*N), for the best, worst, and average cases.
Space complexity: O(1)

************************************************************************************************************************************
2) Bubble sort

#Pushes the largest to the last, by swapping the adjacents.

The bubble sort algorithm is a simple sorting algorithm that repeatedly compares 
adjacent elements and swaps them if they are in the wrong order. This process is 
repeated until the entire list is sorted.

Article vaach!!

void bubbleSort(vector<int>& arr, int n) {
    // loop from n-1 to 0, to set range for inner loop
    for(int i = n-1;i>=0;i--){
        // flag to optimise
        bool swap = 0;
        // loop from 0 to i-1; 0 to n-2, 0 to n-3... and so on
        for(int j = 0;j<=i-1;j++){
            // swap if left ele is greater than right.
            if(arr[j] > arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                swap = 1;
            }
        }
        // If no swaps, array is already sorted so break
        if(!swap) break;
    }
}


Recursive:
void bubble_sort(int arr[], int n) {
    // Base Case: range == 1.
    if (n == 1) return;

    for (int j = 0; j <= n - 2; j++) {
        if (arr[j] > arr[j + 1]) {
            int temp = arr[j + 1];
            arr[j + 1] = arr[j];
            arr[j] = temp;
        }
    }

    //Range reduced after recursion:
    bubble_sort(arr, n - 1);
}
Note: Here, after each iteration, the array becomes sorted up to the last index of the range. 
That is why the last index of the range decreases by 1 after each iteration. 
This decrement is achieved by the outer loop and the last index is represented by variable i in the following code. 
And the inner loop(i.e. j) helps to push the maximum element of range [0….i] to the last index(i.e. index i).

Yes, bubble sort is a STABLE sorting algorithm. A sorting algorithm is considered 
stable if it maintains the relative order of elements with equal values. In other 
words, if two elements have the same value and appear in a particular order in 
the input, a stable sorting algorithm will ensure that they remain in the same 
order in the output.

Bubble sort compares adjacent elements and swaps them if they are in the wrong 
order. During the sorting process, when two adjacent elements are equal, the algorithm
only swaps them if their relative order needs to be adjusted. In this case, the elements 
are swapped when the one on the left is greater than the one on the right. By only 
swapping elements when necessary, bubble sort preserves the relative order of equal elements.

Time complexity: O(N*N), (where N = size of the array), for the worst, and average cases.
Best Case: O(N), obviously after optimization.

Optimization: Bubble sort can be optimized by adding a flag to track whether any 
swaps were made during an iteration. If no swaps were made in a pass, it indicates 
that the list is already sorted, allowing us to terminate the algorithm early. 
This optimization reduces the number of unnecessary comparisons and iterations.

************************************************************************************************************************************
3) Insertion sort
#Takes an element an place it in it's correct position.

a) Swapping->
#include <bits/stdc++.h> 
void insertionSort(int n, vector<int> &arr){
    // loop from 0 to n-1, as we have to pick each element and
    // place it in it's correct position
    for (int i = 0; i <= n - 1; i++) {
        // Take i, as we have to place it!!
        int j = i;
        // loop till j is 1( avoid 0, as we are accessing j-1) and 
        // left element is greater than current element
        // and swap left element and current element.
        while (j > 0 && arr[j - 1] > arr[j]) {
            int temp = arr[j - 1];
            arr[j - 1] = arr[j];
            arr[j] = temp;
            j--;
        }
    }
}

Recursive:
#include <bits/stdc++.h> 
void f(int i, vector<int> &arr, int n){

    if(i == n) return ;

    // Take i, as we have to place it!!
    int j = i;
    // loop till j is 1( avoid 0, as we are accessing j-1) and 
    // left element is greater than current element
    // and swap left element and current element.
    while (j > 0 && arr[j - 1] > arr[j]) {
        int temp = arr[j - 1];
        arr[j - 1] = arr[j];
        arr[j] = temp;
        j--;
    }

    f(i+1, arr, n);

}

void insertionSort(int n, vector<int> &arr){
    int i = 1;
    f(0,arr,n);
}



b) Shifting->
#include <bits/stdc++.h> 
void insertionSort(int n, vector<int> &arr){
    // Pick an element from 1 to n-1.
    for(int i = 1; i <= n-1; i++){
        // Current element to be inserted in the sorted part
        int ele = arr[i];  
        
        // Index of the last element in the sorted part
        int j = i-1;  
        
        // Shift elements in the sorted part to the right until the correct position for 'ele' is found
        while(j >= 0 && ele < arr[j]){
            // Shift element to the right
            arr[j+1] = arr[j];  
            j--;
        }
      
        // Insert 'ele' into the correct position in the sorted part
        arr[j+1] = ele;  
    }
}

Recursive:
#include <bits/stdc++.h> 

void f(int i, vector<int> &arr, int n){

    if(i == n) return ;

    // Current element to be inserted in the sorted part
    int ele = arr[i];  
    
    // Index of the last element in the sorted part
    int j = i-1;  
    
    // Shift elements in the sorted part to the right until the correct position for 'ele' is found
    while(j >= 0 && ele < arr[j]){
        // Shift element to the right
        arr[j+1] = arr[j];  
        j--;
    }
    
    // Insert 'ele' into the correct position in the sorted part
    arr[j+1] = ele; 

    f(i+1, arr, n);

}

void insertionSort(int n, vector<int> &arr){
    int i = 1;
    f(i,arr,n);
}


The key idea behind insertion sort is to build the sorted part of the list gradually, one element at a time. 
By continuously inserting elements into their appropriate positions, the sorted part expands until it encompasses 
the entire list. Insertion sort has a time complexity of O(n^2), making it less efficient than some other 
sorting algorithms for large lists. However, it performs well on small or nearly sorted lists, and its simplicity
and efficiency for small inputs make it a viable option in certain scenarios.

Yes, insertion sort is a STABLE sorting algorithm. A sorting algorithm is considered stable 
if it maintains the relative order of elements with equal values. In other words, if two elements 
have the same value and appear in a particular order in the input, a stable sorting algorithm 
will ensure that they remain in the same order in the output.

In insertion sort, when inserting an element into the sorted part of the list, if there are 
multiple elements with equal values, the algorithm compares and shifts them to the right until 
it finds the correct position to insert the new element. This process ensures that elements with 
equal values are inserted in the same order as they appeared in the original list, preserving their relative order.


Time complexity: O(N*N), (where N = size of the array), for the worst, and average cases.
Best Case: O(N), as while loop will not run, if the array is already sorted.

************************************************************************************************************************************
4) Merge sort

Divide divide divide and then merge sortedly!!
The intuition behind merge sort is to divide the unsorted array into smaller 
subarrays, recursively sort them, and then merge the sorted subarrays to obtain 
the final sorted array.

The merge sort algorithm follows these steps:
1. Divide the unsorted array into two halves.
2. Recursively sort the left half.
3. Recursively sort the right half.
4. Merge the sorted left and right halves to create a sorted merged array.

By repeatedly dividing the array and sorting the smaller subarrays, merge sort 
takes advantage of the divide-and-conquer approach. The key operation is the 
merge step, where two sorted subarrays are merged into a larger sorted array. 
This process is repeated until the entire array is sorted.

The main advantage of merge sort is that it guarantees a time complexity of 
O(n log n) for sorting, regardless of the initial order of the elements. It is a STABLE
sorting algorithm, meaning that the relative order of elements with equal values 
is preserved. However, merge sort requires additional memory for the temporary 
array used during the merging process.

Preserving order during merging: When merging two sublists, if there are equal elements in the input, 
merge sort ensures that the elements from the first sublist are placed before the elements from the 
second sublist. Since merge sort merges the sublists in a stable manner, equal elements retain their 
relative order. SO MERGE SORT IS STABLE ALGORITHM.


void merge(vector<int> &arr, int low, int mid, int high) {
    vector<int> temp;  // Temporary array to store sorted elements
    int left = low;     // Pointer for the left subarray
    int right = mid+1; // Pointer for the right subarray

    // Merfge the two subarrays by comparing elements
    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right])
            temp.push_back(arr[left++]); // Add element from the left subarray
        else
            temp.push_back(arr[right++]); // Add element from the right subarray
    }

    // Add any remaining elements from the left subarray
    while (left <= mid) {
        temp.push_back(arr[left++]);
    }

    // Add any remaining elements from the right subarray
    while (right <= high) {
        temp.push_back(arr[right++]);
    }

    // Copy the sorted elements from the temporary array back to the original array
    for (int i = low; i <= high; i++) {
        arr[i] = temp[i - low]; // i-l-> l-l -> 0
                              // i+1-l-> l+1-l -> 1 and so on
    }
}

void mergeSort(vector<int>& arr, int low, int high) {
    // Initially, low = 0 and r = n-1!!
    if (low >= high) {
        return; // Base case: If the subarray has only one element or is empty, no sorting is needed
    }

    int mid = low - (low - high) / 2; // Calculate the middle index of the subarray

    // Recursively divide the array into two halves and sort them
    mergeSort(arr, low, mid);       // Sort the left half
    mergeSort(arr, mid + 1, high);  // Sort the right half
    merge(arr, low, mid, high);     // Merge the two sorted halves
}

Time complexity: O(nlogn) if n = 16, there will be 4 divisions.(16 = 2^4)
Reason: At each step, we divide the whole array, for that logn and we assume n steps are taken to get 
sorted array, so overall time complexity will be nlogn

Space complexity: O(n)  
Reason: We are using a temporary array to store elements in sorted order.

Auxiliary Space Complexity: O(n)
************************************************************************************************************************************
5) Quick sort

1) Pick a pivot( can be any element) and place it in its correct place in the sorted 
   array.
2) Shift smaller elements(i.e. Smaller than the pivot) on the left of the pivot and 
   larger ones to the right.

The intuition behind quicksort is to divide the array into two partitions based on a 
chosen pivot element, such that elements smaller than the pivot are placed to its 
left, and elements greater than the pivot are placed to its right. This process is then 
recursively applied to the subarrays on the left and right of the pivot until the entire 
array is sorted.

The quicksort algorithm follows these steps:
1. Choose a pivot element from the array (usually the first or last element).
2. Reorder the array such that all elements smaller than the pivot are placed to its 
   left, and all elements greater than the pivot are placed to its right.
3. Recursively apply steps 1 and 2 to the subarray on the left of the pivot and the 
   subarray on the right of the pivot.
4. Continue the recursion until each subarray contains only one element or is empty.

int partitionArray(int arr[], int low, int high) {
    int i = low;
    int j = high;

    // Choose the pivot as the element at the low index
    int pivot = arr[low];

    // Perform the partitioning of the array
    while (i < j) {
        // Find the first element from the left that is greater than the pivot
        while (i < high && arr[i] <= pivot)
            i++;

        // Find the first element from the right that is smaller than or equal to the pivot
        while (j >= low && arr[j] > pivot)
            j--;

        // If there are elements on both sides that are out of place, swap them
        if (i < j) {
            swap(arr[i], arr[j]);
        }
    }

    // The indices i and j have crossed each other,
    // so swap the pivot with the element at index j
    // j will now be the correct position of the pivot
    swap(arr[low], arr[j]);

    // Return the index of the pivot
    return j;
}

void quickSort(int arr[], int low, int high) {
    // Initially, low = 0 and high = n-1!!
    if (low < high) {
        // Partition the array and obtain the index of the pivot
        int partitionIndex = partitionArray(arr, low, high);

        // Recursively sort the subarray to the left of the pivot
        quickSort(arr, low, partitionIndex - 1);

        // Recursively sort the subarray to the right of the pivot
        quickSort(arr, partitionIndex + 1, high);
    }
}



No, the QuickSort algorithm is NOT STABLE. A sorting algorithm is considered stable if it preserves 
the relative order of elements with equal values. In other words, if there are two elements in the 
original array that have the same value, and one appears before the other, then in a stable sorting 
algorithm, the element that appeared first will still appear first in the sorted array.

In the QuickSort algorithm, during the partitioning step, the relative order of elements with equal 
values may change. When swapping elements to partition the array, there is no guarantee that elements 
with equal values will maintain their original order. As a result, QuickSort is not stable

Time Complexity: O(N*logN), where N = size of the array.
Reason: At each step, we divide the whole array, for that logN and n steps are taken for the partition() 
	function, so overall time complexity will be N*logN.

The following recurrence relation can be written for Quick sort : 

F(n) = F(k) + F(n-1-k) 

Here k is the number of elements smaller or equal to the pivot and n-1-k denotes elements greater than the pivot.

There can be 2 cases :

Worst Case – This case occurs when the pivot is the greatest or smallest element of the array. If the partition is done and the last element is the 
             pivot, then the worst case would be either in the increasing order of the array or in the decreasing order of the array. 

Recurrence:
F(n) = F(0)+F(n-1)  or  F(n) = F(n-1) + F(0) 

Worst Case Time complexity: O(n2) 

Best Case – This case occurs when the pivot is the middle element or near to middle element of the array.
Recurrence :
F(n) = 2F(n/2)
----------------
Time Complexity for the best and average case: O(N*logN)
Worst Case Time complexity: O(N*N) 

Space Complexity: O(1) + O(N) auxiliary stack space.
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++










