#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int data;
    Node *next;
    Node(int data)
    {
        this->data = data;
        this->next = NULL;
    }
};

class Stack
{
public:
    Node *top;
    int size;
    Stack()
    {
        size = 0;
        top = NULL;
    }
    void push(int x);
    void pop();
    int peek();
    int Size();
};

void Stack::push(int x)
{
    // create a node
    Node *node = new Node(x);
    // if node was not created that means heap memory is full
    if (!node)
    {
        cout << "Stack overflow\n";
        return;
    }

    // we can now push element at front of LL
    // if stack/LL is empty
    if (top == NULL)
        top = node;
    else
    {
        // LL has some node, so insert new node at head/top
        node->next = top;
        top = node;
    }
    size++;
}

void Stack::pop()
{
    if (top == NULL)
    {
        cout << "Stack Underflow\n";
        return;
    }

    Node *nodeToDelete = top;
    // to delete, move head/top ahead
    top = top->next;
    delete nodeToDelete;
    size--;
}

int Stack::peek()
{
    if (top == NULL)
    {
        cout << "No elements in stack\n";
        return -1;
    }
    return top->data;
}

int Stack:: Size(){
    return size;
}

int main()
{
    Stack s;
    s.push(1);
    s.push(2);
    cout << s.peek() << "\n";
    s.pop();
    cout << s.peek() << "\n";
    cout<<s.Size()<<"\n";
}