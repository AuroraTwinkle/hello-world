#include "Canvas.h"



Canvas::Canvas(int capacity)
{
	this->capacity = capacity;
	this->cursor = 1;
	if (capacity > 0) {
		this->point =new Point * [capacity];
	}
}


Canvas::~Canvas()
{
	//�ͷ��ڴ�
	for (int i = 0; i < this->capacity; i++) {
		delete[] point[i];
	}
	delete[] point;
}
