#pragma once
class Point
{
public:
	Point();
	~Point();
	Point(double x, double y);
	//get��set����
	void setX_origin(double x);
	double getX_origin();
	void setY_origin(double y);
	double getY_origin();
protected:
	double x_origin;//x����
	double y_origin;//y����
};

