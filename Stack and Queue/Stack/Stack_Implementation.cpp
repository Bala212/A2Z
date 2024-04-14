Q. Implement Stack using Arrays
#include<bits/stdc++.h>
using namespace std;

class Stack{
    public:
    int *arr;
    int Top;
    Stack(){
        int size = 1000;
        arr = new int[size];
        Top = -1;
    }
    void push(int val){
        Top++;
        arr[Top] = val;
    }
    int top(){
        if(Top == -1){
            cout<<"Stack is empty"<<endl;
            return -1;
        }
        else{
        return arr[Top];
        }
    }
    void pop(){
        if(Top == -1){
            cout<<"Stack is empty"<<endl;
            return;
        }
        Top--;
    }
    int size(){
        return Top+1;
    }
    bool isEmpty(){
        if(Top==-1){
            return true;
        }
        else{
            return false;
        }
    }
};
int main(){
    Stack s;
    // cout<<s.top()<<endl;
    // s.pop();
    s.push(4);
    s.push(5);
    s.push(6);
    while(s.size()>0){
        cout<<s.top()<<endl;
        s.pop();
    }
    cout<<endl;
}

// Advantage
Easy to implement.
Memory is saved as pointers are not involved.
// disadvantage
It is not dynamic i.e., it doesn’t grow and shrink depending on needs at runtime. [But in case of dynamic sized arrays like vector in C++, list in Python, ArrayList in Java, stacks can grow and shrink with array implementation as well].
The total size of the stack must be defined beforehand.

-------------------------------------------------------------------------------------------------------------------------
Stack using Linked List
#include<bits/stdc++.h>
using namespace std;

struct StackNode{
    int data;
    StackNode *next;
    StackNode(int d){
        data = d;
        next = NULL;
    }
};

class Stack{
    public:
    StackNode *Top;
    int size;
    Stack(){
        int size = 0;
        Top = NULL;
    }
    void push(int val){
        StackNode* element = new StackNode(val);
        element->next = Top;
        Top = element;
        size++;
    }
    int top(){
        if(Top == NULL){
            cout<<"Stack is empty"<<endl;
            return -1;
        }
        else{
        return Top->data;
        }
    }
    void pop(){
        if(Top == NULL){
            cout<<"Stack is empty"<<endl;
            return;
        }
        StackNode *temp = Top;
        Top = Top->next;
        delete temp;
        size--;
    }
    int Size(){
        return size;
    }
    bool isEmpty(){
        if(Top==NULL){
            return true;
        }
        else{
            return false;
        }
    }
    void print(){
        StackNode *current = Top;
        while(current != NULL){
            cout<<current->data<<" ";
            current = current->next;
        }
        cout<<endl;
    }
};
int main(){
    Stack s;
    // cout<<s.top()<<endl;
    // s.pop();
    s.push(4);
    s.push(5);
    s.push(6);
    s.print();
    s.pop();
    s.print();
}
Advantages:
The linked list implementation of a stack can grow and shrink according to the needs at runtime.
Disadvantages:
Requires extra memory due to the involvement of pointers.

QUEUE:
A Queue is defined as a linear data structure that is open at both ends and the operations are performed in First In First Out (FIFO) order.

Queue using Array
#include<bits/stdc++.h>
using namespace std;
class Queue{
    public:
    int *arr;
    int cursize,rear,front,size;
    Queue(int size){
        cursize = 0;
        rear = 0;
        front = 0;
        this->size = size;
        arr = new int[size];
    }
    void push(int val){
        if(cursize == size){
            cout<<"Queue is Full"<<endl;
            return;
        }
        arr[rear%size] = val;
        rear++;
        cursize++;
    }
    int Front(){
        if(cursize == 0){
            cout<<"Queue is empty"<<endl;
            return -1;
        }
        return arr[front%size];
        
    }
    void pop(){
        if(cursize == 0){
            cout<<"Queue is empty"<<endl;
            return;
        }
        cursize--;
        arr[front%size] = -1;
        front++;
    }
    int Size(){
        return cursize;
    }
    bool isEmpty(){
        if(cursize==0){
            return true;
        }
        else{
            return false;
        }
    }
    void print(){
        for(int i = front; i<rear; i++){
            cout<<arr[i%size]<<" ";
        }
        cout<<endl;
    }
};
int main(){
    Queue q(3);
    q.Front();
    q.pop();
    q.push(4);
    q.push(5);
    cout<<q.Front()<<endl;
}
Advantage:
Easy to implement
Disadvantage:
Static Data Structure, fixed size.

