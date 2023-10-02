1. Find the Largest element in an array
int largest(vector<int> &arr, int n)
{
    int ans = -1e9;
    for (int i = 0; i < n; i++)
    {
        ans = max(ans, arr[i]);
    }
    return ans;
}
//! T.C-> O(N)
//! S.C-> O(1)
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
2. Find Second Smallest and Second Largest Element in an array

// Second largest
int print2largest(int arr[], int n)
{
    // code here
    int max = -1;
    int second_max = -1;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > max)
        {
            second_max = max;
            max = arr[i];
        }
	// Lasct check is to handle duplicates!!
        else if (arr[i] > second_max && arr[i] != max)
        {
            second_max = arr[i];
        }
    }
    return second_max;
}

// second smallest
int secondSmallest(int arr[], int n)
{
    if (n < 2)
        return -1;
    int small = INT_MAX;
    int second_small = INT_MAX;
    int i;
    for (i = 0; i < n; i++)
    {
        if (arr[i] < small)
        {
            second_small = small;
            small = arr[i];
        }
        else if (arr[i] < second_small && arr[i] != small)
        {
            second_small = arr[i];
        }
    }
    return second_small;
}
//T.C-> O(N)
//S.C-> O(1)
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
3.Check if an Array is Sorted

bool isSorted(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        if (arr[i] < arr[i - 1])
            return false;
    }

    return true;
}
//T.C-> O(N)
//S.C-> O(1)
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
4.Remove Duplicates in-place from Sorted Array

int removeDuplicates(int arr[], int n)
{
    int i = 0;
    for (int j = 1; j < n; j++)
    {
        if (arr[i] != arr[j])
        {
            i++;
            arr[i] = arr[j];
        }
    }
    return i + 1;
}
//T.C-> O(N)
//S.C-> O(1)
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
5.Left Rotate the Array by One
void solve(int arr[], int n)
{
    int temp = arr[0]; // storing the first element of array in a variable
    for (int i = 0; i < n - 1; i++)
    {
        arr[i] = arr[i + 1];
    }
    arr[n - 1] = temp; // assigned the value of variable at the last index
}
//T.C-> O(N)
//S.C-> O(1)
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
6.Rotate array by K elements

#For Rotating the Elements to left

// Approach 1: Using a temp array
// Step 1: Copy the first k elements into the temp array.
// Step 2: Shift n-k elements from last by k position to the left
// Step 3: Copy the elements into the main array from the temp array.

void Rotatetoleft(int arr[], int n, int k)
{
    if (n == 0)
        return;
    k = k % n;
    if (k > n)
        return;
    int temp[k];
    for (int i = 0; i < k; i++)
    {
        temp[i] = arr[i];
    }
    for (int i = 0; i < n - k; i++)
    {
        arr[i] = arr[i + k];
    }
    for (int i = n - k; i < n; i++)
    {
        arr[i] = temp[i - n + k];
    }
}
//T.C-> O(N+K)
//S.C-> O(1)

// Approach 2: Using ” Reversal Algorithm “
// Step 1: Reverse the first k elements of the array
// Step 2: Reverse the last n-k elements of the array.
// Step 3: Reverse the whole array.

// Function to Reverse the array
void Reverse(int arr[], int start, int end)
{
    while (start <= end)
    {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}
// Function to Rotate k elements to left
void Rotateeletoleft(int arr[], int n, int k)
{
    // Reverse first k elements
    Reverse(arr, 0, k - 1);
    // Reverse last n-k elements
    Reverse(arr, k, n - 1);
    // Reverse whole array
    Reverse(arr, 0, n - 1);
}
//T.C-> O(N)
//S.C-> O(1)
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
7. Move all Zeros to the end of the array

// i will point to first zero element and j will point to i+1, then i will be used for replacing 
// non-zero numbers with i index everytime and increment i, and j will find the non-zero 
// elements to get replaced with ith index

// i chya adhi sagle elements non-zero pahije

    void moveZeroes(vector<int>& nums) {
        int i = -1;
        int n = nums.size();
        for(int k=0;k<n;k++){
            if(nums[k] == 0) {
                i = k;
                break;
            }
        }

        if(i == -1) return;
        int j = i + 1;
        while(j<n){
            if(nums[j] != 0){
                swap(nums[i], nums[j]);
                i++;
            }
            j++;
        }
    }

//T.C-> O(N)
//S.C-> O(1)
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 8. Linear Search
int search(int arr[], int n, int num)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (arr[i] == num)
            return i;
    }
    return -1;
}
//T.C-> O(N)
//S.C-> O(1)

