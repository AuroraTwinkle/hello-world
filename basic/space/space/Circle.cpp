#include "Circle.h"



Circle::Circle()
{
}


Circle::~Circle()
{
}

Circle::Circle(double x, double y, double r):Point(x,y)
{
	this->r = r;
}

void Circle::setR(double r)
{
	this->r = r;
}

double Circle::getR()
{
	return this->r;
}