Queue using LinkedList
#include<bits/stdc++.h>
using namespace std;
class QueueNode{
    public:
    int val;
    QueueNode *next;
    QueueNode(int data){
        val = data;
        next = NULL;
    }
};
class Queue{
    public:
    QueueNode* front, *rear;
    int size;
    Queue(){
        rear = NULL;
        front = NULL;
        size = 0;
    }
    void push(int val){
        QueueNode* temp = new QueueNode(val);
        if(front == NULL){
            front = temp;
            rear = temp;
        }
        else{
            rear->next = temp;
            rear = temp;
        }
        size++;
    }
    int Front(){
        if(front == NULL){
            cout<<"Queue is empty"<<endl;
            return -1;
        }
        return front->val;
        
    }
    void pop(){
        if(front == NULL){
            cout<<"Queue is empty"<<endl;
            return;
        }
        QueueNode* temp = front;
        front = front->next;
        delete temp;
        size--;
    }
    int Size(){
        return size;
    }
    bool isEmpty(){
        return front == NULL;
    }
    void print(){
       QueueNode* current = front;
       while(current != NULL){
           cout<<current->val<<" ";
           current = current->next;
       }
       cout<<endl;
    }
};
int main(){
    Queue q;
    q.Front();
    q.pop();
    q.push(4);
    q.push(5);
    cout<<q.Front()<<endl;
    q.print();
    q.pop();
    q.print();
    cout<<q.Front()<<endl;
    q.push(6);
    q.print();
    cout<<q.Size()<<endl;
    
}

-------------------------------------------------------------------------------------------------------------------------
Stack using 2 queues
// by making push operation costly
class MyStack {
public:
    queue<int>q1,q2;
    MyStack() {
        
    }
    
    void push(int x) {
        q2.push(x);
        while(!q1.empty()){
            q2.push(q1.front());
            q1.pop();
        }
        swap(q1,q2);
    }
    
    int pop() {
       int top = q1.front();
        q1.pop();
         return top;
    }
    
    int top() {
        return q1.front();
    }
    
    bool empty() {
        return q1.size()==0;
    }
    // TC - O(N)
    // SC - O(2*N)
};
// by making pop operation costly
One by one dequeue everything except the last element from q1 and enqueue to q2.
Dequeue the last item of q1, the dequeued item is the result, store it.
Swap the names of q1 and q2
Return the item stored in step 2.
    void pop()
    {
        if (q1.empty())
            return;
 
        // Leave one element in q1 and
        // push others in q2.
        while (q1.size() != 1) {
            q2.push(q1.front());
            q1.pop();
        }
 
        // Pop the only left element
        // from q1
        q1.pop();
 
        // swap the names of two queues
        queue<int> q = q1;
        q1 = q2;
        q2 = q;
    }
 
    void push(int x) { q1.push(x); }
-------------------------------------------------------------------------------------------------------------------------
Stack using 1 queue
class MyStack {
public:
    queue<int>q;
    MyStack() {
        
    }
    
    void push(int x) {
        q.push(x);
        for(int i=0; i<q.size()-1; i++){
            q.push(q.front());
            q.pop();
        }
    }
    
    int pop() {
       int top = q.front();
        q.pop();
         return top;
    }
    
    int top() {
        return q.front();
    }
    
    bool empty() {
        return q.size()==0;
    }
    // TC - O(N)
    // SC - O(N)
};
-------------------------------------------------------------------------------------------------------------------------
Queue using stacks
approach 1: 
   stack<int>st1,st2;
    MyQueue() {
        
    }
    
    void push(int x) {
        while(!st1.empty()){
            st2.push(st1.top());
            st1.pop();
        }
        st1.push(x);
        while(!st2.empty()){
            st1.push(st2.top());
            st2.pop();
        }
    }
    
    int pop() {
        int Top = st1.top();
        st1.pop();
        return Top;
    }
    
    int peek() {
        return st1.top();
    }
    
    bool empty() {
        return st1.empty();
    }
    // TC - push-O(N)
    // SC - O(2N)
