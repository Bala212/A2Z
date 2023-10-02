1. Two Sum : Check if a pair with given sum exists in Array
string twoSum(int n, vector<int> &arr, int target)
{
    unordered_map<int, int> mpp;
    for (int i = 0; i < n; i++)
    {
        int num = arr[i];
        int moreNeeded = target - num;
        if (mpp.find(moreNeeded) != mpp.end())
        {
            return "YES";
        }
        mpp[num] = i;
    }
    return "NO";
}
// T.C-> O(N)
// S.C-> O(N)
string twoSum(int n, vector<int> &arr, int target)
{
    sort(arr.begin(), arr.end());
    int left = 0, right = n - 1;
    while (left < right)
    {
        int sum = arr[left] + arr[right];
        if (sum == target)
        {
            return "YES";
        }
        else if (sum < target)
            left++;
        else
            right--;
    }
    return "NO";
}
// T.C-> O(N)
// S.C-> O(1)
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
2.Sort an array of 0s, 1s and 2s
// In dutch flag algorithm we don't increment mid when we encounter 2 at mid and swap 
// it with high, because we have to again process the element at high which now is at mid
// and talking about low after swapping we move both low and mid pointers because 
// element at low will always be 1 as 2 will get swap before only! But we are not sure 
// about that what will be element at high index! So that is why we don't increment mid 
// while swapping with high!!

//  This problem is a variation of the popular Dutch National flag algorithm.
void sortArray(vector<int> &arr, int n)
{

    int low = 0, mid = 0, high = n - 1; // 3 pointers

    while (mid <= high)
    {
        if (arr[mid] == 0)
        {
            swap(arr[low], arr[mid]);
            low++;
            mid++;
        }
        else if (arr[mid] == 1)
        {
            mid++;
        }
        else
        {
            swap(arr[mid], arr[high]);
            high--;
        }
    }
}
// T.C-> O(N)
// S.C-> O(1)
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
3.Find the Majority Element that occurs more than N/2 times
// Cancelling the elements and left off with the 
// majority one and if question does not guarantee if there exists majority element 
// then again check whether the element( which we get after cancellation) occurs>n/2 
// times or not !

//  Moore’s Voting Algorithm:
int majorityElement(vector<int> v)
{
    // size of the given array:
    int n = v.size();
    int cnt = 0; // count
    int el;      // Element

    // applying the algorithm:
    for (int i = 0; i < n; i++)
    {
        if (cnt == 0)
        {
            cnt = 1;
            el = v[i];
        }
        else if (el == v[i])
            cnt++;
        else
            cnt--;
    }

    // checking if the stored element
    //  is the majority element:
    int cnt1 = 0;
    for (int i = 0; i < n; i++)
    {
        if (v[i] == el)
            cnt1++;
    }

    if (cnt1 > (n / 2))
        return el;
    return -1;
}
// T.C-> O(2*N)
// S.C-> O(1)
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
4.Kadane’s Algorithm : Maximum Subarray Sum in an Array

long long maxSubarraySum(int arr[], int n)
{
    long long maxi = LONG_MIN; // maximum sum
    long long sum = 0;

    for (int i = 0; i < n; i++)
    {

        sum += arr[i];

        if (sum > maxi)
        {
            maxi = sum;
        }

        // If sum < 0: discard the sum calculated
        if (sum < 0)
        {
            sum = 0;
        }
    }
}
// T.C-> O(N)
// S.C-> O(1)
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
5.Print Subarray with Given Sum

long long maxSubarraySum(int arr[], int n)
{
    long long maxi = LONG_MIN; // maximum sum
    long long sum = 0;

    int start = 0;
    int ansStart = -1, ansEnd = -1;
    for (int i = 0; i < n; i++)
    {

        if (sum == 0)
            start = i; // starting index

        sum += arr[i];

        if (sum > maxi)
        {
            maxi = sum;

            ansStart = start;
            ansEnd = i;
        }

        // If sum < 0: discard the sum calculated
        if (sum < 0)
        {
            sum = 0;
        }
    }
}
// printing the subarray:
cout << "The subarray is: [";
for (int i = ansStart; i <= ansEnd; i++)
{
    cout << arr[i] << " ";
}
// T.C-> O(N)
// S.C-> O(1)
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
6.Stock Buy And Sell

