#pragma once
class Queue
{
public:
	Queue();
	void Pop();
	void Push(int data);
	bool IsEmpty();
	bool IsFull();
	void Clear();
	int Size();
	~Queue();
private:
	int SIZE = 5;
	int size = 0;
	int queue[5] = {0};
	int front = -1;
	int rear = -1;
};

