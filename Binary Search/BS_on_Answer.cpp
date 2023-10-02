Note- first tell brute to the interviewer by removing binary search and, iterating 
linearly.

// 1. Square root of a number
long long int floorSqrt(long long int x)
{
    // define the search space
    long long low = 1;
    long long high = x;

    int ans = -1;

    while (low <= high)
    {
        long long mid = (low + high) / 2;

        // if we got some integer whose square is less than or equal to x, we store it and look
        // for larger one
        if (mid * mid <= x)
        {
            ans = mid;
            low = mid + 1;
        }
        // square is larger, so reduce the number by moving towards left
        else
            high = mid - 1;
    }
    return ans;
}
// T.C-> O(logN)
// S.C-> O(1)

// --------------------------------------------------------------------------------------------------
// 2. Find Nth root of M
int check(int num, int n, int m)
{
    long long ans = 1;
    for (int i = 0; i < n; i++)
    {
        ans *= num;
        // If multiplication exceed given number
        if (ans > m)
            return 2;
    }
    // We got our answer
    if (ans == m)
        return 1;
    // multiplication is less than given number i.e we cannot form given number with this mid
    return 0;
}
int NthRoot(int n, int m)
{
    int low = 1;
    int high = m;

    while (low <= high)
    {
        int mid = (low + high) / 2;

        // Check if mid is root or not
        int midN = check(mid, n, m);

        // mid is the root
        if (midN == 1)
        {
            return mid;
        }

        // mid is smaller to give the multiplication 'm'
        else if (midN == 0)
        {
            low = mid + 1;
        }

        // midN == 2, means mid is high, reduce it (multiplication is going large)
        else
            high = mid - 1;
    }
    // No root exists
    return -1;
}
// T.C-> O(N*logM) n for finding multiplication under check function, logm for bs on 1 to m
// S.C-> O(1)
// --------------------------------------------------------------------------------------------------
// 3. Koko eating bananas
long long pred(int m, vector<int> &piles)
{
    long long time = 0;
    for (int i = 0; i < piles.size(); i++)
    {
        // time += ceil((double)piles[i] / m);

        // OR

        // if element is less than hours simply add one hour
        // if (piles[i] <= m)
        // {
            // time++;
        // }
        // element is greater, so add element/hour and if it is not divisible and again 1
        // else
            // time += piles[i] / m + (piles[i] % m != 0);

        // OR

        // justtt
        time += piles[i] / m + (piles[i] % m != 0);
    }

    // If time we get by mid no. of bananas per hour is less than given h, this can be our possible
    // answer, so return true else false.
    return time;
};

int minEatingSpeed(vector<int> &piles, int h)
{
    int n = piles.size();

    int low = 1;
    int high = -1e9;
    for (int i = 0; i < n; i++)
    {
        high = max(high, piles[i]);
    }
    int ans = 0;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        // if mid can satisfy the given h hours condition, go and again find for less number of bananas
        // per hour.
        int reqTime = pred(mid, piles);
        if (reqTime <= h)
        {
            // ans=mid;
            high = mid - 1;
        }
        // mid is not satisfying the 'h' hours condition, so increase no. of bananas per hour
        else
            low = mid + 1;
    }

    // low will be pointing to our ans
    return low;
}
// T.C-> O(N*log(Max))
// S.C-> O(1)
// --------------------------------------------------------------------------------------------------
// 4. Minimum days to make M bouquets
bool pred(vector<int> &nums, int day, int m, int k)
{
    // for maintaining cnt of adjacent days which comes under 'mid' as a day
    int cnt = 0;
    // to count the number of bouqes
    int bouqe = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        // if current day is less than 'mid' day, i.e flower can be bloomed.
        if (nums[i] <= day)
        {
            cnt++;
        }
        // we encounter non-adjacent flowwers, so cnt bouqes that can be formed until now, and make cnt of adjacent
        // flowers as zero
        else
        {
            bouqe += cnt / k;
            cnt = 0;
        }
    }

    // For last set of adjacent flowers
    bouqe += cnt / k;
    return bouqe >= m;
}

