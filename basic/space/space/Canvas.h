#pragma once
#include "Point.h"
class Canvas
{
public:
	Canvas(int capacity);
	~Canvas();
	void add(Point * point);
private:
	Point ** point;
	int capacity;//��������
	int cursor;//�α꣬����ָʾĿǰ�������ж��ٸ�ͼ��
};

