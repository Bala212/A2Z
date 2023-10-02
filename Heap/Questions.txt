1) Kth Largest Element in an Array

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();

        // declare min heap
        priority_queue<int, vector<int> , greater<int>> pq;

        for(int i = 0;i<n;i++){
            // push current element in pq
            pq.push(nums[i]);
            // if size exceeds k, pop the element, to remove n-k largest elements from queue
            if(pq.size()>k) pq.pop();
        }

        // return top of the queue
        return pq.top();
    }
};

Time complexity: O(n*logk)
Space complexity: O(k)
-------------------------------------------------------------------------------------------------------------------------------------------------------
2) Kth Smallest Element in an Array

//User function template for C++

class Solution{
    public:
    int kthSmallest(int arr[], int k) {
        int n = arr.size();
        priority_queue<int> pq;
        for(int i =0;i<n;i++){
            pq.push(arr[i]);
            if(pq.size() > k) pq.pop();
        }
        
        return pq.top();
    }
};

Time complexity: O(n*logk)
Space complexity: O(k)
-------------------------------------------------------------------------------------------------------------------------------------------------------
3) Merge k Sorted Arrays

class Solution
{
    public:
    //Function to merge k sorted arrays.
    vector<int> mergeKArrays(vector<vector<int>> arr, int k)
    {
        // mim heap of pair of pair
        // {element, {array number, index of element in that array} }
        priority_queue< pair<int, pair<int, int>>, vector<pair<int, pair<int, int>> > ,
        greater<pair<int, pair<int, int>> >> pq; 
        
        // Push 1st element of every array!
        for(int i = 0;i<k;i++){
            // {element, {array number, index of element in that array} }
            pq.push({arr[i][0] ,{i, 0 }});
        }
        
        vector<int> ans;
        // traverse and extract minimum element always from pq, and push into ans
        while(!pq.empty()){
            auto top = pq.top();
            pq.pop();
            // get the element
            int ele = top.first;
            // get the array number
            int arrNum = top.second.first;
            // get the index of that element
            int arrInd = top.second.second;
            
            // push the ele in ans, which will be minimum
            ans.push_back(ele);
            
            // index should be under array!!, and array is of size k
            if(arrInd+1 < k){
                // push next element, arrNumber and index of pushed element
                pq.push({arr[arrNum][arrInd+1], {arrNum, arrInd+1}});
            }
        }
        
        // As we are traversing the entire 2D matrix, by pushing each element in pq
        // T.C -> K*KlogK
        return ans;
    }
};

        // As we are traversing the entire 2D matrix, by pushing each element in pq
        // T.C -> K*KlogK -> pq will contain k elements always
-------------------------------------------------------------------------------------------------------------------------------------------------------
4) Merge k Sorted Lists

class cmp{
    public:
    bool operator()(ListNode *a,ListNode *b){
        return (a->val)>(b->val);
    }
};


class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& arr) {
        int K = arr.size();
        priority_queue<ListNode*,vector<ListNode*>, cmp>pq;

        // Push all Nodes in pq
        for(int i=0;i<K;i++){
            if(arr[i] != NULL) pq.push(arr[i]);
        }

        // create a dummy node, to return the answer
        ListNode* head = new ListNode(-1);
        ListNode* ans = head;

        while(!pq.empty()){
            // pop the node, as its min heap we will get the node with minimum value
            ListNode* node = pq.top();
            pq.pop();

            // Attach the node, to ans i.e. change the linkage
            head -> next = node;
            // point head ti current node
            head = node;

            // Push next node of current List into pq
            if(node->next != NULL) pq.push(node->next);
        }

        return ans->next;
    
    }
    // T.C -> N*M*logM
};
-------------------------------------------------------------------------------------------------------------------------------------------------------
5) Replace elements by its rank in the array

