//
// Created by Aurora on 2018/9/14.
//

#include "Point.h"

Point::Point()
{
}


Point::~Point()
{
}

Point::Point(int x, int y)
{
    this->x_origin = x;
    this->y_origin = y;
}

void Point::setX_origin(int x)
{
    this->x_origin = x;
}

int Point::getX_origin()
{
    return this->x_origin;
}

void Point::setY_origin(int y)
{
    this->y_origin = y;
}

int Point::getY_origin()
{
    return this->y_origin;
}

bool Point::operator==(const Point & pt)
{
	return this->x_origin==pt.x_origin && this->y_origin==pt.y_origin;
}


