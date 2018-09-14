//
// Created by Aurora on 2018/9/14.
//

#ifndef SPACE_RECT_H
#define SPACE_RECT_H


#include "Point.h"
class Rect :
        public Point
{
public:
    Rect();
    ~Rect();
    Rect(double x_origin, double y_origin, double x_max, double y_max);
    static int countRect;//指示添加的矩形的数量
    //get和set方法
    void setX_max(double x);
    double getX_max();
    void setY_max(double y);
    double getY_max();
private:
    double x_max;//矩形右下方x坐标
    double y_max;//矩形右下方y坐标
};


#endif //SPACE_RECT_H
