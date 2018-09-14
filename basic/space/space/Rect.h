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
    Rect(int x_origin, int y_origin, int x_max, int y_max);
    static int countRect;//指示添加的矩形的数量
    //get和set方法
    void setX_max(int x);
    int getX_max();
    void setY_max(int y);
    int getY_max();
private:
    int x_max;//矩形右下方x坐标
    int y_max;//矩形右下方y坐标
};


#endif //SPACE_RECT_H