approach 2:
    stack<int>st1,st2;
    MyQueue() {
        
    }
    
    void push(int x) {
       st1.push(x);
    }
    
    int pop() {
       if(st2.size()){
           int Top = st2.top();
           st2.pop();
           return Top;
       }
       else{
           while(!st1.empty()){
               st2.push(st1.top());
               st1.pop();
           }
           int Top = st2.top();
           st2.pop();
           return Top;
       }
    }
    
    int peek() {
        if(st2.size()){
           int Top = st2.top();
           return Top;
       }
       else{
           while(st1.size()){
               st2.push(st1.top());
               st1.pop();
           }
           return st2.top();
       }
    }
    
    bool empty() {
        return (st1.size()+st2.size())==0;
    }
    // TC - push-O(1)(amotized)
    // SC - O(2N)

approach 3: using only one stack
    stack<int>st;
    MyQueue() {
        
    }
    
    void push(int x) {
       PushHelper(x);
    }
    void PushHelper(int x){
        if(st.size() == 0){
            st.push(x);
            return;
        }
        int data = st.top();
        st.pop();
        PushHelper(x);
        st.push(data);
        return;
    }
    int pop() {
        int Top = st.top();
        st.pop();
        return Top;
    } 
    
    int peek() {
        return st.top();
    }
    
    bool empty() {
        return st.size()==0;
    }
    // TC - pop(O(N))
    // SC - O(N)
-------------------------------------------------------------------------------------------------------------------------
Design min stack
approach 1: using 2 stacks
    stack<ll>st1,st2;
    MinStack() {
    }
    
    void push(ll val) {
        if(st1.empty()){
            st1.push(val);
            st2.push(val);
        }
        else{
            st1.push(val);
            st2.push(min(val,st2.top()));
        }
    }
    
    void pop() {
        st1.pop();
        st2.pop();
    }
    
    int top() {
        return st1.top();
    }
    
    int getMin() {
        return st2.top();
    }
    // TC - O(1)
    // SC - O(2N)

approach2: using pair 
    stack<pair<ll,ll>>st;
    MinStack() {
    }
    
    void push(ll val) {
        if(st.empty()){
            st.push({val,val});
        }
        else{
            st.push({val,min(val,st.top().second)});
        }
    }
    
    void pop() {
        st.pop();
    }
    
    int top() {
        return st.top().first;
    }
    
    int getMin() {
        return st.top().second;
    }
    // TC - O(1)
    // SC - O(2N)
approach 3: using only one stack
    stack<ll>st;
    ll mini;
    MinStack() {
        mini = 1e10;
    }
    
    void push(ll val) {
        if(st.empty()){
            mini = val;
            st.push(val);
        }
        else{
            if(val >= mini){
                st.push(val);
            }
            else{
                st.push(2*val*1LL-mini);
                 mini = min(val,mini);
            }
        }
    }
    
    void pop() {
        ll Top = st.top();
        st.pop();
        if(Top < mini){
            mini = 2*mini - Top;
        }
    }
    
    int top() {
        if(st.top() < mini){
            return mini;
        }
        else{
            return st.top();
        }
    }
    
    int getMin() {
        return mini;
    }
    // TC - O(1)
    // SC - O(N)
    /* pop intution
      st.top() < mini
      modified < mini
      what we were pushing?
      val < mini (-3<-2)
      val - mini < 0
      val + val - mini < val
      2*val - mini < val
      modified < val
      what was that val that val was mini
      modified < val
      hence proved
      mini modification while poping intution
      mini = (2*mini-st.top())
      mini = (2*mini-(2*val-prev_min))
      mini = prev_min
    */
-------------------------------------------------------------------------------------------------------------------------
stack in two arrays
#include <bits/stdc++.h> 
using namespace std;
class TwoStack {

public:

