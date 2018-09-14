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

Rect::Rect(int x_origin, int y_origin, int x_max, int y_max) :Point(x_origin, y_origin) {
    this->x_max = x_max;
    this->y_max = y_max;
    std::cout<<"add a rect:"<<"("<<this->x_origin<<","<<this->y_origin<<","<<this->x_max<<","<<this->y_max<<")"<<std::endl;
}

void Rect::setX_max(int x)
{
    this->x_max = x;
}

int Rect::getX_max()
{
    return this->x_max;
}

void Rect::setY_max(int y)
{
    this->y_max = y;
}

int Rect::getY_max()
{
    return this->y_max;
}