vector<int> replaceWithRank(vector<int> &arr, int n) {
    // Create a map to store the rank of each unique element
    map<int, int> mp;
    int temp = 1;
    
    // Create a copy of the input array to sort
    int brr[n];
    for (int i = 0; i < n; i++) {
        brr[i] = arr[i];
    }
    
    // Sort the copy of the array to find the ranks
    sort(brr, brr + n);
    
    // Assign ranks to each unique element in the sorted array
    for (int i = 0; i < n; i++) {
        // If the element is encountered for the first time, assign a rank and increment the rank counter
        if (mp[brr[i]] == 0) {
            mp[brr[i]] = temp;
            temp++;
        }
    }

    // Create a vector to store the ranks corresponding to the original array elements
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        // Replace each element with its rank
        ans.push_back(mp[arr[i]]);
    }

    return ans;
}

Time Complexity:O(n)+O(nlogn)+O(n). O(n) for copying the elements from the original to the dummy array, 
                O(nlogn) for sorting the dummy array, and O(n) for printing the ranks.

Space Complexity:O(N+N), for using dummy array and hashmap.
-------------------------------------------------------------------------------------------------------------------------------------------------------
6) Task Scheduler

class Solution {
public:
    int leastInterval(vector<char>& tasks, int k) {
        // store freq, char in pq
        if(k==0) return tasks.size();
        priority_queue< pair<int,char>> pq;
        int n = tasks.size();
        unordered_map<char,int> m;
        for(int i=0;i<n;i++){
            m[tasks[i]]++;
        }

        for(auto &val : m){
            pq.push({val.second, val.first});
        }


        int time = 0;
        while(!pq.empty()){
            // to store popped elements from pq, to push them later to avoid same task under the 
            // idle time
            // this makes sure that unique tasks are performed under the idle time
            vector< pair<int,int>> temp;

            // perform k+1 tasks
            for(int i = 0;i<=k;i++){
                // No more tasks to complete, i.e. all tasks are exhausted
                if(pq.empty() && temp.size() == 0) break;
                
                // k+1 tasks are done, no need to push anymore
                if(!pq.empty()){
                    char ch = pq.top().second;
                    int freq = pq.top().first;
                    pq.pop();
                    freq--;
                    if(freq>0)
                    temp.push_back({freq, ch});
                }
                // we have to add idle time also
                time ++;
            }
            
            // push proceesed tasks again into the queue
            for(auto &val:temp){
                pq.push(val);
            }
        }


        return time;
    }
};
-------------------------------------------------------------------------------------------------------------------------------------------------------
7) Hand of Straights

using map:

class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        // Create a map to store the frequency of each card value in the hand
        map<int, int> m;
        int n = hand.size();
        
        // Count the frequency of each card value in the hand
        for (int i = 0; i < n; i++) {
            m[hand[i]]++;
        }

        // Loop until the map is not empty
        while (!m.empty()) {
            // Get the smallest card value in the current sequence
            int ele = m.begin()->first;
            
            // Check for the consecutive groupSize elements
            for (int i = 0; i < groupSize; i++) {
                // If the next value is not found or its frequency is 0, return false
                if (m.find(ele + i) == m.end() || m[ele + i] == 0) {
                    return false;
                }
                
                // Decrease the frequency of the current card value
                m[ele + i]--;
                
                // If the frequency becomes 0, remove the card value from the map
                if (m[ele + i] == 0) {
                    m.erase(ele + i);
                }
            }
        }
        
        // All groupSize consecutive sequences are valid, return true
        return true;
    }
};

using pq:
Intuition is simple just add all the elements in the heap at first, now take out elements which are just greater than the 
current element and take a note of group size, if ever curr group size does not meet the required group size, we return false

