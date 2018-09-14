//
// Created by Aurora on 2018/9/14.
//

#ifndef SPACE_CANVAS_H
#define SPACE_CANVAS_H

#include <vector>
#include "Point.h"
#include "Circle.h"
#include "Rect.h"
#include <random>
#include <ctime>


class Canvas
{
public:
    Canvas();
    ~Canvas();
    static std::default_random_engine random;
    std::vector<Circle> addCircle(Rect *rect, int count);//添加count个圆
    Rect addRect(double x_origin, double y_origin, double x_max, double y_max);//添加一个矩形区域
    std::vector<Point> cutRectByScalar(Rect *rect, double x, double y);//分割矩形区域
private:

};


#endif //SPACE_CANVAS_H
