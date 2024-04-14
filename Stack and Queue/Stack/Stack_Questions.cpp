1) Implement two stacks in an array
class twoStacks
{
    int *arr;
    int size;
    int top1, top2;
    public:
    
    twoStacks(int n=100)
    {
        size = n; 
        arr = new int[n]; 
        top1 = -1; 
        top2 = size;
    }
 
    //Function to push an integer into the stack1.
    void push1(int x)
    {
        if(top2 - top1 > 1){
          top1++;
          arr[top1] = x;
        }
    }
    
    //Function to push an integer into the stack2.
    void push2(int x)
    {
       if(top2 - top1 > 1){
          top2--;
          arr[top2] = x;
        }
    }
    
    //Function to remove an element from top of the stack1.
    int pop1()
    {
        if(top1!=-1){
            int ele = arr[top1];
            top1--;
            return ele;
        }
        return -1;
    }
    
    //Function to remove an element from top of the stack2.
    int pop2()
    {
       if(top2!=size){
            int ele = arr[top2];
            top2++;
            return ele;
        }
        return -1;
    }
};
---------------------------------------------------------------------------------------------------------------------
2) Delete middle element of a stack
class Solution
{
    public:
    //Function to delete middle element of a stack.
    
    void solve(stack<int> &s, int cnt, int size){
        if(cnt == size/2){
            s.pop();
            return ;
        }
        
        int x = s.top();
        
        s.pop();
        
        solve(s,cnt+1,size);
        
        s.push(x);
    }
    
    void deleteMid(stack<int>&s, int sizeOfStack)
    {
        solve(s,0,sizeOfStack);
    }
};
---------------------------------------------------------------------------------------------------------------------
3) Insert An Element At Its Bottom In A Given Stack
#include <bits/stdc++.h> 

void solve(stack<int> &s, int x){
    if(s.empty()){
        s.push(x);
        return;
    }

    int num = s.top();
    s.pop();
    solve(s,x);
    s.push(num);
}

stack<int> pushAtBottom(stack<int>& myStack, int x) 
{
    solve(myStack,x);
    return myStack;
}
---------------------------------------------------------------------------------------------------------------------
4) Reverse a Stack
class Solution{
public:

    void insertAtBottom(stack<int> &s, int num){
        if(s.empty()){
            s.push(num);
            return;
        }
        
        int x = s.top();
        s.pop();
        insertAtBottom(s,num);
        s.push(x);
    }

    void Reverse(stack<int> &St){
        if(St.empty()) return;
        
        int x = St.top();
        St.pop();
        Reverse(St);
        insertAtBottom(St,x);
    }
};
---------------------------------------------------------------------------------------------------------------------
5) Sort a Stack
void sortedInsert(stack<int> &s, int x){
    // pop until we get element which is less than or equal to element to be inserted
    // so that we pop all the elements greater than the element to be inserted
    if(s.empty() || s.top()<=x){
        s.push(x);
        return;
    }
    int num = s.top();
    s.pop();
    sortedInsert(s, x);
    s.push(num);
}

