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