int minDays(vector<int> &bloomDay, int m, int k)
{

    int n = bloomDay.size();

    // If required flowers are greater than number of present flowers i.e size of array
    if ((long long)m * (long long)k > n)
        return -1;
    // Range -> min to max
    int low = INT_MAX;
    int high = INT_MIN;

    for (int i = 0; i < n; i++)
    {
        low = min(low, bloomDay[i]);
        high = max(high, bloomDay[i]);
    }

    // We are using ans variable here as we have to return -1, if bouqets are not possible otherwise low will be the answer
    // No need of ans, if case of -1 is handled before
    int ans = -1;

    while (low <= high)
    {
        int mid = (low + high) / 2;
        // if mid can be our answer, set it to ans and find for smaller one
        if (pred(bloomDay, mid, m, k))
        {
            ans = mid;
            high = mid - 1;
        }
        // mid/day is low, bloom more flowers increasing the days
        else
            low = mid + 1;
    }

    return ans;
}
// T.C-> O(N*log(Max-Min))
// S.C-> O(1)
// --------------------------------------------------------------------------------------------------
// 5. Find the Smallest Divisor Given a Threshold
int divSum(vector<int> &nums, int mid)
{
    int sum = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        // sum += ceil((double)nums[i]/m);

        // OR

        // If value is less than divisor, add 1
        // if (nums[i] < mid)
            // sum++;
        // if value is greater than divisor and not completely divisible
        // this actuall acts as a ceil function only.
        // else
            // sum += nums[i] / mid + (nums[i] % mid != 0);


        // OR
        // justtt
        sum += nums[i]/mid + (nums[i]%mid != 0);
    }
    return sum;
}

int smallestDivisor(vector<int> &nums, int threshold)
{

    // If threshild is less than given numbers, as minimum sum of divisors can be n
    // then we cannot form the answer
    if (threshold < nums.size())
        return -1;

    int low = 1;
    int high = 0;

    for (int i = 0; i < nums.size(); i++)
        high = max(high, nums[i]);

    int ans = 0;

    while (low <= high)
    {
        int mid = (low + high) / 2;

        // If divisor/mid satisfies the given condition then look for more smaller one
        int divisor = divSum(nums, mid);
        if (divisor <= threshold)
        {
            ans = mid;
            high = mid - 1;
        }
        // Mid does not satisfies the given condition, i.e. the mid value is too less so, increase it.
        else
            low = mid + 1;
    }

    // low will be pointing to our answer, yesss first low swill be at not possible wala side, at last it will be at opposite i.e at possible side and will be our answer.
    return ans;
}
// T.C-> O(N*log(Max))
// S.C-> O(1)
// --------------------------------------------------------------------------------------------------
// 6. Capacity To Ship Packages Within D Days
class Solution
{
public:
    int possible(vector<int> &weights, int days, int mid)
    {
        // initial load will be 0
        int sum = 0;
        //    We will start loading ship from 1st day
        int d = 1;
        for (int i = 0; i < weights.size(); i++)
        {
            // if we can load the ship, such that it does not exceed the capacity of ship
            if (sum + weights[i] <= mid)
            {
                sum += weights[i];
            }
            else
            {
                // we cannot load the ship anymore, so let put this item on another day
                d++;
                // load the ship on next day with current item
                sum = weights[i];
            }
        }

        return d;
    }

    int shipWithinDays(vector<int> &weights, int days)
    {
        int n = weights.size();
        int low = 0, high = 0;
        for (int i = 0; i < n; i++)
        {
            low = max(low, weights[i]);
            high += weights[i];
        }
        int ans = 0;
        while (low <= high)
        {
            // mid is the capacity, as we minimizing the capacity.
            int mid = (low + high) / 2;
            // if days we required by this capacity(mid) is less than or equal to desired weight,
            // lets look for less capacity
            int d = possible(weights, days, mid);
            if (d <= days)
            {
                // ans=mid;
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        // Answer will be at low, yessss ulta zala ata low, adho non possible part madhe hota na toh!!
        return low;
    }
};
// T.C-> O(N*log(sum - max + 1))
// S.C-> O(1)
// --------------------------------------------------------------------------------------------------
// 7. Kth Missing Positive Number
class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        int cnt = 0;  // Initialize a counter to keep track of missing numbers.
        for(int i = 0; i < arr.size(); i++) {
            if(arr[i] <= k)  // If the current element in the array is less than or equal to k.
                k++;  // Increment k to account for the missing number.
            else
                break;  // If the current element is larger than k, exit the loop.
        }
        return k;  // Return the value of k as the kth missing positive number.
    }
};
// --------------------------------------------------------------------------------------------------