void SortedStack :: sort()
{
    // Make a stack empty, and insert elements sortedly
    if(s.empty()) return;
    int x = s.top();
    s.pop();
    sort();
    sortedInsert(s, x);
}
---------------------------------------------------------------------------------------------------------------------
6) Redundant Brackets
#include <bits/stdc++.h> 
bool findRedundantBrackets(string &s)
{
    stack<char> st;
    for(int i = 0;i<s.size();i++){
        // Push opening brackets and operators, which matters for us
        // we have to check for oprators between opening and closing brackets
        if(s[i] == '(' || s[i] == '/' || s[i] == '*' || s[i]=='-' || s[i] == '+'){
            st.push(s[i]);
        }
        // s[i] can be a, b, c... so check for closing bracket
        else if(s[i] == ')'){
            // if there is immediate openeing bracket, i.e. there is no operator
            // between this brackets
            if(st.top() == '(') return true;
            // Go until we get opening bracket, pop *, +, -, / which will fall
            // under this two brackets
            while(st.top() != '('){
                st.pop();
            }
            // pop the opening bracket too
            st.pop();
        }
    }
    // there is no redundancy!!
    return false;
}
---------------------------------------------------------------------------------------------------------------------
7) Minimum Cost To Make String Valid
#include <bits/stdc++.h> 
int findMinimumCost(string str) {
  // if length is odd, return -1
  if(str.length()%2 ==1) return -1;
  stack<char> s;
  for(int i = 0;i<str.size();i++){
    if(str[i] == '{') s.push(str[i]);
    else{
      if(!s.empty() && s.top() == '{') s.pop();
      else s.push(str[i]);
    }
  }

  int a = 0, b=0;
  while(!s.empty()){
    if(s.top() == '{'){
      a++;
    }
    else b++;
    s.pop();
  }
  
  return (a+1)/2 + (b+1)/2;
}
---------------------------------------------------------------------------------------------------------------------
8) Minimum Number of Swaps to Make the String Balanced 
https://leetcode.com/problems/minimum-number-of-swaps-to-make-the-string-balanced/
   int minSwaps(string s) {
      stack<char> st;
      for(char &ch:s){
      if(ch=='[')  st.push(ch);
      else if(!st.empty()) st.pop();
      }
      return (st.size()+1)/2;
    }
---------------------------------------------------------------------------------------------------------------------
9) Next Greater Element I
https://leetcode.com/problems/next-greater-element-i
// We have to return next greater elements of elements present in nums1
// by computing next greatest elements of nums2, basically nums1 is subset if nums2
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        int m = nums2.size();
        vector<int> ans(n,-1);
        stack<int> s;
        unordered_map<int,int> mp;

         for(int i = m-1;i>=0;i--){
            while(!s.empty()){
                if(s.top() > nums2[i]){
                    mp[nums2[i]] = s.top();
                    break;
                }
                s.pop();
            }
            s.push(nums2[i]);
        }

        for(int i = 0;i<n;i++){
            // If the value to any element is zero, means there is no next greater element
            // for that element, so let it be -1, as ans is initilized with -1!!
            if(mp[nums1[i]] != 0)
                ans[i] = mp[nums1[i]];
        }
        return ans;
    }
};
Delete middle element of a stack   
 void solve(stack<int>&s, int count, int size){
        if(count == size/2){
            s.pop();
            return;
        }
        int num = s.top();
        s.pop();
        solve(s,count+1,size);
        s.push(num);
    }
    void deleteMid(stack<int>&s, int size)
    {
        solve(s,0,size);
    }
// TC - O(N)
// SC - O(1)
-------------------------------------------------------------------------------------------------------------------------
Insert An Element At Its Bottom In A Given Stack
void solve(stack<int>&s, int x){
    if(s.size() == 0){
        s.push(x);
        return;
    }
    int num = s.top();
    s.pop();
    solve(s,x);
    s.push(num);
}
stack<int> pushAtBottom(stack<int>&s, int x) 
{
    solve(s,x);
    return s;
}
// TC - O(N)
// SC - O(1)
-------------------------------------------------------------------------------------------------------------------------
Reverse Stack Using Recursion
void insertAtBottom(stack<int>&s, int num){
    if(s.size() == 0 ){
        s.push(num);
        return;
    }
    int x = s.top();
    s.pop();
    insertAtBottom(s,num);
    s.push(x);
}
void reverseStack(stack<int> &s) {
    if(s.size()==0){
        return;
    }
    int num = s.top();
    s.pop();
    reverseStack(s);
    insertAtBottom(s,num);
}
// TC - O(N^2)
// SC - O(1)
-------------------------------------------------------------------------------------------------------------------------
Sort a Stack
void sortt(stack<int>&s, int num){
	if(s.size() == 0 || s.top()<num){
		s.push(num);
		return;
	}
	int x  = s.top();
	s.pop();
	sortt(s,num);
	s.push(x);
}
void sortStack(stack<int> &s)
{
	if(s.size() == 0){
		return;
	}
    int num = s.top();
	s.pop();
	sortStack(s);
	sortt(s,num);
}
// TC - O(N^2)
// SC - O(1)
-------------------------------------------------------------------------------------------------------------------------
Redundant Brackets
https://www.codingninjas.com/codestudio/problems/redundant-brackets_975473?leftPanelTab=0
bool findRedundantBrackets(string &s)
{
    stack<char>st;
    int n = s.size();
    for(int i=0; i<n; i++){
        if(s[i] == '(' || s[i] == '+' || s[i] == '-' || s[i] == '/' || s[i] == '*'){
            st.push(s[i]);
        }
        else{
            if(s[i] == ')'){
            bool rebundant = true;
            while(st.top() != '('){
                if(st.top() == '+' || st.top() == '-' || st.top() == '/' || st.top() == '*'){
                    rebundant = false;
                }
                st.pop();
            }
            if(rebundant){
                return true;
            }
            st.pop();
            }
            
        }
       
    }
     return false;
}
        // TC - O(2*N)
        // SC - O(N)
