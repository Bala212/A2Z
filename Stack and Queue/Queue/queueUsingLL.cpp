#include <bits/stdc++.h>
using namespace std;
// We will push at end of LL using tail pointer
// Pop and front ele from head of LL, using front pointer
class QueueNode
{
public:
    int val;
    QueueNode *next;
    QueueNode(int data)
    {
        val = data;
        next = NULL;
    }
};

class Queue
{
public:
    QueueNode *front, *rear;
    int size;
    Queue()
    {
        rear = NULL;
        front = NULL;
        size = 0;
    }
    void push(int val)
    {
        QueueNode *temp = new QueueNode(val);
        // Node not created, heap is full
        if (!temp)
        {
            cout << "Overflow\n";
            return;
        }
        // If queue is empty, then
        // new node is front and rear both
        if (front == NULL)
        {
            front = temp;
            rear = temp;
        }
        // generally, insert at tail
        // Add the new node at
        // the end of queue and change rear
        else
        {
            rear->next = temp;
            rear = temp;
        }
        // increase size of Queue
        size++;
    }
    int Front()
    {
        // Queue is empty
        if (front == NULL)
        {
            cout << "Queue is empty" << endl;
            return -1;
        }
        // return data of front
        return front->val;
    }
    void pop()
    {
        if (front == NULL)
        {
            cout << "Queue is empty" << endl;
            return;
        }
        QueueNode *nodeToDelete = front;
        // move front
        front = front->next;

        // Delete popped node
        delete nodeToDelete;
        // as we pop, decrease the size of queue/LL
        size--;
    }
    int Size()
    {
        return size;
    }
    bool isEmpty()
    {
        // if front is empty, return true
        return front == NULL;
    }
    void print()
    {
        QueueNode *current = front;
        while (current != NULL)
        {
            cout << current->val << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main()
{
    Queue q;
    q.push(4);
    q.push(5);
    cout << q.Size() << endl;
    cout << q.Front() << endl;
    q.print();
    q.pop();
    q.print();
    cout << q.Front() << endl;
    q.push(6);
    q.print();
    cout << q.Size() << endl;
}