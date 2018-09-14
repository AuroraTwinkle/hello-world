#include "Point.h"



Point::Point()
{
}


Point::~Point()
{
}

Point::Point(double x, double y)
{
	this->x_origin = x;
	this->y_origin = y;
}

void Point::setX_origin(double x)
{
	this->x_origin = x;
}

double Point::getX_origin()
{
	return this->x_origin;
}

void Point::setY_origin(double y)
{
	this->y_origin = y;
}

double Point::getY_origin()
{
	return this->y_origin;
}
