//
// Created by Aurora on 2018/9/14.
//

#include "Rect.h"

int Rect::countRect=1;

Rect::Rect()
{
}


Rect::~Rect()
{
}

Rect::Rect(double x_origin, double y_origin, double x_max, double y_max) :Point(x_origin, y_origin) {
    this->x_max = x_max;
    this->y_max = y_max;
    std::cout<<"add a rect:"<<"("<<this->x_origin<<","<<this->y_origin<<","<<this->x_max<<","<<this->y_max<<")"<<std::endl;
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