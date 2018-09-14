//
// Created by Aurora on 2018/9/14.
//

#ifndef SPACE_POINT_H
#define SPACE_POINT_H

#include <iostream>


class Point {
public:
    Point();
    ~Point();
    Point(int x, int y);
    //get和set方法
    void setX_origin(int x);
    int getX_origin();
    void setY_origin(int y);
    int getY_origin();
	bool operator <(Point point) const;//重载 < 操作符
protected:
    int x_origin;//x坐标
    int y_origin;//y坐标

};


#endif //SPACE_POINT_H