---------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 9.Union of Two Sorted Arrays
vector<int> FindUnion(int arr1[], int arr2[], int n, int m)
{
    int i = 0, j = 0;  // pointers

    vector<int> Union; // Uninon vector
    while (i < n && j < m)
    {
        if (arr1[i] <= arr2[j]) // Case 1 and 2
        {
            if (Union.size() == 0 || Union.back() != arr1[i])
                Union.push_back(arr1[i]);
            i++;
        }
        else // case 3
        {
            if (Union.size() == 0 || Union.back() != arr2[j])
                Union.push_back(arr2[j]);
            j++;
        }
    }

    while (i < n) // IF any element left in arr1
    {
        if (Union.back() != arr1[i])
            Union.push_back(arr1[i]);
        i++;
    }

    while (j < m) // If any elements left in arr2
    {
        if (Union.back() != arr2[j])
            Union.push_back(arr2[j]);
        j++;
    }
    return Union;
}

// T.C-> O(M+N)
// S.C -> O(M+N)
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
10.Find the missing number in an array
// 1. Summation approach
// 2. XOR(^) approach
int missingNumber(vector<int> &a, int N)
{

    // Summation of first N numbers:
    int sum = (N * (N + 1)) / 2;

    // Summation of all array elements:
    int s2 = 0;
    for (int i = 0; i < N; i++)
    {
        s2 += a[i];
    }

    int missingNum = sum - s2;
    return missingNum;
}
int missingNumber(vector<int> &nums)
{
    int ans = 0;
    int n = nums.size();
    for (int i = 0; i < n; i++)
    {
        ans ^= (i + 1) ^ nums[i];
    }
    return ans;
}
//! T.C-> O(N)
//! S.C-> O(1)
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 11.Count Maximum Consecutive One’s in the array
int findMaxConsecutiveOnes(vector<int> &nums)
{
    int cnt = 0;
    int maxi = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] == 1)
        {
            cnt++;
        }
        else
        {
            cnt = 0;
        }
        maxi = max(maxi, cnt);
    }
    return maxi;
}
//! T.C-> O(N)
//! S.C-> O(1)
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 12.Find the number that appears once, and the other numbers twice
int getSingleElement(vector<int> &arr)
{
    // size of the array:
    int n = arr.size();

    // XOR all the elements:
    int xorr = 0;
    for (int i = 0; i < n; i++)
    {
        xorr = xorr ^ arr[i];
    }
    return xorr;
}
//!T.C-> O(N)
//!S.C-> O(1)
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 13.Longest Subarray with given Sum K (Positives)
int getLongestSubarray(vector<int> &a, long long k)
{
    int n = a.size(); // size of the array.

    int left = 0, right = 0; // 2 pointers
    long long sum = a[0];
    int maxLen = 0;
    while (right < n)
    {
        // if sum > k, reduce the subarray from left
        // until sum becomes less or equal to k:
        while (left <= right && sum > k)
        {
            sum -= a[left];
            left++;
        }

        // if sum = k, update the maxLen i.e. answer:
        if (sum == k)
        {
            maxLen = max(maxLen, right - left + 1);
        }

        // Move forward thw right pointer:
        right++;
        if (right < n)
            sum += a[right];
    }

    return maxLen;
}
//! T.C-> O(2*N)
//! S.C-> O(1)


Sliding window:
using namespace std;
int longestSubarrayWithSumK(vector<int> A, long long k) {
   int n = A.size();
    int left = 0, right = 0;
    long long sum = 0;
    int ans = 0;
    while(right<n){
        sum += A[right];

        while(sum>k){
            sum -= A[left];
            left++;
        }

        if (sum == k) {
          ans = max(ans, right - left + 1);
        }
        right++;
    }
    return ans;
} 

//! T.C-> O(2N)
//! S.C-> O(1)
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 14.Longest Subarray with sum K | [Postives and Negatives]
int getLongestSubarray(vector<int> &a, int k)
{
    int n = a.size(); // size of the array.

    map<int, int> preSumMap;
    int sum = 0;
    int maxLen = 0;
    for (int i = 0; i < n; i++)
    {
        // calculate the prefix sum till index i:
        sum += a[i];

        // calculate the sum of remaining part i.e. x-k:
        int rem = sum - k;

        // Calculate the length and update maxLen:
        if (preSumMap.find(rem) != preSumMap.end())
        {
            int len = i - preSumMap[rem];
            maxLen = max(maxLen, len);
        }
	
        // Finally, update the map checking the conditions:
        if (preSumMap.find(sum) == preSumMap.end())
        {
            preSumMap[sum] = i;
        }

	// if the sum = k, update the maxLen:
        if (sum == k)
        {
            maxLen = max(maxLen, i + 1);
        }
    }
    return maxLen;
}
//! T.C-> O(N) or O(N*logN) depending on which map data structure we are using, where N = size of the array.
//! S.C-> O(N)