-------------------------------------------------------------------------------------------------------------------------
Minimum Cost To Make String Valid
https://www.codingninjas.com/codestudio/problems/minimum-cost-to-make-string-valid_1115770?leftPanelTab=0
int findMinimumCost(string &s) {
   int n = s.size();
   if(n%2){
     return -1;
   }
   stack<char>st;
   for(int i=0; i<n; i++){
      if(s[i] == '{'){
        st.push(s[i]);
      }
      else{
        if(!st.empty() && st.top()=='{'){
          st.pop();
        }
        else{
          st.push(s[i]);
        }
      }
   }
   int a = 0, b = 0;
   while(!st.empty()){
     if(st.top()=='{'){
       b++;
     }
     else{
       a++;
     }
     st.pop();
   }
   return (a+1)/2 + (b+1)/2;
}
-------------------------------------------------------------------------------------------------------------------------
Next Greater Element
https://practice.geeksforgeeks.org/problems/next-larger-element-1587115620/1?utm_source=gfg&utm_medium=article&utm_campaign=bottom_sticky_on_article
    vector<long long> nextLargerElement(vector<long long> arr, int n){
        stack<long long>st;
        vector<long long> ans(n);
        for(int i=n-1; i>=0; i--){
            if(st.empty()){
                st.push(arr[i]);
                ans[i]=-1;
            }
            else{
                while(!st.empty() && st.top()<=arr[i]){
                    st.pop();
                }
                if(st.empty()){
                    ans[i]=-1;
                }
                else{
                    ans[i] = st.top();
                }
                st.push(arr[i]);
            }
        }
        return ans;
    }
    // TC - O(2*N)
    // SC - O(N)
-------------------------------------------------------------------------------------------------------------------------
Next Greater Element I
https://leetcode.com/problems/next-greater-element-i/description/
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        stack<int>st;
        vector<int> ans(n);
        for(int i=n-1; i>=0; i--){
            if(st.empty()){
                st.push(nums2[i]);
                ans[i]=-1;
            }
            else{
                while(!st.empty() && st.top()<=nums2[i]){
                    st.pop();
                }
                if(st.empty()){
                    ans[i]=-1;
                }
                else{
                    ans[i] = st.top();
                }
                st.push(nums2[i]);
            }
        } 
        map<int, int>mp;
        for(int i=0; i<n; i++){
            mp[nums2[i]] = ans[i];
        }
        vector<int>res(m);
        for(int i=0; i<m; i++){
            res[i] = mp[nums1[i]];
        }
        return res;
    }
    // TC - O(2*N)
    // SC - O(N)
-------------------------------------------------------------------------------------------------------------------------
Next Greater Element II
https://leetcode.com/problems/next-greater-element-ii/description/
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        stack<int>st;
        vector<int> ans(n);
        for(int i=2*n-1; i>=0; i--){
                while(!st.empty() && st.top()<=nums[i%n]){
                    st.pop();
                }
                if(i<n){
                if(st.empty()){
                    ans[i]=-1;
                }
                else{
                    ans[i] = st.top();
                }
                }
                st.push(nums[i%n]);
        } 
        return ans;
    }
    // TC - O(2*N)
    // SC - O(N)