class Solution {
public:
        bool isNStraightHand(vector<int> &hand, int groupSize)
    {
        priority_queue<int, vector<int>, greater<int>> pq;
        // Insert all the elements in the heap
        for (auto val : hand)
            pq.push(val);

        while (!pq.empty())
        {
            vector<int> rem; // Storing the duplicate elements

            int group = groupSize - 1; // Current group size, -1 because we take out one element in the beginning

            int prev = pq.top();
            pq.pop(); // Taking out the first element of the group

            while (!pq.empty() and group)
            {
                if (pq.top() == prev + 1) // Checking the criteria of inclusion
                {
                    prev = pq.top();
                    group--; // If included then reduce the size of current group
                }
                else
                    rem.push_back(pq.top()); // If not included then simply put it in remaining elements
                pq.pop();
            }

            for (auto x : rem)
                pq.push(x); // Push the remaining elements in the heap
            // If the size of the current group is not equal to the required group size then return false
            if (group)
                return false;
        }
        return true; // If all the groups meet the requirement then just return true
    }
};
-------------------------------------------------------------------------------------------------------------------------------------------------------
8) Top K Frequent Elements

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // We will store pair in pq
        // first element will be be the frequency of elements, and second element will be element itself
        // to sort the elements in pq according to their frequencies in the heap
        // We have to pop the elements from queue which has minimum frequency(logic of kth largest element), 
        // so we will be using min heap
        // at last elements with  maximum frequencies will be left in queue
        // extract and return them

        int n = nums.size();
        priority_queue< pair<int,int>, vector<pair<int,int>> , greater<pair<int,int>> > pq;
        unordered_map<int,int> m;

        // get the frequency of elements
        for(int i=0;i<n;i++){
            m[nums[i]]++;
        }

        // pop elements with, less frequency by kipping k elements in queue
        for(auto &val : m){
            pq.push({val.second, val.first});
            if(pq.size() > k ) pq.pop();
        }

        // queue will contain k elements with having maximum count
        vector<int> ans;
        while(!pq.empty()){
            ans.push_back(pq.top().second);
            pq.pop();
        }

        return ans;
    }
};
T.C -> No. of unique elements*K
-------------------------------------------------------------------------------------------------------------------------------------------------------
9) Minimum Cost of ropes

class Solution
{
    public:
    //Function to return the minimum cost of connecting the ropes.
    long long minCost(long long arr[], long long n) {
        // Your code here
        priority_queue<long long, vector<long long>, greater<long long>> pq;
        
        for(int i=0;i<n;i++){
            pq.push(arr[i]);
        }
        
        long long ans = 0;
        
        while(pq.size()>1){
            long long a = pq.top();
            pq.pop();
            
            long long b = pq.top();
            pq.pop();
            
            long long sum = a + b;
            
            ans += sum;
            
            pq.push(sum);
        }
        
        return ans;
    }
};
-------------------------------------------------------------------------------------------------------------------------------------------------------
10) Find Median from Data Stream

class MedianFinder {
public:

    // WE WILL THINK ARRAY IN TWO PARTS IN SORTED MANNER, LIKE LEFT PART WILL BE MAX HEAP
    // AS WE WANT ELEMENTS AROUND MID OF ARRAY, MAX HEAP WILL GIVE US THE MAXIMUM AMONG THE LEFT OF MEDIAN
    // PART OF ARRAY
    // SIMILARLY, RIGHT PART(THINK OF SORTED ARRAY) WILL STORED IN MIN HEAP, AS WE WANT CLOSE TO MID I.E.
    // MINIMUM AMONG RIGHT PART, WHICH WIL BR AT TOP OF HEAP

    // declare min ad max heaps
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int> > minHeap;
    // initially both heaps are empty, so whole length is even
    bool even = 1;

    MedianFinder() {
        
    }
    
    void addNum(int num) {
        // if length in even, we will add incoming element into max heap, we can also add
        // it to min heap
        if(even){
            // as we want mimimum elements in max heap, first push it into min heap so that
            // if incoming element is greater, it will get stored in min heap and we will get
            // the minimum element
            minHeap.push(num);
            int ele = minHeap.top();
            minHeap.pop();
            maxHeap.push(ele);
        }
        // if length in odd, means there are more elements in max heap, as we are pushing element
        // in max heap, when both have same size, but as we want max elements in min heap we will
        // first push it into max heap, if incoming element is smaller it will get stored into
        // max heap, and we will pop maxHeap and push it into min heap, so we got max element
        // in min heap
        else{
            maxHeap.push(num);
            int ele = maxHeap.top();
            maxHeap.pop();
            minHeap.push(ele);
        }
        even = !even;
    }
    
