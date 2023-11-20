1) Row with max 1s

A) Brute:
Iterate each row, and maximize number of ones and store index of that row

B) Better: Binary search each row
Number of 1 in a row: Nummber of elements in row(m) - Lower bound of 1 of that row

class Solution{
public:
   int lower(vector<int> arr,int n,int x){
        int low = 0;
        int high = n-1;
        int ans = n;
        while(low <= high){
            int mid = (low+high)/2;
            if(arr[mid] >= x){
                ans = mid;
                high = mid-1;
            }
            else{
                low = mid+1;
            }
        }
        return ans;
    }

	int rowWithMax1s(vector<vector<int> > arr, int n, int m) {
        int index = -1;
        int max_count = 0;
        for(int i = 0;i<n;i++){
            int count_ones = m - lower(arr[i],m,1);
            if(count_ones > max_count){
                max_count = count_ones;
                index = i;
            }
        }
        return index;
	}
};

C) Optimal:
O(N+M): Traverse from top right corner:
//User function template for C++
class Solution{
public:
	int rowWithMax1s(vector<vector<int> > arr, int n, int m) {
        int i = 0;       // Start from the first row (topmost row)
        int j = m - 1;   // Start from the last column (rightmost column)
        int ans = -1;    // Initialize the answer to -1 (no row with all 1s found yet)
    
        // The loop continues as long as we are within the bounds of the matrix
        // and haven't reached the first column or last row
        while (i < n && j >= 0) {
            if (arr[i][j] == 1) {
                // If the current element is 1, it means that this row has not encountered a 0 yet.
                // This row might be a candidate for having all 1s. We update 'ans' to the current
                // row index (i) and move one column to the left (j--) to check for 0s in the same row.
                ans = i; //kontya row la continue hot ahe 1's
                j--;
            }
            else if (arr[i][j] == 0) {
                // If the current element is 0, it means that the current row can't have
                // all 1s since we encountered a 0. Therefore, we move to the next row (i++) 
                // to check the row below.
                i++;
            }
        }
        return ans;  // Return the row index containing the maximum number of 1s
	}

};
-----------------------------------------------------------------------------------------------
2) Search a 2D Matrix
Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous row

A) Brute: O(N*M)

B) Binary Search: Notes bgh
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int lo = 0;
        if(!matrix.size()) return false;
        int hi = (matrix.size() * matrix[0].size()) - 1;
        
        while(lo <= hi) {
            int mid = (lo + (hi - lo) / 2);
            if(matrix[mid/matrix[0].size()][mid % matrix[0].size()] == target) {
                return true;
            }
            if(matrix[mid/matrix[0].size()][mid % matrix[0].size()] < target) {
                lo = mid + 1;
            }
            else {
                hi = mid - 1;
            }
        }
        return false;
    }
};
--------------------------------------------------------------------------------------
3) Search a 2D Matrix II | Search in a row and column-wise sorted matrix

Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom

A) Brute:
bool searchElement(vector<vector<int>>& matrix, int target) {
    int n = matrix.size(), m = matrix[0].size();

    //traverse the matrix:
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == target)
                return true;
        }
    }
    return false;
}
B) Better:
Binary search on each row:
bool binarySearch(vector<int>& nums, int target) {
    int n = nums.size(); //size of the array
    int low = 0, high = n - 1;

    // Perform the steps:
    while (low <= high) {
        int mid = (low + high) / 2;
        if (nums[mid] == target) return true;
        else if (target > nums[mid]) low = mid + 1;
        else high = mid - 1;
    }
    return false;
}

bool searchElement(vector<vector<int>>& matrix, int target) {
    int n = matrix.size();

    for (int i = 0; i < n; i++) {
        bool flag =  binarySearch(matrix[i], target);
        if (flag) return true;
    }
    return false;
}

C) Optimal:
Start from top right corner:
Top right pasun start kara, ani check kara ki target tya value pekshya chota
ahe ka jar ahe tr ti tya corresponding row madhe ahe, nhi tr column madhe
ahe mhnje ti value target motha ahe tya value pekshya.

We can also start from bottom left and right logic accordingly

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& mat, int t) {
        int n =  mat.size();
        int m = mat[0].size();
        int i = 0, j = m-1;
        // traverse the matrix from (0, m-1):
        while(i<n && j>=0){
            // we got the element
            if(mat[i][j] == t) return true;
            // target is grater, so it will lie in beneath column
            if(t > mat[i][j]) i++;
            // target is small, so it will lie in corresponding row
            else j--;
        }
        return false;
    }
};
**************************************************************************************************