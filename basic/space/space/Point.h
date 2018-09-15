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
	int x_origin;//x坐标
	int y_origin;//y坐标
	bool operator==(const Point& pt); //重载==操作符
	bool operator<(const Point& pt)const;//重载<操作符
protected:
    

};


#endif //SPACE_POINT_H
