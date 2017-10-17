#include "Queue.h"
#include <iostream>
using namespace std;


Queue::Queue()
{
}


Queue::~Queue()
{
}

void Queue::Push(int data)
{
    if(!IsFull())
    {
        rear = (rear+1) % SIZE;
        queue[rear] = data;
    }
    else
    {
        cout<<"It's full";
    }

}

void Queue::Pop()
{
    if(!IsEmpty())
    {
        front = (front+1) % SIZE;
        cout<<queue[front];
    }
    else
    {
        cout<<"It's empty";
    }
}

bool Queue::IsEmpty()
{
    return front == rear;
}

bool Queue::IsFull()
{
    return (rear+1) % SIZE == front;
}

int Queue::Size()
{
    return (rear-front)%SIZE;
}

void Queue::Clear()
{
    rear = front;
}