    double findMedian() {
        if(even){
            // median will be top of avg of top of both heaps
            double num1 = minHeap.top();
            double num2 = maxHeap.top();
            double ans = (num1+num2)/2;
            return ans;
        }
        else{
            // when length is odd, maxHeap will contain one more element than min heap, so return
            // top of max heap
            return maxHeap.top();
        }
    }
};
-------------------------------------------------------------------------------------------------------------------------------------------------------
11) Is Binary Tree Heap

class Solution {
  public:
  
    int countNodes(struct Node* root){
        if(root == NULL) return 0;
        // count left and right nodes, and add root also
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
    
    bool isCBT(struct Node* root, int ind, int totalNodes){
        // empty tree is a CBT
        if(root == NULL) return true;
        
        // if index number exceeds total count of nodes, this checks the right align of nodes
        // at last level
        if(ind >= totalNodes) return false;
        
        // check left and right nodes, go on their respective indexes
        bool left = isCBT(root->left, 2*ind+1, totalNodes);
        bool right = isCBT(root->right, 2*ind+2, totalNodes);
        
        // true if left and right subtrees are CBT
        return left && right;
    }
    
    bool isProperty(struct Node* root){
        
        // leaf node satisfies the property
        if(root->left == NULL && root->right == NULL) return true;
        
        // by CBT it is sure that, the nodes would be left as possible at last level
        // so right node can be NULL, so if it is NULL check for left node whether it is smaller
        // than root or not
        if(root -> right == NULL){
            return root->data > root->left->data;
        }
        
        // both nodes are present, so check for them as well
        bool isLeftAndRightSmaller = root->data > root->left->data && root->data > root->right->data;
        
        // check left and right subtree
        bool left = isProperty(root->left);
        bool right = isProperty(root->right);
        
        // return true, is all above three are satisfied
        return isLeftAndRightSmaller && left && right;
        
    }
  
    bool isHeap(struct Node* tree) {
        
        // Time -> O(3*N)
        // Space -> O(3*H)
        
        // root index is 0, we start checking from root so we need index to verify CBT
        int index = 0;
        
        // count total nodes in a tree
        int totalNodes = countNodes(tree);
        
        // Tree has to Complete Binary Tree and Max heap property should be satisfied
        return isCBT(tree, index, totalNodes) && isProperty(tree);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------
12) Merge two binary Max heaps

class Solution{
    public:
    
    void heapifyMax(int i, int n, vector<int> &arr)
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

    
    vector<int> mergeHeaps(vector<int> &a, vector<int> &b, int n, int m) {
        // 1) store a and b in one vector
        vector<int> temp(a.begin(), a.end());
        
        for(int i = 0;i<m;i++){
            temp.push_back(b[i]);
        }
        
        // size of temp
        int size = n+m;
        
        // 2) Heapify the temp array, to build max heap
        // 0 based heap
        for(int i = size/2-1; i >= 0 ; i-- ){
            heapifyMax(i,size,temp);
        }
        
        // return updated array according to max heap property
        return temp;
    }
};
-------------------------------------------------------------------------------------------------------------------------------------------------------
13) Convert BST to Min Heap

#include <bits/stdc++.h> 
void find_inorder(BinaryTreeNode * root, vector<int>& ans){

    if(root == NULL){

        return;

    }

    find_inorder(root->left, ans);

    ans.push_back(root->data);

    find_inorder(root->right, ans);

}

void constructTree(BinaryTreeNode* root, vector<int>& ans, int &i){

    if(i == ans.size()){

        return;

    }

    if(root == NULL){

        return;

    }

    root->data = ans[i++];

    constructTree(root->left, ans, i);

    constructTree(root->right, ans, i);

}

BinaryTreeNode* convertBST(BinaryTreeNode* root)
{
	// As it's CBT, no need to change the structure of tree

	// Node(N) ka -> Left(L) and Right(R)
	// Heap property-> N<L && N<R
	// BST -> L<R
	// Get the sorted elements of tree using inorder fashion
	// Therefore -> N<L<R which is the preorder form( Root, left, right)
	// So we can fill the tree in preorder fashion, to get the required answer

// Create an array arr[] of size N, where N is the number of nodes in the given BST.
// Perform the inorder traversal of the BST and copy the node values in the arr[] in 
// sorted order.
// Now perform the preorder traversal of the tree.
// While traversing the root during the preorder traversal, one by one copy the values 
// from the array arr[] to the nodes of the BST.
	
    // vector to store the data of all the
    // nodes of the BST
     vector<int> inorder;
    // store the inorder
    find_inorder(root, inorder);

    int index = 0;

	// copy the inorder nodes into tree
    constructTree(root, inorder, index);

    return root;
}
-------------------------------------------------------------------------------------------------------------------------------------------------------
14) K-th Largest Sum Contiguous Subarray

