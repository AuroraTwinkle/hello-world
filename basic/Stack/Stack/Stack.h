#pragma once
const int SIZE = 5;
class Stack
{
public:
	Stack();
	bool PopStack();
	bool PushStack(int data);
	bool IsFull();
	bool IsEmpty();
	void GetTop();
	void ClearStack();
	void ShowStack();
	~Stack();
private:
	int top;
	int stack[SIZE];
};

