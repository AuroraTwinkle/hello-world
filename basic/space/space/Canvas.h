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
    Rect addRect(double x_origin, double y_origin, double x_max, double y_max);//添加一个矩形区域
    std::vector<Point> cutRectByScalar(Rect *rect, double xScalar, double yScalar);//分割矩形区域
	std::set<Point> findSubRectHasObstacle(Rect *rect, std::vector<Circle> vectorCircle);//寻找被障碍物（圆形）占领的子区域
	Point findCenterInWhichSubRect(Circle circle);//计算出圆心位于哪个子区域

	//set and get method
	void setXscalar(double xScalar);
	double getXscalar();
	void setYscalar(double yScalar);
	double getYscalar();
private:
	double xScalar;//x方向标尺的长度
	double yScalar;//y方向标尺的长度

};


#endif //SPACE_CANVAS_H
