#include <iostream>
#include "Stack.h"
using namespace std;

int main()
{
    Stack stack;
    stack.PushStack(456);
	stack.PushStack(46);
	stack.PushStack(453);
	stack.PushStack(4565);
	stack.PushStack(45656);
    stack.GetTop();
    stack.ShowStack();
    system("pause");
    return 0;
}