#include <bits/stdc++.h>
using namespace std;
class Queue
{
public:
    int *arr;
    // how many numbers are crrently in array/queue
    int cursize;
    int rear, front, size;

    Queue(int size)
    {
        cursize = 0;
        rear = 0;
        front = 0;
        this->size = size;
        arr = new int[size];
    }

    void push(int val)
    {
        // array/queue is full
        if (cursize == size)
        {
            cout << "Queue is Full" << endl;
            return;
        }
        // push x at front index, to avoid loss of unused space we do mod with n
        arr[rear % size] = val;
        // do rear++ for next push
        rear++;
        // increase number of elements as we push one element
        cursize++;
    }

    int Front()
    {
        if (cursize == 0)
        {
            cout << "Queue is empty" << endl;
            return -1;
        }
        // return the front index!!
        return arr[front % size];
    }

    void pop()
    {
        if (cursize == 0)
        {
            cout << "Queue is empty" << endl;
            return;
        }
        // store dummy value at front
        arr[front % size] = -1;
        // do front++, to move to next element in queue/array
        front ++;
        // decrease count of numbers as we pop the element
        cursize--;
    }

    int Size()
    {
        return cursize;
    }

    bool isEmpty()
    {
        return cursize == 0;
    }

    void print()
    {
        for (int i = front; i < rear; i++)
        {
            cout << arr[i % size] << " ";
        }
        cout << endl;
    }
};
int main()
{
    Queue q(3);
    q.Front();
    q.push(4);
    q.push(5);
    q.push(6);
    q.pop();
    q.push(7);
    q.pop();
    q.push(8);
    q.pop();
    cout << q.Front() << endl;
    /////////////
}