int maxProfit(vector<int> &arr)
{
    int maxPro = 0;
    int n = arr.size();
    int minPrice = INT_MAX;

    for (int i = 0; i < arr.size(); i++)
    {
        minPrice = min(minPrice, arr[i]);
        maxPro = max(maxPro, arr[i] - minPrice);
    }

    return maxPro;
}
// T.C-> O(N)
// S.C-> O(1)
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
7.Rearrange Array Elements by Sign

vector<int> RearrangebySign(vector<int> A)
{

    int n = A.size();

    // Define array for storing the ans separately.
    vector<int> ans(n, 0);

    // positive elements start from 0 and negative from 1.
    int posIndex = 0, negIndex = 1;
    for (int i = 0; i < n; i++)
    {

        // Fill negative elements in odd indices and inc by 2.
        if (A[i] < 0)
        {
            ans[negIndex] = A[i];
            negIndex += 2;
        }

        // Fill positive elements in even indices and inc by 2.
        else
        {
            ans[posIndex] = A[i];
            posIndex += 2;
        }
    }
    return ans;
}
// T.C-> O(N)
// S.C-> O(N)

// When no. of positives and negatives are different
vector<int> RearrangebySign(vector<int> A, int n)
{

    // Define 2 vectors, one for storing positive
    // and other for negative elements of the array.
    vector<int> pos;
    vector<int> neg;

    // Segregate the array into positives and negatives.
    for (int i = 0; i < n; i++)
    {

        if (A[i] > 0)
            pos.push_back(A[i]);
        else
            neg.push_back(A[i]);
    }

    // If positives are lesser than the negatives.
    if (pos.size() < neg.size())
    {

        // First, fill array alternatively till the point
        // where positives and negatives ar equal in number.
        for (int i = 0; i < pos.size(); i++)
        {

            A[2 * i] = pos[i];
            A[2 * i + 1] = neg[i];
        }

        // Fill the remaining negatives at the end of the array.
        int index = pos.size() * 2;
        for (int i = pos.size(); i < neg.size(); i++)
        {

            A[index] = neg[i];
            index++;
        }
    }

    // If negatives are lesser than the positives.
    else
    {

        // First, fill array alternatively till the point
        // where positives and negatives ar equal in number.
        for (int i = 0; i < neg.size(); i++)
        {

            A[2 * i] = pos[i];
            A[2 * i + 1] = neg[i];
        }

        // Fill the remaining positives at the end of the array.
        int index = neg.size() * 2;
        for (int i = neg.size(); i < pos.size(); i++)
        {

            A[index] = pos[i];
            index++;
        }
    }
    return A;
}
// T.C-> O(2*N)
// S.C-> O(N)

---------------------------------------------------------------------------------------------------------------------------------------------------------------------
8.next_permutation : find next lexicographically greater permutation

// Magun check karnar kuth paryant increasing ahe mhnje kay ki te apan change nahi karu
// shakat karan change kelyavr to next permutation nahi rahnar na, tyamule apan asa index 
// baghnar Jo sorted part nantr ahe mhnje aaplaya tyala change krta yeil, ani ata tyala kashyane 
// change karaycha tr right part madhe tyachya pekshya just greater element ne replace/swap karaych 
// mhnje next permutation hoel ani tya index cha pudcha part/array reverse karaycha karan aaplyala 
// just greater permutation pahije ae na tr te tya index cha pudcha part decreasing order madhe asel
// tr to just greater permutation hoel!!

// Jar aaplyala asa konta index milala ch nahi tr array la ahe tasa reverse karun return kar

vector<int> nextGreaterPermutation(vector<int> &A)
{
    int n = A.size(); // size of the array.

    // Step 1: Find the break point:
    int ind = -1; // break point
    for (int i = n - 2; i >= 0; i--)
    {
        if (A[i] < A[i + 1])
        {
            // index i is the break point
            ind = i;
            break;
        }
    }

    // If break point does not exist:
    if (ind == -1)
    {
        // reverse the whole array:
        reverse(A.begin(), A.end());
        return A;
    }

    // Step 2: Find the next greater element
    //         and swap it with arr[ind]:

    for (int i = n - 1; i > ind; i--)
    {
        if (A[i] > A[ind])
        {
            swap(A[i], A[ind]);
            break;
        }
    }

    // Step 3: reverse the right half:
    reverse(A.begin() + ind + 1, A.end());

    return A;
}
// T.C-> O(3*N)
// S.C-> O(1)
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
9.Leaders in an Array

