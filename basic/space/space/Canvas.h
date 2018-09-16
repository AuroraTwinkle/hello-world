//
// Created by Aurora on 2018/9/14.
//

#ifndef SPACE_CANVAS_H
#define SPACE_CANVAS_H


#include "Point.h"
#include "Circle.h"
#include "Rect.h"
#include <random>
#include <ctime>
#include <set>
#include <vector>


class Canvas
{
public:
    Canvas();
    ~Canvas();
    static std::default_random_engine random;//随机数引擎
	double distanceBtwPoints(Point pt, Point pt1);//计算两个点之间的距离
	Point findCenterInWhichSubRect(Circle &circle);//计算出圆心位于哪个子区域
	Rect addRect(int x_origin, int y_origin, int x_max, int y_max);//添加一个矩形区域
	void addToObstacleSet(std::set<Point> &setPoint,Rect *rect, std::vector<Point> eigthSubRectss, Circle circle, std::vector<double> distance);//将被障碍物占领的子区域加入集合
	bool isInRect(Rect *rect, Point pointRect);//判断一个子区域是否是合法区域
	std::set<Point> findSubRectHasObstacle(Rect *rect, std::vector<Circle> &vectorCircle);//寻找被障碍物（圆形）占领的子区域
	std::vector<Point> eightSubRectsByOnePoint(Point *pointRect);//由一个子区域起始点的坐标计算出其周围八个子区域起始坐标
	std::vector<Point> fourVertexOfRect(Point *pointRect);//传入矩形左上方顶点坐标计算出四个顶点的坐标存入vector返回
    std::vector<Circle> addCircle(Rect *rect, int count);//添加count个圆
    std::vector<Point> cutRectByScalar(Rect *rect, int xScalar, int yScalar);//分割矩形区域
	std::vector<Point> circleBySubRect(int index, Point * pointRect, std::vector<double> &distance, Circle &circle);//圆经过的区域
	std::vector<double> distCenterToVertex(Point *point, Circle &circle);//计算圆心到子区域四个顶点的距离
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
