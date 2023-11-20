// 1.Search an element in sorted array
int search(vector<int> &nums, int target)
{
    int n = nums.size();
    int l = 0, r = n - 1;
    int ans = -1;
    
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (target < nums[mid])
        {
            r = mid - 1;
        }
        else if (target > nums[mid])
        {
            l = mid + 1;
        }
        else
        {
            ans = mid;
            break;
        }
    }
    return ans;
}
// T.C-> O(logN)
// S.C-> O(1)
// --------------------------------------------------------------------------------------------------
// 2.Implement Lower Bound
int lowerBound(vector<long long> v, long long n, long long x)
{
    // Your code here
    int low = 0;
    int high = n - 1;
    // If there is no lower_bound present
    int ans = n;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (v[mid] >= x)
        {
            ans = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return ans;
}
// T.C-> O(logN)
// S.C-> O(1)
// --------------------------------------------------------------------------------------------------
// 3.Implement Upper Bound
// just ">=" --> ">"
int upperBound(vector<long long> v, long long n, long long x)
{
    // Your code here
    int low = 0;
    int high = n - 1;
    int ans = n;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (v[mid] > x)
        {
            ans = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return ans;
}
// T.C-> O(logN)
// S.C-> O(1)
// --------------------------------------------------------------------------------------------------
// 4. Search Insert Position --> It's lower bound only
// --------------------------------------------------------------------------------------------------
// 5.Floor/Ceil in Sorted Array
int floor(int x, int arr[], int n)
{
    int ans = -1;
    int low = 0;
    int high = n - 1;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (arr[mid] <= x)
        {
            ans = arr[mid];
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return ans;
}
int ceil(int x, int arr[], int n)
{
    int ans = -1;
    int low = 0;
    int high = n - 1;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (arr[mid] >= x)
        {
            ans = arr[mid];
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return ans;
}
pair<int, int> getFloorAndCeil(int arr[], int n, int x)
{
    // Write your code here.
    sort(arr, arr + n);
    return {floor(x, arr, n), ceil(x, arr, n)};
}

// T.C-> O(2*logN)
// S.C-> O(1)

// --------------------------------------------------------------------------------------------------
// 6.First and Last occurrence in a sorted array
//  O(n)-->
vector<int> searchRange(vector<int> &nums, int target)
{
    int f = -1, l = -1;
    int n = nums.size();
    for (int i = 0; i < n; i++)
    {
        if (nums[i] == target)
        {
            if (f == -1)
                f = i;
            l = i;
        }
    }
    return {f, l};
}
// Using lower bound and upper bound
vector<int> searchRange(vector<int> &nums, int target)
{
    int lb = lower_bound(nums.begin(), nums.end(), target) - nums.begin();
    int ub = upper_bound(nums.begin(), nums.end(), target) - nums.begin();
    if (lb == nums.size() || nums[lb] != target)
    {
        return {-1, -1};
    }
    return {lb, ub - 1};
}
// Using actual binary search
int first(vector<int> &nums, int k)
{
    int low = 0;
    int high = nums.size() - 1;
    int ans = -1;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (nums[mid] == k)
        {
            ans = mid;
            high = mid - 1;
        }
        else if (nums[mid] < k)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return ans;
}
int last(vector<int> &nums, int k)
{
    int low = 0;
    int high = nums.size() - 1;
    int ans = -1;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (nums[mid] == k)
        {
            ans = mid;
            low = mid + 1;
        }
        else if (nums[mid] < k)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return ans;
}
vector<int> searchRange(vector<int> &nums, int target)
{
    return {first(nums, target), last(nums, target)};
}
// T.C-> O(2*logN)
// S.C-> O(1)
// --------------------------------------------------------------------------------------------------
// 7.Count Occurrences in Sorted Array
// Using lower bound and upper bound
int count(int arr[], int n, int x)
{
    // code here
    int lb = lowerBound(arr, n, x);
    int ub = upperBound(arr, n, x);
    if (lb == n)
        return 0;
    return ub - lb;
}
// OR
// Using first and last occurrence
int count(int arr[], int n, int x)
{
    // code here
    int f = first(arr, n, x);
    int l = last(arr, n, x);
    if (l == -1)
        return 0;
    return l - f + 1;
}
// T.C-> O(2*logN)
// S.C-> O(1)
// --------------------------------------------------------------------------------------------------
// 8.Search in Rotated Sorted Array I (Without duplicates)

// Sorted part konta ae shodha ani jar target tithe asel tr tya part la BS lava
// nahi tr dusrya part la move kara!!
int search(vector<int> &nums, int target)
{
    int n = nums.size();
    int low = 0;
    int high = n - 1;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (nums[mid] == target)
            return mid;
        // If left part is sorted, check whether target lies in that part or not and move accordingly
        if (nums[low] <= nums[mid])
        {
            if (target >= nums[low] && target <= nums[mid])
                high = mid - 1;
            else
                low = mid + 1;
        }
        // Right part is sorted, check whether target lies in that part or not and move accordingly
        else
        {
            if (target >= nums[mid] && target <= nums[high])
                low = mid + 1;
            else
                high = mid - 1;
        }
    }
    return -1;
}
// T.C-> O(logN)
// S.C-> O(1)

// --------------------------------------------------------------------------------------------------
// 9.Search in Rotated Sorted Array II (With duplicates)

// A minute change, but necessary one !
bool search(vector<int> &nums, int target)
{
    int n = nums.size();
    int low = 0;
    int high = n - 1;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (nums[mid] == target)
            return true;
        // This is the condition added!
        // we are direct eliminating low and high, coz we are sure that they are not the element we are
        // looking for as it will checked above only.
        if (nums[low] == nums[mid] && nums[mid] == nums[high])
        {
            low++;
            high--; // 3 0 3 3 3 
            continue;
        }
        // If left part is sorted, check whether target lies in that part or not and move accordingly
        if (nums[low] <= nums[mid])
        {
            if (target >= nums[low] && target <= nums[mid])
                high = mid - 1;
            else
                low = mid + 1;
        }
        // Right part is sorted, check whether target lies in that part or not and move accordingly
        else
        {
            if (target >= nums[mid] && target <= nums[high])
                low = mid + 1;
            else
                high = mid - 1;
        }
    }
    return false;
}
// T.C-> O(logN) and in worst case it would be O(N/2) for the new line added, when all the elements are same
// S.C-> O(1)

// --------------------------------------------------------------------------------------------------
// 10.Find Minimum in Rotated Sorted Array I (without duplicates)
int findMin(vector<int> &nums)
{
    int low = 0;
    int high = nums.size() - 1;
    int ans = INT_MAX;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        // Left part is sorted, store minimum of that part and move to right
        if (nums[low] <= nums[mid])
        {
            ans = min(ans, nums[low]);
            low = mid + 1;
        }
        // Right part is sorted, store minimum of that part and move to left
        else
        {
            ans = min(ans, nums[mid]);
            high = mid - 1;
        }
    }
    return ans;
}
// OR
int findMin(vector<int> &nums)
{
    int low = 0;
    int n = nums.size();
    int high = n - 1;

    while (low < high)
    {
        int mid = low + (high - low) / 2;
        // If right part is sorted, mid index can be the answer as it is the minimun
        if (nums[mid] < nums[high])
        {
            high = mid;
        }
        // Left part is sorted, answer cannot be in left part as array is sorted and rotated
        else
        {
            low = mid + 1;
        }
    }
    return nums[high];
}
// T.C-> O(logN)
// S.C-> O(1)
// --------------------------------------------------------------------------------------------------
// 11.Find Minimum in Rotated Sorted Array II (with duplicates)
int findMin(vector<int> &nums)
{
    int low = 0;
    int high = nums.size() - 1;
    int ans = INT_MAX;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        // This is the condition added!
        // we are direct eliminating low and high by considering them as a answer!
        // At this case we are not able to identify the sorted part!!
        if (nums[low] == nums[mid] && nums[mid] == nums[high])
        {
            ans = min(ans, nums[low]);
            low++;
            high--;
            continue;
        }
        // Left part is sorted, store minimum of that part and move to right
        if (nums[low] <= nums[mid])
        {
            ans = min(ans, nums[low]);
            low = mid + 1;
        }
        // Right part is sorted, store minimum of that part and move to left
        else
        {
            ans = min(ans, nums[mid]);
            high = mid - 1;
        }
    }
    return ans;
}
// OR
int findMin(vector<int> &nums)
{
    int n = nums.size();
    int low = 0;
    int high = n - 1;
    while (low < high)
    {
        int mid = low + (high - low) / 2;
        if (nums[mid] < nums[high])
        {
            high = mid;
        }
        else if (nums[mid] > nums[high])
        {
            low = mid + 1;
        }
        else
            high--;
    }
    return nums[high];
}
// T.C-> O(logN) and in worst case it would be O(N/2) for the new line added, when all the elements are same
// S.C-> O(1)