    // Initialize TwoStack.
    int top1;
    int top2;
    int *arr;
    int size;
    TwoStack(int s) {
        // Write your code here.
        size = s;
        arr = new int[size];
        top1 = (size/2) + 1;
        top2 = size/2;
    }
    
    // Push in stack 1.
    void push1(int num) {
        if(top1 > 0){
            top1--;
            arr[top1] = num;
        }
        else{
            // cout<<"Stack Overflow"<<endl;
            return;
        }
    }

    // Push in stack 2.
    void push2(int num) {
         if(top2 < size - 1){
            top2++;
            arr[top2] = num;
        }
        else{
            // cout<<"Stack Overflow"<<endl;
            return;
        }
    }

    // Pop from stack 1 and return popped element.
    int pop1() {
        if(top1 <= (size/2)){
            int top = arr[top1];
            top1++;
            return top;
        }
        else{
            // cout<<"Stack Underflow"<<endl;
            return -1;
        }
    }
    

    // Pop from stack 2 and return popped element.
    int pop2() {
        if(top2 >= (size/2) +1 ){
            int top = arr[top2];
            top2--;
            return top;
        }
        else{
            // cout<<"Stack Underflow"<<endl;
            return -1;
        }
    }
};
--> 2nd approach
space utilization
#include <bits/stdc++.h> 
using namespace std;
class TwoStack {

public:

    // Initialize TwoStack.
    int top1;
    int top2;
    int *arr;
    int size;
    TwoStack(int s) {
        // Write your code here.
        size = s;
        arr = new int[size];
        top1 = -1;
        top2 = size;
    }
    
    // Push in stack 1.
    void push1(int num) {
        if(top2 - top1 > 1){
            top1++;
            arr[top1] = num;
        }
        else{
            // cout<<"Stack Overflow"<<endl;
            return;
        }
    }

    // Push in stack 2.
    void push2(int num) {
         if(top2 - top1 > 1){
            top2--;
            arr[top2] = num;
        }
        else{
            // cout<<"Stack Overflow"<<endl;
            return;
        }
    }

    // Pop from stack 1 and return popped element.
    int pop1() {
        if(top1 >= 0){
            int top = arr[top1];
            top1--;
            return top;
        }
        else{
            // cout<<"Stack Underflow"<<endl;
            return -1;
        }
    }
    

    // Pop from stack 2 and return popped element.
    int pop2() {
        if(top2 < size){
            int top = arr[top2];
            top2++;
            return top;
        }
        else{
            // cout<<"Stack Underflow"<<endl;
            return -1;
        }
    }
};
-------------------------------------------------------------------------------------------------------------------------
N stacks in an array
brute force : partition array into n/k parts
optimised:
#include <bits/stdc++.h> 
class NStack
{
    int *arr, *top, *next;
    int n, s, freespot;
public:
    // Initialize your data structure.
    NStack(int N, int S)
    {
        n = N;
        s = S;
        freespot = 0;
        arr = new int[s];
        top = new int[n];
        next = new int[s];
        for(int i=0; i<n; i++){
            top[i] = -1;
        }
        for(int i=0; i<s; i++){
            next[i] = i+1;
        }
        next[s-1] = -1;
    }

    // Pushes 'X' into the Mth stack. Returns true if it gets pushed into the stack, and false otherwise.
    bool push(int x, int m)
    {
        if(freespot == -1){
            return false;
        }
        else{
            // find index
            int index = freespot;
            // update freespot
            freespot = next[index];
            // insert element into array
            arr[index] = x;
            // update next
            next[index] = top[m-1];
            // update top
            top[m-1] = index;
            return true;
        }
    }

    // Pops top element from Mth Stack. Returns -1 if the stack is empty, otherwise returns the popped element.
    int pop(int m)
    {
        if(top[m-1]==-1){
            return -1;
        }
        else{
            int index = top[m-1];
            top[m-1] = next[index];
            next[index] = freespot;
            freespot = index;
            return arr[index];
        }
    }
    // TC - O(1)
    // SC - O(N+S)
};
-------------------------------------------------------------------------------------------------------------------------
