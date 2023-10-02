// 1.Pascal's triangle

//  ---------------------------------------------------------------------------------------------------------------------------------------------------------------------
//  2.Majority Elements(>N/3 times) | Find the elements that appears more than N/3 times in the array
vector<int> majorityElement(vector<int> &nums)
{
    int n = nums.size();
    int ele1 = INT_MIN, ele2 = INT_MIN;
    int cnt1 = 0, cnt2 = 0;
    for (int i = 0; i < n; i++)
    {
        if (cnt1 == 0 && nums[i] != ele2)
        {
            cnt1 = 1;
            ele1 = nums[i];
        }
        else if (cnt2 == 0 && nums[i] != ele1)
        {
            cnt2 = 1;
            ele2 = nums[i];
        }
        else if (nums[i] == ele1)
        {
            cnt1++;
        }
        else if (nums[i] == ele2)
        {
            cnt2++;
        }
        else
        {
            cnt1--;
            cnt2--;
        }
    }
    cnt1 = 0, cnt2 = 0;
    for (int i = 0; i < n; i++)
    {
        if (nums[i] == ele1)
            cnt1++;
        if (nums[i] == ele2)
            cnt2++;
    }
    vector<int> ans;
    if (cnt1 >= n / 3 + 1)
        ans.push_back(ele1);
    if (cnt2 >= n / 3 + 1)
        ans.push_back(ele2);
    return ans;
}
// T.C-> O(2*N)
// S.C-> O(1)
//  ---------------------------------------------------------------------------------------------------------------------------------------------------------------------
//  3.3-Sum Problem
// Used two pointers like 2 sum and fixed 1 element (index i)
vector<vector<int>> threeSum(vector<int> &nums)
{
    int n = nums.size();
    sort(nums.begin(), nums.end());
    vector<vector<int>> ans;
    for (int i = 0; i < n; i++)
    {
        if (i > 0 && nums[i] == nums[i - 1])
            continue;
        int j = i + 1;
        int k = n - 1;
        while (j < k)
        {
            int sum = nums[i] + nums[j] + nums[k];
            if (sum < 0)
                j++;
            else if (sum > 0)
                k--;
            else
            {
                vector<int> t = {nums[i], nums[j], nums[k]};
                ans.push_back(t);
                j++;
                k--;
                while (j < k && nums[j] == nums[j - 1])
                    j++;
                while (j < k && nums[k] == nums[k + 1])
                    k--;
            }
        }
    }
    return ans;
}
// T.C-> O(N*N)
// S.C-> O(3*k)  // k is the no.of triplets.
//  ---------------------------------------------------------------------------------------------------------------------------------------------------------------------
//  4.4 Sum | Find Quads that add up to a target value
//    used hashing technique like 2 sum!!
vector<vector<int>> fourSum(vector<int> &nums, int target)
{
    set<vector<int>> st;
    int n = nums.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            set<long long> s;
            for (int k = j + 1; k < n; k++)
            {
                long long sum = nums[i] + nums[j];
                sum += nums[k];
                if (s.find(target - sum) != s.end())
                {
                    vector<int> t = {nums[i], nums[j], nums[k], int(target - sum)};
                    sort(t.begin(), t.end());
                    st.insert(t);
                }
                s.insert(nums[k]);
            }
        }
    }
    vector<vector<int>> ans(st.begin(), st.end());
    return ans;
}

// T.C-> O(N^3*longN)
// S.C-> O(2 * no. of the quadruplets)+O(N)