-------------------------------------------------------------------------------------------------------------------------
Next Smallest Element   
 vector<int> help_classmate(vector<int> arr, int n) 
    { 
        stack<int>st;
        vector<int> ans(n);
        for(int i=n-1; i>=0; i--){
            if(st.empty()){
                st.push(arr[i]);
                ans[i]=-1;
            }
            else{
                while(!st.empty() && st.top()>=arr[i]){// just change < sign to > sign from NGE
                    st.pop();
                }
                if(st.empty()){
                    ans[i]=-1;
                }
                else{
                    ans[i] = st.top();
                }
                st.push(arr[i]);
            }
        }
        return ans;
    } 
-------------------------------------------------------------------------------------------------------------------------
Online Stock Span
https://leetcode.com/problems/online-stock-span/description/
    stack<pair<int,int>>st;    
    int next(int price) {
            int ans = 1;
            while(st.size() && st.top().first<=price){
                ans += st.top().second;
                st.pop();
            }
            st.push({price,ans});
            return ans;
    }
    // TC - O(2*N)
    // SC - O(N)
-------------------------------------------------------------------------------------------------------------------------
https://leetcode.com/problems/largest-rectangle-in-histogram/description/
Largest Rectangle in Histogram
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        int leftsmall[n],rightsmall[n];
        stack<int>st;
        for(int i=0; i<n; i++){
            while(!st.empty() && heights[st.top()]>=heights[i]){
                st.pop();
            }
            if(st.empty()){
                leftsmall[i] = 0;
            }
            else{
                leftsmall[i] = st.top()+1;
            }
            st.push(i);
        }
        while(st.size()){
            st.pop();
        }
        for(int i=n-1; i>=0; i--){
            while(!st.empty() && heights[st.top()]>=heights[i]){
                st.pop();
            }
            if(st.empty()){
                rightsmall[i] = n-1;
            }
            else{
                rightsmall[i] = st.top()-1;
            }
            st.push(i);
        }
        int maxA = 0;
        for(int i=0; i<n; i++){
            maxA = max(maxA,(rightsmall[i]-leftsmall[i]+1)*heights[i]);
        }
        return maxA;
    }
    // TC - O(2*N)
    // SC - O(N)
-------------------------------------------------------------------------------------------------------------------------
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        stack<int>st;
        int maxA = 0;
        for(int i=0; i<=n; i++){
            while(!st.empty() && (i==n || heights[st.top()]>=heights[i])){
               int height = heights[st.top()];
            st.pop();
            int width;
            if(st.empty()){
                width = i;
            }
            else{
                width = i - st.top() - 1;
            }
            maxA = max(maxA,width*height);
            }
            st.push(i);
        }
        return maxA;
    }
    // TC - O(2*N)
    // SC - O(N)
-------------------------------------------------------------------------------------------------------------------------
Maximal Rectangle
https://leetcode.com/problems/maximal-rectangle/description/
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        int leftsmall[n],rightsmall[n];
        stack<int>st;
        for(int i=0; i<n; i++){
            while(!st.empty() && heights[st.top()]>=heights[i]){
                st.pop();
            }
            if(st.empty()){
                leftsmall[i] = 0;
            }
            else{
                leftsmall[i] = st.top()+1;
            }
            st.push(i);
        }
        while(st.size()){
            st.pop();
        }
        for(int i=n-1; i>=0; i--){
            while(!st.empty() && heights[st.top()]>=heights[i]){
                st.pop();
            }
            if(st.empty()){
                rightsmall[i] = n-1;
            }
            else{
                rightsmall[i] = st.top()-1;
            }
            st.push(i);
        }
        // for(int i=0; i<n; i++){
        //     cout<<leftsmall[i]<<" ";
        // }
        // cout<<endl;
        // for(int i=0; i<n; i++){
        //     cout<<rightsmall[i]<<" ";
        // }
        // cout<<endl;
        int maxA = 0;
        for(int i=0; i<n; i++){
            maxA = max(maxA,(rightsmall[i]-leftsmall[i]+1)*heights[i]);
        }
        return maxA;
    }
    int maximalRectangle(vector<vector<char>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        int maxA = 0;
        vector<int>heights(m,0);
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(i==0){
                    if(matrix[i][j]=='1'){
                        heights[j] = 1;
                    }
                }
                    else{
                        if(matrix[i][j]=='1'){
                            heights[j]++;
                        }
                        else{
                            heights[j] = 0;
                        }
                    }
            }
             maxA = max(maxA,largestRectangleArea(heights));
        }
        return maxA;
    }
    // TC - O(N*M)
    // SC - O(N)
