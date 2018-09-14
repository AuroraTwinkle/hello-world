//
// Created by Aurora on 2018/9/14.
//

#include "Circle.h"

int Circle::countCircle=1;

Circle::Circle()
{
}


Circle::~Circle()
{
}

Circle::Circle(double x, double y, double r):Point(x,y)
{
    this->r = r;
    std::cout<<"add "<<countCircle<<"th "<<"circle:"<<"("<<this->x_origin<<","<<this->y_origin<<","<<this->r<<")"<<std::endl;
    countCircle++;
}

void Circle::setR(double r)
{
    this->r = r;
}

double Circle::getR()
{
    return this->r;
}