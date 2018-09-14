#include "Rect.h"



Rect::Rect()
{
}


Rect::~Rect()
{
}

Rect::Rect(double x, double y, double x_max, double y_max) :Point(x, y) {
	this->x_max = x_max;
	this->y_max = y_max;
}

void Rect::setX_max(double x)
{
	this->x_max = x;
}

double Rect::getX_max()
{
	return this->x_max;
}

void Rect::setY_max(double y)
{
	this->y_max = y;
}

double Rect::getY_max()
{
	return this->y_max;
}