// T.C-> O(N*log(sum - max + 1))
// S.C-> O(1)
// --------------------------------------------------------------------------------------------------
// 8.Aggressive Cows
class Solution {
public:

    bool possible(vector<int> &stalls, int dist, int k){
        // Initially we will place one cow at first stall
        int cowsPlaced = 1;
        int lastPlaced = stalls[0];
        
        for(int i = 1;i<stalls.size();i++){
            // If the distance between stalls is at least mid/dist, place the cow(cow++) and
            // update the lastPlaced position of cow
            if(stalls[i] - lastPlaced >= dist){
                cowsPlaced++;
                lastPlaced = stalls[i];
            }
        }
        
        // If we are able to place at least given nuber of cows, return true else return false
        // cows jar vadhat ahet mhnje tyachya madhla distance kami ahe
        // mg cows kami (k) karnyasathi tyanchyamadhla distance vadhvava lagel na!!
        // khali( code madhe) possible asel tr apana distance vadhvat ahot!!
        return cowsPlaced >= k;
    }

    int solve(int n, int k, vector<int> &stalls) {
        // sort the stalls, as we can get minimum when we place cows adjacent when sorted
        sort(stalls.begin(), stalls.end());
        int low = 1;
        // maxi-mini
        int high = stalls[n-1]-stalls[0];
        int ans = 0;
        while(low <= high){
            
            int mid = (low + high)/2;
            
            // If we can place cows, with distance between them as 'mid', move to right
            // to maximize the distance between them
            if(possible(stalls, mid, k)) {
                ans = mid;
                low = mid + 1;
            }
            // We are not able to place all cows with 'mid' distance apart it is too high, so reduced it
            else high = mid - 1;
        }
        
        // Initially high will be pointing to not possible polarity, at last it will be pointing 
        // to possible/ans
        return ans;
    }
};

// T.C-> O(N*log(maxi - min + 1))
// S.C-> O(1)
// --------------------------------------------------------------------------------------------------
// 9.Book Allocation Problem
class Solution
{
public:
    bool possible(int a[], int pages, int n, int givenStudents)
    {
        // We will start with 1st student
        int students = 1;
        // starting from 0, becaause it is not always sure that first element will be less than
        // maximum pages to be allowed (pages here)
        int currentPages = 0;
        for (int i = 0; i < n; i++)
        {
            // If the pages we are going to allocate comes under maximum pages allowed
            // then only consider it, otherwise allocate it to next student
            if (currentPages + a[i] <= pages)
            {
                currentPages += a[i];
            }
            else
            {
                // We are not able to allocate a[i] pages to previous student do, allocate
                // it to next student
                students++;
                // allocate pages
                currentPages = a[i];
            }
        }

        // If count of students is less than required students, we need to increase the number of students
        // and it can be done by decreasing the number of pages!!
        // kami students la jast jast pages ale tr, no. of pages kami kara mhnje jast students yetil
        return students <= givenStudents;
    }