-------------------------------------------------------------------------------------------------------------------------
https://practice.geeksforgeeks.org/problems/the-celebrity-problem/1?utm_source=gfg&utm_medium=article&utm_campaign=bottom_sticky_on_article
The Celebrity Problem
    int celebrity(vector<vector<int> >& m, int n) 
    {
        stack<int>st;
        // push all elements into stack
        for(int i=0; i<n; i++){
            st.push(i);
        }
        // get 2 elements and compare them
        while(st.size()>1){
            int a = st.top();
            st.pop();
            int b = st.top();
            st.pop();
            if(m[a][b]==1){
                st.push(b);
            }
            else{
                st.push(a);
            }
        }
        int cel = st.top();
        int ct = 0;
        // col check
        for(int i=0; i<n; i++){
            if(m[cel][i]==0){
                ct++;
            }
        }
        if(ct != n){
            return -1;
        }
        ct = 0;
        // row check
        for(int i=0; i<n; i++){
            if(m[i][cel]==1){
                ct++;
            }
        }
        if(ct != n-1){
            return -1;
        }
        return cel;
    }
    // TC - O(N)
    // SC - O(N)
-------------------------------------------------------------------------------------------------------------------------
https://leetcode.com/problems/longest-valid-parentheses/description/
Longest Valid Parentheses
    int longestValidParentheses(string s) {
        int n = s.size();
        stack<int>st;
        int ans = 0;
        st.push(-1);
        for(int i=0; i<n; i++){
            int t = st.top();
            if(t!=-1 && s[t]=='(' && s[i]==')'){
                st.pop();
                ans = max(ans,i-st.top());
            }
            else{
                st.push(i);
            }
        }
        return ans;
    }
// TC - O(N)
// SC - O(N)
-------------------------------------------------------------------------------------------------------------------------
Evaluation of Postfix Expression
https://practice.geeksforgeeks.org/problems/evaluation-of-postfix-expression1735/1
    int evaluatePostfix(string s)
    {
        stack<int>st;
        int n = s.size();
        for(int i=0; i<n; i++){
            if(s[i]>='0' && s[i]<='9'){
                st.push(s[i]-'0');
            }
            else{
                int a = st.top();
                st.pop();
                int b = st.top();
                st.pop();
                if(s[i]=='+'){
                    st.push(b+a);
                }
                else if(s[i]=='-'){
                    st.push(b-a);
                }
                else if(s[i]=='*'){
                    st.push(b*a);
                }
                else{
                    st.push(b/a);
                }
            }
        }
        return st.top();
    }
-------------------------------------------------------------------------------------------------------------------------
https://practice.geeksforgeeks.org/problems/stack-permutations/1?utm_source=gfg&utm_medium=article&utm_campaign=bottom_sticky_on_article
Stack Permutations
    int isStackPermutation(int n,vector<int> &a,vector<int> &b){
        stack<int>st;
        int j=0;
        for(int i=0; i<n; i++){
            st.push(a[i]);
            while(!st.empty() && st.top()==b[j]){
                j++;
                st.pop();
            }
        }
        if(st.empty()){
            return true;
        }
        return false;
    }
-------------------------------------------------------------------------------------------------------------------------
https://leetcode.com/problems/trapping-rain-water/description/
Trapping Rain Water
    int trap(vector<int>& height) {
        int n = height.size();
        int maxL[n],maxR[n];
        maxL[0] = height[0];
        for(int i=1; i<n; i++){
            maxL[i] = max(maxL[i-1],height[i]);
        }
        maxR[n-1] = height[n-1];
        for(int i=n-2; i>=0; i--){
            maxR[i] = max(maxR[i+1],height[i]);
        }
        int ans=0;
        for(int i=0; i<n; i++){
            ans += (min(maxL[i],maxR[i])-height[i]);
        }     
        return ans;   
    }
-------------------------------------------------------------------------------------------------------------------------