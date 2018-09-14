#pragma once
#include "Point.h"
class Rect :
	public Point
{
public:
	Rect();
	~Rect();
	Rect(double x, double y, double x_max, double y_max);
	//get和set方法
	void setX_max(double x);
	double getX_max();
	void setY_max(double y);
	double getY_max();
private:
	double x_max;//矩形右下方x坐标
	double y_max;//矩形右下方y坐标
};

