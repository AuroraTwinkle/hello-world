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
	int capacity;//画布容量
	int cursor;//游标，用来指示目前画布上有多少个图形
};