    // Function to find minimum number of pages.
    int findPages(int A[], int N, int M)
    {
        // If number of book are less than given m students
        if (N < M)
            return -1;

        // Range -> ( max to sum)
        int low = INT_MIN;
        int high = 0;
        for (int i = 0; i < N; i++)
        {
            low = max(low, A[i]);
            high += A[i];
        }

        while (low <= high)
        {
            int mid = (low + high) / 2;
            // if it is possible to distribute 'mid' no. of pages among students count <= M
            // then we will again look for, minimum no. of pages so go to left.
            if (possible(A, mid, N, M))
                high = mid - 1;
            // we are not able to distribute 'mid' pages among given students, student count
            // is getting more than M, so we need to increase the number of pages na!!
            else
                low = mid + 1;
        }

        // high was pointing to possible polarity, as all pages can take single student
        // ans low was pointing to not possible part
        // so at the end polarity gets reversed, so low will be pointing to answer.
        return low;
    }
};
// T.C-> O(N*log(sum - max + 1))
// S.C-> O(1)
// --------------------------------------------------------------------------------------------------
// 10. Split Array Largest Sum
class Solution
{
public:
    bool possible(vector<int> &nums, int maxSum, int k)
    {
        // at start we will be starting with one subarray
        int subArray = 1;
        int sum = 0;
        // count how many subarrays can be formed, keeping largest sum of subarray as mid
        for (int i = 0; i < nums.size(); i++)
        {
            if (sum + nums[i] <= maxSum)
            {
                sum += nums[i];
            }
            else
            {
                subArray++;
                sum = nums[i];
            }
        }
        // If we are getting less subarray's than k, and we want it exact k so we need to increase
        // subarrays, it can be done by minimizing the larget permisable sum of each subarray
        // so we move to left of mid to decrease the largest sum
        return subArray <= k;
    }

    int splitArray(vector<int> &nums, int k)
    {
        int n = nums.size();
        // Range-> ( max to sum) minimum eka subarray chi sum maximum element thevavi lagel
        int low = INT_MIN;
        int high = 0;
        for (int i = 0; i < n; i++)
        {
            low = max(low, nums[i]);
            high += nums[i];
        }
        int ans = 0;
        while (low <= high)
        {
            int mid = (low + high) / 2;
            // if it is possible to form atleast k subarrays (<=k) by kipping 'mid' as largesr sum
            // then we have to increase the subarrays, by decreasing the largest sum od each subarray
            // can take.
            if (possible(nums, mid, k)){
                ans = mid;
                high = mid - 1;
            }
            // Subarrays formed are more than k, so we need to minimize them by increasing largest sum.
            else
                low = mid + 1;
        }

        // first high will be pointing to possible part of answers, as we will be able to form
        // one subarray with largest sum as sum of whole array i.e. at least condition in satisfied!!
        // at last polarity will get changed, low will be pointing to posible part i.e. answer.
        // return ans
        return low;
    }
};
// T.C-> O(N*log(sum - max + 1))
// S.C-> O(1)
// --------------------------------------------------------------------------------------------------
// 12. Painter's Partition Problem
https://www.codingninjas.com/studio/problems/painter-s-partition-problem_1089557?leftPanelTab=0

bool pred(int mid, vector<int> &a, int k){  // Define a function 'pred' to check if a given 'mid' value satisfies the condition

    // first board will be printed by 1 painter
    int painters = 1;  // Initialize the number of painters

    int curr = a[0];  // Initialize the current segment's length with the first element

    int n = a.size();  // Get the size of the input vector 'a'

    for(int i=1;i<n;i++){  // Iterate through the elements starting from the second one
        if(curr + a[i] <= mid){  // If adding the current element to the current segment is within the limit 'mid'
            curr += a[i];  // Expand the current segment
        }
        else{
            painters++;  // If adding the current element exceeds the limit, increment the painter count
            curr = a[i];  // Start a new segment with the current element's length
        }
    }

    return painters <= k;  // Return whether the number of painters required is less than or equal to 'k'
}

int findLargestMinDistance(vector<int> &a, int k)  // Define a function to find the largest minimum distance
{
    int l = INT_MIN;  // Initialize the left boundary as the smallest possible value
    int r = 0;  // Initialize the right boundary as 0

    for(int i=0;i<a.size();i++){  // Iterate through the elements of the input vector 'a'
        l = max(l, a[i]);  // Update the left boundary as the maximum of the current element and the existing left boundary
        r += a[i];  // Update the right boundary by adding the current element
    }

    int ans = 0;  // Initialize the answer variable

    while(l<=r){  // Perform a binary search within the boundaries
        int mid = (l+r)/2;  // Calculate the middle value

        if(pred(mid, a, k)){  // Check if the current middle value satisfies the condition
            ans = mid;  // Update the answer with the current middle value
            r = mid - 1;  // Update the right boundary for further search in the left half
        }
        else
            l = mid + 1;  // Update the left boundary for further search in the right half
    }

    return ans;  // Return the final answer
}