// Used two pointers like 2 sum and fixed two elements(i and j)
vector<vector<int>> fourSum(vector<int> &nums, int k)
{
    set<vector<int>> st;
    int n = nums.size();
    sort(nums.begin(), nums.end());
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (j > i + 1 && nums[j] == nums[j - 1])
                continue;
            int low = j + 1;
            int high = n - 1;
            while (low < high)
            {
                long long sum = nums[i] + nums[j];
                sum += nums[low];
                sum += nums[high];
                if (sum < k)
                    low++;
                else if (sum > k)
                    high--;
                else
                {
                    vector<int> t = {nums[i], nums[j], nums[low], nums[high]};
                    sort(t.begin(), t.end());
                    st.insert(t);
                    low++;
                    high--;
                    while (low < high && nums[low] == nums[low - 1])
                        low++;
                    while (low < high && nums[high] == nums[high + 1])
                        high--;
                }
            }
        }
    }
    vector<vector<int>> ans(st.begin(), st.end());
    return ans;
}
// T.C-> O(N^3)
// S.C-> O(no. of quadruplets), This space is only used to store the answer. We are not using any extra space to solve this problem.
//  So, from that perspective, space complexity can be written as O(1).
//  ---------------------------------------------------------------------------------------------------------------------------------------------------------------------
//  5.Length of the longest subarray with zero Sum
int maxLen(vector<int> &A, int n)
{
    // Your code here
    int ans = 0;
    int sum = 0;
    unordered_map<int, int> m;
    for (int i = 0; i < n; i++)
    {
        sum += A[i];
        if (sum == 0)
        {
            ans = max(ans, i + 1);
        }
        if (m.find(sum) != m.end())
        {
            ans = max(ans, i - m[sum]);
        }
        else
        {
            m[sum] = i;
        }
    }
    return ans;
}
// T.C-> O(N) or O(N*logN) depending on which map data structure we are using, where N = size of the array.
// S.C-> O(N)
//  ---------------------------------------------------------------------------------------------------------------------------------------------------------------------
//  6.Count number of subarrays with given xor K
int subarraysWithXorK(vector<int> a, int k)
{
    int n = a.size(); // size of the given array.
    int xr = 0;
    map<int, int> mpp; // declaring the map.
    mpp[xr]++;         // setting the value of 0.
    int cnt = 0;

    for (int i = 0; i < n; i++)
    {
        // prefix XOR till index i:
        xr = xr ^ a[i];

        // By formula: x = xr^k:
        int x = xr ^ k;

        // add the occurrence of xr^k
        // to the count:
        cnt += mpp[x];

        // Insert the prefix xor till index i
        // into the map:
        mpp[xr]++;
    }
    return cnt;
}
// OR
int solve(vector<int> &A, int B)
{
    unordered_map<int, int> m;
    int n1 = A.size();
    m[0]++;
    int ans = 0;
    int x = 0;
    for (int i = 0; i < n1; i++)
    {
        x ^= A[i];
        if (m.find(x ^ B) != m.end())
        {
            ans += m[x ^ B];
        }
        m[x]++;
    }
    return ans;
}
// T.C-> O(N) or O(N*logN) depending on which map data structure we are using, where N = size of the array.
// S.C-> O(N)

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 7.Merge Overlapping Subintervals
vector<vector<int>> merge(vector<vector<int>> &intervals)
{
    int n = intervals.size();
    vector<vector<int>> ans;
    // sort the given intervals:
    sort(intervals.begin(), intervals.end());
    for (int i = 0; i < n; i++)
    {
        // if the current interval does not
        // lie in the last interval:
        if (ans.empty() || intervals[i][0] > ans[ans.size() - 1][1])
        {
            ans.push_back(intervals[i]);
        }
        // if the current interval
        // lies in the last interval:
        else
        {
            ans[ans.size() - 1][1] = max(ans[ans.size() - 1][1], intervals[i][1]);
        }
    }
    return ans;
}
// T.C-> O(N*logN) + O(N)
// S.C-> O(N)
//  ---------------------------------------------------------------------------------------------------------------------------------------------------------------------
//  8.Merge two Sorted Arrays Without Extra Space
vector<int> leaders(int a[], int n)
{
    // Code here
    int maxi = INT_MIN;
    vector<int> ans;
    for (int i = n - 1; i >= 0; i--)
    {
        if (maxi <= a[i])
        {
            ans.push_back(a[i]);
        }
        maxi = max(maxi, a[i]);
    }
    reverse(ans.begin(), ans.end());
    return ans;
}
// T.C-> O(N)
// S.C -> O(N)
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 9.Find the repeating and missing numbers
vector<int> findTwoElement(vector<int> arr, int nn) {
        // code here
        long long n = arr.size();
        long long s = 0;
        long long sn =(n*(n+1))/2;
        long long s2 = 0;
        long long s2n = (n*(n+1)*(2*n+1))/6;
        for(int i=0;i<n;i++){   
            s += (long long)arr[i];
            s2 += (long long)arr[i]*(long long)arr[i];
        }
        
        // x is repeating and y is missing
        
        // var1 -> x - y
        long long var1 = s - sn;
        
        // var2 -> x^2 - y^2
        long long var2 = s2-s2n;
        
        // var3 -> x + y
        long long var3 = var2/var1;
        
        // 2*x = var1+var3
        long long x = (var1+var3)/2;

        // var1 = x - y
        long long y = x - var1;
        
        return {(int)x,(int)y};
    }
