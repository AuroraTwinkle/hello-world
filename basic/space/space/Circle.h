//
// Created by Aurora on 2018/9/14.
//

#ifndef SPACE_CIRCLE_H
#define SPACE_CIRCLE_H


#include "Point.h"

class Circle :
        public Point
{
public:
    Circle();
    ~Circle();
    Circle(int x, int y, int r);
    static int countCircle;//用来指示创建了多少个圆
    //get和set方法
    void setR(int r);
    int getR();
private:
    int r;//半径
};

#endif //SPACE_CIRCLE_H
