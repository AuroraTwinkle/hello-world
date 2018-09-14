#pragma once
#include "Point.h"
class Circle :
	public Point
{
public:
	Circle();
	~Circle();
	Circle(double x, double y, double r);
	//get和set方法
	void setR(double r);
	double getR();
private:
	double r;//圆的半径
};