// T.C-> O(N)
// S.C -> O(1)
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 11.Set Matrix Zero
vector<vector<int>> zeroMatrix(vector<vector<int>> &matrix, int n, int m)
{

    int row[n] = {0}; // row array
    int col[m] = {0}; // col array

    // Traverse the matrix:
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (matrix[i][j] == 0)
            {
                // mark ith index of row wih 1:
                row[i] = 1;

                // mark jth index of col wih 1:
                col[j] = 1;
            }
        }
    }

    // Finally, mark all (i, j) as 0
    // if row[i] or col[j] is marked with 1.
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (row[i] || col[j])
            {
                matrix[i][j] = 0;
            }
        }
    }

    return matrix;
}
// T.C-> O(2*(N*M))
// S.C-> O(N+M)

vector<vector<int>> zeroMatrix(vector<vector<int>> &matrix, int n, int m)
{

    // int row[n] = {0}; --> matrix[..][0]
    // int col[m] = {0}; --> matrix[0][..]

    int col0 = 1;
    // step 1: Traverse the matrix and
    // mark 1st row & col accordingly:
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (matrix[i][j] == 0)
            {
                // mark i-th row:
                matrix[i][0] = 0;

                // mark j-th column:
                if (j != 0)
                    matrix[0][j] = 0;
                else
                    col0 = 0;
            }
        }
    }

    // Step 2: Mark with 0 from (1,1) to (n-1, m-1):
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < m; j++)
        {
            if (matrix[i][j] != 0)
            {
                // check for col & row:
                if (matrix[i][0] == 0 || matrix[0][j] == 0)
                {
                    matrix[i][j] = 0;
                }
            }
        }
    }

    // step 3: Finally mark the 1st col & then 1st row:
    if (matrix[0][0] == 0)
    {
        for (int j = 0; j < m; j++)
        {
            matrix[0][j] = 0;
        }
    }
    if (col0 == 0)
    {
        for (int i = 0; i < n; i++)
        {
            matrix[i][0] = 0;
        }
    }

    return matrix;
}
// T.C-> O(2*(N*M))
// S.C-> O(1)
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------
12) Count Inversions
int merge(vector<int> &arr, int low, int mid, int high) {
    int left = low;
    int right = mid + 1;

    vector<int> temp; // Temporary array to store sorted elements

    int cnt = 0; // Counter to keep track of inversions

    // Merge the two sorted subarrays while counting inversions
    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) {
            temp.push_back(arr[left++]);
        } else {
            // If element from right subarray is smaller, count inversions
            cnt += mid - left + 1;
            temp.push_back(arr[right++]);
        }
    }

    // Add remaining elements from the left subarray
    while (left <= mid) {
        temp.push_back(arr[left++]);
    }

    // Add remaining elements from the right subarray
    while (right <= high) {
        temp.push_back(arr[right++]);
    }

    // Copy the sorted elements from the temporary array back to the original array
    for (int i = low; i <= high; i++) {
        arr[i] = temp[i - low];
    }

    return cnt; // Return the count of inversions
}

