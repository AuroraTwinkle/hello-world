#pragma once
class Queue
{
public:
	Queue();
	void Pop();
	void Push(int data);
	bool IsEmpty();
	bool IsFull();
	void Destory();
	void Clear();
	int Size();
	~Queue();
private:
	int queue[100] = {0};
	int front = -1;
	int rear = -1;
};