class Solution{
public:
    int kthLargest(vector<int> &Arr,int n,int k){

        // We have to pop the minimum sums(n-k) among all the subarray sums!!
        priority_queue<int, vector<int> , greater<int> > pq;

        // remove n-k smallest sums, so that we will left with k largest sums in priority queue!!
        for(int i = 0;i<n;i++){
            int sum = 0;
            for(int j = i;j<n;j++){
                sum += Arr[j];
                // push each subarray sum in pq
                pq.push(sum);
                // If size exceeds k, pop the minimumm sum from pq (min heap)
                if(pq.size() > k) pq.pop();
            }
        }
        
        // top of min heap will be required sum
        return pq.top();
        // Instead of sorting all sums, we are just playing with k elements(sum) in pq
	// then complexity will be (N^2)*log(N^2).
    }
    // T.C -> N^2*logK
};
-------------------------------------------------------------------------------------------------------------------------------------------------------
15) Smallest Range Covering Elements from K Lists 

class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        // step1: Push first elements of each array into min heap
        // step2: traverse through pq, find minimum(top of pq) and maximum(keep track) element from pq
        // Find length of range of current elements in pq, which will be maxi - mini + 1
        // Here,we have minimize the length of range,everytime when we get the minimum range length than prev
        // We will update the range length, and store the starting element and ending element when we get\
        // the shorter length

        // declare min heap, which will store element, arrNumber and index (see merge k sorted arrays)
        priority_queue< pair<int,pair<int,int>> , vector<pair<int,pair<int,int>> >, greater<pair<int,pair<int,int>> > > pq; 

        int maxi = -1e9;
        int n = nums.size();
        for(int i = 0;i<n;i++){
            pq.push({nums[i][0],{i,0}});
            maxi = max(nums[i][0], maxi);
        }
        // start and end will be the mini and maxi from among first elements from arrays, which are stored
        // in pq
        int start = pq.top().first;
        int end = maxi;
        int range = maxi - start + 1;
        while(!pq.empty()){
            int mini = pq.top().first;
            int arrNum = pq.top().second.first;
            int arrInd = pq.top().second.second;
            pq.pop();

            int currentRange = maxi-mini+1;
            if(currentRange < range){
                // update range, start and end of range
                range = currentRange;
                start = mini;
                end = maxi;
            }
            
            // Push Next element of current array, if exists
            if(arrInd +1 < nums[arrNum].size()){
                pq.push({nums[arrNum][arrInd+1] , {arrNum, arrInd+1 } });
                // update the maximum element
                maxi = max(maxi,nums[arrNum][arrInd+1]);
            }
            // if one of the array exceeds, stop the traversals
            else break;
        }

        // return start and end of range
        return {start, end};
    }

    // T.C -> T*logK - T is number of elements in entire 2D array
};
-------------------------------------------------------------------------------------------------------------------------------------------------------
16) Reorganize String

