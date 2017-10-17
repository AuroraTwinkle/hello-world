#include <iostream>
#include "Stack.h"
using namespace std;

int main()
{
    Stack stack;
    stack.PushStack(456);
    stack.GetTop();
    stack.ShowStack();
    system("pause");
    return 0;
}