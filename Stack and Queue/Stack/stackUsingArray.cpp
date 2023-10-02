#include <bits/stdc++.h>
using namespace std;

class MyStack
{
private:
    // to access array in heap memory
    int *arr;
    int top;
    int size;

public:
    MyStack(int size)
    {
        this->size = size;
        // created in heap memory
        arr = new int[size];
        top = -1;
    }
    int pop();
    void push(int);
    int topEle();
    bool empty();
};

// Function to push an integer into the stack.
void MyStack ::push(int x)
{
    if (top == size - 1)
    {
        cout << "Stack is full, " << x << " "
             << "can't be pushed\n";
        return;
    }
    top++;
    arr[top] = x;
}

// Function to remove an item from top of the stack.
int MyStack ::pop()
{
    if (top == -1)
    {
        cout << "Stack is empty\n";
        return -1;
    }
    int ele = arr[top];
    top--;
    return ele;
}

int MyStack::topEle()
{
    if (top == -1)
    {
        cout << "Stack is empty\n";
        return -1;
    }
    return arr[top];
}

bool MyStack ::empty()
{
    return top == -1;
}

int main()
{
    MyStack s(3);
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    while (!s.empty())
    {
        cout << s.topEle() << " ";
        s.pop();
    }
}