int mergeSort(vector<int> &arr, int low, int high) {
    int cnt = 0; // Counter to keep track of inversions

    // Base case: If the subarray has only one element or is empty, no sorting is needed
    if (low == high) {
        return cnt;
    }

    int mid = low - (low - high) / 2; // Calculate the middle index of the subarray

    // Recursively divide the array into two halves, sort them, and count inversions
    cnt += mergeSort(arr, low, mid);
    cnt += mergeSort(arr, mid + 1, high);
    cnt += merge(arr, low, mid, high);

    return cnt; // Return the count of inversions
}

int numberOfInversions(vector<int>& a, int n) {
    return mergeSort(a, 0, n - 1);
}

Time Complexity: O(N*logN), where N = size of the given array.
Reason: We are not changing the merge sort algorithm except by adding a variable to it. So, the time complexity is as same as the merge sort.

Space Complexity: O(N), as in the merge sort We use a temporary array to store elements in sorted order.
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
13) Reverse Pairs

class Solution {
public:
    void merge(vector<int>& arr, int low, int mid, int high) {
        vector<int> temp; // Temporary array to store sorted elements
        int left = low; // Pointer for the left subarray
        int right = mid + 1; // Pointer for the right subarray

        // Merge the two subarrays by comparing elements
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
            arr[i] = temp[i - low];
        }
    }

    int countPairs(vector<int>& arr, int low, int mid, int high) {
        int cnt = 0;
        int right = mid + 1;

        // Count the number of reverse pairs
        for (int i = low; i <= mid; i++) {
            // Iterate over the right subarray and find elements that form reverse pairs
            while (right <= high && arr[i] > 2LL * arr[right]) {
                right++;
            }
            // Increment the count by the number of elements in the right subarray that form reverse
            // pairs
            cnt += (right - (mid + 1));
        }

        return cnt;
    }


    int mergeSort(vector<int>& arr, int low, int high) {
        int cnt = 0;
        
        // Base case: If the subarray has only one element or is empty, no sorting is needed
        if (low >= high) {
            return cnt;
        }

        int mid = low - (low - high) / 2; // Calculate the middle index of the subarray

        // Recursively divide the array into two halves and sort them
        cnt += mergeSort(arr, low, mid); // Sort the left half
        cnt += mergeSort(arr, mid + 1, high); // Sort the right half
        cnt += countPairs(arr, low, mid, high); // Count reverse pairs
        merge(arr, low, mid, high); // Merge the two sorted halves

        return cnt;
    }

    int reversePairs(vector<int>& arr) {
        return mergeSort(arr, 0, arr.size() - 1);
    }
};

Time Complexity: O(2N*logN), where N = size of the given array.
Reason: Inside the mergeSort() we call merge() and countPairs() except mergeSort() itself. 
Now, inside the function countPairs(), though we are running a nested loop, we are actually 
iterating the left half once and the right half once in total. That is why, the time complexity is O(N). 
And the merge() function also takes O(N). The mergeSort() takes O(logN) time complexity. 
Therefore, the overall time complexity will be O(logN * (N+N)) = O(2N*logN).

Space Complexity: O(N), as in the merge sort We use a temporary array to store elements in sorted order.
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
14) Maximum product subarray
*The product is present on either start or end of the array i.e prefix or suffix !!int maxProduct(vector<int> & nums)
{
    int n = nums.size();
    int ans = INT_MIN;
    int prefProd = 1;
    int suffProd = 1;
    for (int i = 0; i < n; i++)
    {
        // If any of the sum got zero start with the new subarray
        if (prefProd == 0) prefProd = 1;
        if (suffProd == 0) suffProd = 1;

        // Multiply for respective product
        prefProd *= nums[i];
        suffProd *= nums[n - i - 1];

        // Maximize the product everytime
        ans = max(ans, max(suffProd, prefProd));
    }
    return ans;
}
// T.C-> O((N))
// S.C-> O(1)