// --------------------------------------------------------------------------------------------------
// 12.	Find out how many times has an array has been rotated

// Index of minimum element is the answer
int findKRotation(int nums[], int n)
{
    int low = 0;
    int high = n - 1;
    int minEle = INT_MAX;
    int ind = -1;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        // Left part is sorted, store minimum of that part and move to right
        if (nums[low] <= nums[mid])
        {
            if (nums[low] < minEle)
            {
                minEle = nums[low];
                ind = low;
            }
            low = mid + 1;
        }
        // Right part is sorted, store minimum of that part and move to left
        else
        {
            if (nums[mid] < minEle)
            {
                minEle = nums[mid];
                ind = mid;
            }
            high = mid - 1;
        }
    }
    return ind;
}
// OR
int findKRotation(int nums[], int n)
{
    int low = 0;
    int high = n - 1;
    int ans = -1;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        // Minimum of right sorted can be answer
        if (nums[mid] < nums[high])
        {
            high = mid;
        }
        // Left sorted cannot have answer, if right is not sorted right
        // part only contains the minimum element
        else
            low = mid + 1;
    }
    return high;
}
// T.C-> O(logN)
// S.C-> O(1)
// --------------------------------------------------------------------------------------------------
// 13.Search Single Element in a sorted array
int singleNonDuplicate(vector<int> &nums)
{
    int n = nums.size();
    // To avoid edge cases in binary search, check for them separately
    if (n == 1)
        return nums[0];
    if (nums[0] != nums[1])
        return nums[0];
    if (nums[n - 1] != nums[n - 2])
        return nums[n - 1];

    // Start search space by moving one step as they are handled above
    int low = 1;
    int high = n - 2;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        // Check for a single element
        if (nums[mid - 1] != nums[mid] && nums[mid] != nums[mid + 1])
        {
            return nums[mid];
        }
        // We are on left part of mid i.e
        // ( even, odd) --> single element is in right half, so eliminate left part
        if ((mid % 2 == 1 && nums[mid - 1] == nums[mid]) || (mid % 2 == 0 && nums[mid] == nums[mid + 1]))
        {
            low = mid + 1;
        }
        // We are on right part of mid i.e
        // ( odd, even) --> single element is in lefthalf, so eliminate right part
        else
        {
            high = mid - 1;
        }
    }
    return -1;
}
// T.C-> O(logN)
// S.C-> O(1)
// --------------------------------------------------------------------------------------------------
// 14.  Find Peak Element
// element greater than its left and right element
int findPeakElement(vector<int> &nums)
{
    int n = nums.size();
    // A single element
    if (n == 1)
        return 0;
    // If first element is peak
    if (nums[0] > nums[1])
        return 0;
    // If last element is peak
    if (nums[n - 1] > nums[n - 2])
        return n - 1;
    // Start binary search from one step ahead
    int low = 1;
    int high = n - 2;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        // If mid is the peak element
        if (nums[mid] > nums[mid - 1] && nums[mid] > nums[mid + 1])
            return mid;
        // If we are on right side of the peak i.e. mid element is greater than its next element
        if (nums[mid] > nums[mid + 1])
        {
            high = mid - 1;
        }   
        // We are on left side of peak, i.e. mid element is smaller than its next element
        // This also handles the case where mid element is at 'reverse peak' i.e. ulta cone, valley
        // In that case none of the above cases will be valid, so below will get execute
        else
            low = mid + 1;
    }
    return -1;
}
// T.C-> O(logN)
// S.C-> O(1)