#include "Stack.h"
#include <iostream>
using namespace std;


Stack::Stack():top(-1)
{
}


Stack::~Stack()
{
}

bool Stack::PushStack(int data)
{
    if(top >= SIZE-1)
    {
        return false;
    }
    stack[++top] = data;
    return true;
}

bool Stack::PopStack()
{
    if(top <= -1)
    {
        return false;
    }
    top--;
    return true;
}

bool Stack::IsEmpty()
{
    return top == -1;
}

bool Stack::IsFull()
{
    return top == SIZE-1;
}

void Stack::GetTop()
{
    if(!IsEmpty())
    {
        cout<<stack[top]<<endl;
    }
}

void Stack::ClearStack()
{
    top = -1;
}

void Stack::ShowStack()
{
    for(int i=0;i<=top;i++)
    {
        cout<<stack[i]<<"\t";
        if(i % 10 == 0)
        {
            cout<<endl;
        }
    }
}