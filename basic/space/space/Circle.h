#pragma once
#include "Point.h"
class Circle :
	public Point
{
public:
	Circle();
	~Circle();
	Circle(double x, double y, double r);
	//get��set����
	void setR(double r);
	double getR();
private:
	double r;//Բ�İ뾶
};

