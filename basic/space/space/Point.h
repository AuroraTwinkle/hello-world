#pragma once
class Point
{
public:
	Point();
	~Point();
	Point(double x, double y);
	//get和set方法
	void setX_origin(double x);
	double getX_origin();
	void setY_origin(double y);
	double getY_origin();
protected:
	double x_origin;//x坐标
	double y_origin;//y坐标
};

