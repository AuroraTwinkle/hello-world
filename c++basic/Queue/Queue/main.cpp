#include <iostream>
#include "Queue.h"
using namespace std;

int main()
{
	Queue queue;
	queue.Push(89);
	cout<<queue.Size()<<endl;
	queue.Pop();
	queue.Clear();
	system("Pause");
    return 0;
}