class Solution {
public:
    string reorganizeString(string s) {
        // We will store frequency and character in the priority queue/max heap
        // At a time we will pop two elements from pq, and append the characters associated with them
        // in ans string, and again push that character by deacreasing its frequency, but push only if it's
        // frequncy is greater tha 0, in this way go on until pq becomes empty, at last we will get our
        // string. Here we are using max heap because we want to spread characters with more frequency first

        if(s.size() ==1) return s;
        priority_queue< pair<int,int> > pq;

        unordered_map<char, int> m;

        for(int i=0;i<s.length();i++){
            m[s[i]]++;
        }
        for(auto it:m){
            pq.push({it.second,it.first});    //<int,char>      
        }

        // string is "aaaa"
        if(pq.size()==1) return "";

        
        string res="";
        while(pq.size()>1)
        {
		    //take most occuring char and concatentae it to the result string
            int x = pq.top().first;
            char c1 = pq.top().second;
            pq.pop();
			res+=c1;
			// Now hold this element for a while and take the second most occuring element so that if same
            // element is are not together
            int y = pq.top().first;
            char c2 = pq.top().second;
            pq.pop();
            res+=c2;
			// Decrease the occurance of already taken elements and push them with their updated occurance in the
            // priority queue
            x--;
            y--;
            if(y>0)
                pq.push(make_pair(y,c2));
            if(x>0)
                pq.push(make_pair(x,c1));
        }

        // One character left, if its freq is more than 1 return "" as we will not be able to spread them
        // with given condition, if not then push that single character into res string
        if(pq.size() ==1){
            if(pq.top().first > 1) return "";
            else res += pq.top().second;
        }

        return res;
        
    }
};
-------------------------------------------------------------------------------------------------------------------------------------------------------
17) Nearly sorted | Sort a k sorted array

Given an array of n elements, where each element is at most k away from its target position, you need to sort the array optimally.

class Solution
{
    public:
    //Function to return the sorted array.
    vector <int> nearlySorted(int arr[], int num, int k){
        vector<int> ans;
        
        // We will always keep k elements in an pq(min heap) as we need minimum element 
        // everytime form a stream of k elements, while pushing into ans vector
        // When we exceed the queue size by k, we pop the top ele(minimum) and push into ans
        // by doing this, we will push n-k small elemenst from pq into ans
        // at last will will push rest k smaller elements from queue into array
        
        // Basically, apan array la k parts madhe sort karat ahe
        
        priority_queue<int, vector<int>, greater<int>> pq;
        
        // this will push first n-k smaller elements into ans
        for(int i = 0;i<num;i++){
            // push current element into queue
            pq.push(arr[i]);
            // if size exceeds k, that means we pushed a stream of size k into pq
            // ann then we will push the top most element which will be minimum of that stream of size k
            // and then pop that element from current stream, to move to the next stream
            if(pq.size() > k){
                ans.push_back(pq.top());
                pq.pop();
            }
        }
        
        // extract last k smaller elements from queue
        while(!pq.empty()){
            // everytimr minimum element will get pushed!!
            ans.push_back(pq.top());
            pq.pop();
        }
        return ans;
    }
};	
-------------------------------------------------------------------------------------------------------------------------------------------------------
18) Return k largest elements in an array 

class Solution{
public:	
	vector<int> kLargest(int arr[], int n, int k) {
        priority_queue<int, vector<int> , greater<int> > pq;
        vector<int> ans;
        
        for(int i=0; i<n; i++){
            pq.push(arr[i]);
            
            if(pq.size()>k){
                pq.pop();
            }
        }
        
        int temp;
        
        while(!pq.empty()){
            temp = pq.top();
            ans.push_back(temp);
            pq.pop();
        }
        
        reverse(ans.begin(), ans.end()); //optional
        
        return ans;
	}

};
-------------------------------------------------------------------------------------------------------------------------------------------------------
19) Find K Closest Elements