// Keep track of max element from end of array and traverse array from end
// and check whether the current element is greater than the max till now( of right part). 
// Because if current element is greater than max till now, then it is the leader!

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
// 10.Longest Consecutive Sequence in an Array
int longestConsecutive(vector<int> nums)
{
    if (nums.size() == 0)
    {
        return 0;
    }

    sort(nums.begin(), nums.end());

    int ans = 1;
    int prev = nums[0];
    int cur = 1;

    for (int i = 1; i < nums.size(); i++)
    {
        if (nums[i] == prev + 1)
        {
            cur++;
        }
        else if (nums[i] != prev)
        {
            cur = 1;
        }
        prev = nums[i];
        ans = max(ans, cur);
    }
    return ans;
}
// T.C-> O(N*logN)
// S.C -> O(1)

int longestConsecutive(vector<int> &nums)
{
    int n = nums.size();
    unordered_set<int> s;
    for (int i = 0; i < n; i++)
    {
        s.insert(nums[i]);
    }
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        int x = nums[i];
        if (s.find(x - 1) == s.end())
        {
            int cnt = 1;
            while (s.find(x + 1) != s.end())
            {
                cnt++;
                x++;
            }
            ans = max(ans, cnt);
        }
    }
    return ans;
}
// T.C-> O(N)
// S.C-> O(1)
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
11.Set Matrix Zero
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
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
12.Rotate Image by 90 degree

// Brute-> Approach: Take another dummy matrix of n*n, and then take the first row of the matrix and put it in 
// the last column of the dummy matrix take the second row of the matrix, and put it in the second last column 
// of the matrix and so.
vector<vector<int>> rotate(vector<vector<int>> &matrix)
{
    int n = matrix.size();
    vector<vector<int>> rotated(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            rotated[j][n - i - 1] = matrix[i][j];
        }
    }
    return rotated;
}
// T.C-> O((N*N))
// S.C-> O(N*N)

// Optimal Approach:
// Step 1: Transpose the matrix. (transposing means changing columns to rows and rows to columns)
// Step 2: Reverse each row of the matrix.
void rotate(vector<vector<int>> &matrix)
{
    int n = matrix.size();
    // transposing the matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            swap(matrix[i][j], matrix[j][i]);
        }
    }
    // reversing each row of the matrix
    for (int i = 0; i < n; i++)
    {
        reverse(matrix[i].begin(), matrix[i].end());
    }
}
// T.C-> O(2*N*N)
// S.C-> O(1)
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
13.Spiral Traversal of Matrix

vector<int> printSpiral(vector<vector<int>> mat)
{
    // Define ans array to store the result.
    vector<int> ans;

    int n = mat.size();    // no. of nows
    int m = mat[0].size(); // no. of columns

    // Initialize the pointers reqd for traversal.
    int top = 0, left = 0, bottom = n - 1, right = m - 1;

    // Loop until all elements are not traversed.
    while (top <= bottom && left <= right)
    {

        // For moving left to right
        for (int i = left; i <= right; i++)
            ans.push_back(mat[top][i]);

        top++;

        // For moving top to bottom.
        for (int i = top; i <= bottom; i++)
            ans.push_back(mat[i][right]);

        right--;

        // For moving right to left.
        if (top <= bottom)
        {
            for (int i = right; i >= left; i--)
                ans.push_back(mat[bottom][i]);

            bottom--;
        }

        // For moving bottom to top.
        if (left <= right)
        {
            for (int i = bottom; i >= top; i--)
                ans.push_back(mat[i][left]);

            left++;
        }
    }
    return ans;
}
// T.C-> O(N*M)
// S.C-> O(N)
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
14.Count Subarray sum Equals K

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int,int> m;
        m[0]++;
        int n = nums.size();
        int sum = 0;
        int cnt = 0;
        for(int i=0;i<n;i++){
            sum += nums[i];
            if(m.find(sum-k)!=m.end()){
                cnt += m[sum-k];
            }
            m[sum]++;
        }
        return cnt;
    }
};

int findAllSubarraysWithGivenSum(vector<int> &arr, int k)
{
    int n = arr.size(); // size of the given array.
    map mpp;
    int preSum = 0, cnt = 0;

    mpp[0] = 1; // Setting 0 in the map.
    for (int i = 0; i < n; i++)
    {
        // add current element to prefix Sum:
        preSum += arr[i];

        // Calculate x-k:
        int remove = preSum - k;

        // Add the number of subarrays to be removed:
        cnt += mpp[remove];

        // Update the count of prefix sum
        // in the map.
        mpp[preSum] += 1;
    }
    return cnt;
}
// T.C-> O(N) or O(N*logN) depending on which map data structure we are using, where N = size of the array.
// S.C-> O(N)