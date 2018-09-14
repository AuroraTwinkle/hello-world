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
#include <set>


class Canvas
{
public:
    Canvas();
    ~Canvas();
    static std::default_random_engine random;//随机数引擎
    std::vector<Circle> addCircle(Rect *rect, int count);//添加count个圆
    Rect addRect(int x_origin, int y_origin, int x_max, int y_max);//添加一个矩形区域
    std::vector<Point> cutRectByScalar(Rect *rect, int xScalar, int yScalar);//分割矩形区域
	std::set<Point> findSubRectHasObstacle(Rect *rect, std::vector<Circle> vectorCircle);//寻找被障碍物（圆形）占领的子区域
	Point findCenterInWhichSubRect(Circle circle);//计算出圆心位于哪个子区域
	std::vector<int> distCenterToVertex(Point *point, Circle *circle);//计算圆心到子区域四个顶点的距离
	//set and get method
	void setXscalar(int xScalar);
	int getXscalar();
	void setYscalar(int yScalar);
	int getYscalar();
private:
	int xScalar;//x方向标尺的长度
	int yScalar;//y方向标尺的长度

};


#endif //SPACE_CANVAS_H