class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        // We will store pair in pq
        // first element will be be the abs difference of element and x, and second element will be element itself
        // to sort the elements is pq according to their difference
        // We have to pop the elements from queue which has maximum abs difference, as they will be far from the x
        // so we will use max heap, of pair
        // at last elements with least abs difference will be left in queue

        int n = arr.size();

        priority_queue<pair<int,int> > pq;

        for(int i = 0;i<n;i++){
            // push diff and element
            pq.push({abs(x-arr[i]), arr[i]});
            // if size exceeds k, pop the element with maximum abs difference
            if(pq.size()>k) pq.pop();
        }

        // extract elements with, minimum absolute difference
        vector<int> ans;
        while(!pq.empty()){
            int ele = pq.top().second;
            ans.push_back(ele);
            pq.pop();
        }

        // we want ans in sorted fashion
        sort(ans.begin(), ans.end());

        return ans;
    }

};
-------------------------------------------------------------------------------------------------------------------------------------------------------
20) Sort Array by Increasing Frequency

We can use priority queue, by keeping key as a frequency, if there is no such condition that if frequency is same then store them in 
decreasing/increasing fashion (reverse of how the frequency has to sorted). But if there is some reverse condition when frequency is same, 
then we need to use vector of pair and sort it using comparator function.

class Solution {
public:

    bool static cmp(pair<int,int>a, pair<int,int>b){
        if(a.second == b.second){
            return a.first>b.first;
        }
        return a.second<b.second;
    }


    vector<int> frequencySort(vector<int>& nums) {

        // get the frequency
        // store them in vector of pair
        // sort the vector acc to given condition using cmp function
        // extract the values from vector
        unordered_map<int,int> m;
        int n= nums.size();
        for(int i=0;i<n;i++){
            m[nums[i]]++;
        }

        vector<pair<int,int>> v;

        for(auto &val : m){
            v.push_back({val.first, val.second});
        }

        sort(v.begin(), v.end(), cmp);
        vector<int> ans;
        for(auto &val : v){
            int cnt = val.second;
            int num = val.first;
            for(int i = 0;i<cnt;i++){
                ans.push_back(num);
            }
        }
        return ans;
    }
};
-------------------------------------------------------------------------------------------------------------------------------------------------------
21) K Closest Points to Origin

class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& v, int k) {

        // use max heap to pop coordinates far from origin
	// {dist, index}
        priority_queue<pair<long long ,int>> pq;

        int n = v.size();
        // get k coordinates close(minimum dist from origin) in the pq
        // by popping (k-n) large distance coordinates from pq when size exceeds k
        for(int i = 0;i<n;i++){
            double x = v[i][0];
            double y = v[i][1];
            // can be be xsquare + ysquare
            long double temp = x*x + y*y;
            // store distane and index of coordinate, to access the coordinate later
            pq.push({temp, i});

            if(pq.size() > k) pq.pop();
        }

        vector<vector<int>> ans;
        
        // extract closest k coordinates from pq
        while(!pq.empty()){
            int ind = pq.top().second;
            int x = v[ind][0];
            int y = v[ind][1];
            ans.push_back({x,y});
            pq.pop();
        }
        return ans;
    }
};
-------------------------------------------------------------------------------------------------------------------------------------------------------
22) Sum of elements between k1'th and k2'th smallest elements

class Solution{
    public:
    
    long long kthSmallest(long long arr[], long long n, long long k) {
        //code here
        priority_queue<int> pq;
        
        for(int i =0;i<n;i++){
            pq.push(arr[i]);
            if(pq.size() > k) pq.pop();
        }
        
        return pq.top();
    }
    
    long long sumBetweenTwoKth( long long A[], long long N, long long K1, long long K2)
    {
        // get k1th and k2th smallest elemenst
        int k11 = kthSmallest(A,N,K1);
        int k22 = kthSmallest(A,N,K2);
        
        long long ans = 0;
        // sum up those elements who lies between k11 and k22 exclusively
        for(int i = 0;i<N;i++){
            if(A[i] > k11 && A[i] < k22){
                ans += A[i];
            }
        }
        
        return ans;
    }
};
****************************************************************************************************************************************************************