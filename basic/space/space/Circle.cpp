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

Circle::Circle(int x, int y, int r):Point(x,y)
{
    this->r = r;
    std::cout<<"add "<<countCircle<<"th "<<"circle:"<<"("<<this->x_origin<<","<<this->y_origin<<","<<this->r<<")"<<std::endl;
    countCircle++;
}

void Circle::setR(int r)
{
    this->r = r;
}

int Circle::getR()
{
    return this->r;
}