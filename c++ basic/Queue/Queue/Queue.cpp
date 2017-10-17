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
        rear += 1;
        queue[rear] = data;
    }

}

void Queue::Pop()
{
    if(!IsEmpty())
    {
        front++;
        cout<<queue[front];
    }
}