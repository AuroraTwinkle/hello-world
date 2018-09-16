//
// Created by Aurora on 2018/9/14.
//

#include "Canvas.h"

std::default_random_engine Canvas::random(time(NULL));


Canvas::Canvas()
{
	this->xScalar = 10;
	this->yScalar = 10;

}


Canvas::~Canvas()
{

}


/*
计算两点之间的距离
*/
double Canvas::distanceBtwPoints(Point pt, Point pt1)
{
	return sqrt((pt.x_origin - pt1.x_origin)*(pt.x_origin - pt1.x_origin) + (pt.y_origin - pt1.y_origin)*(pt.y_origin - pt1.y_origin));

}

/*
生成count个圆并存入vector返回
*/
std::vector<Circle> Canvas:: addCircle(Rect *rect, int count){
    std::vector<Circle> vectorCircle;
    std::uniform_int_distribution<int> xRand(rect->getX_origin(), rect->getX_max()-1);
	std::uniform_int_distribution<int> yRand(rect->getY_origin(), rect->getY_max()-1);
	int minXYscalar = std::min(this->xScalar, this->yScalar);
	
    for(int i=0;i<count;i++){//随机生成随机大小的圆并放入vector
        int x = xRand(random);
        int y = yRand(random);
		int minXY = std::min(x, y);
		int rMin = std::min(minXY, minXYscalar);
		std::uniform_int_distribution<int> rRand(0, rMin);
        int r = rRand(random);
        Circle circle(x,y,r);
        vectorCircle.push_back(circle);
    }
    return vectorCircle;
}

Rect Canvas:: addRect(int x_origin, int y_origin, int x_max, int y_max){
    Rect rect(x_origin,y_origin,x_max,y_max);
    return rect;
}

void Canvas::addToObstacleSet(std::set<Point>& setPoint, Rect *rect, std::vector<Point> eigthSubRectss, Circle circle, std::vector<double> distance)
{
	if (circle.getR() <= xScalar && circle.getR() <= yScalar) {//圆小于分割标度的情况

		if ((circle.getX_origin() % xScalar) == 0 && (circle.getY_origin() % yScalar) == 0) {//圆心刚好在子区域起始点

			for (int i = 4; i < 8; i++) {//eigthSubRectss[4],[5],[6],[7]分别代表左上，右上，左下，右下子区域
				if (isInRect(rect, eigthSubRectss[i]))
				{
					setPoint.insert(eigthSubRectss[i]);
				}
			}			
		}

		else if (distance[0] == distance[1] == distance[2])//圆心到四个顶点的距离相同时
		{
			setPoint.insert(eigthSubRectss[8]);
		}

		else {
			std::vector<double> ::iterator minDistance = std::min_element(distance.begin(), distance.end());
			int index = minDistance - distance.begin();//获得距离最小值的下标，以确定圆心离哪个子区域最近，0代表左上，1代表右上，2代表左下，3代表右下
			std::vector<Point> pointRects = circleBySubRect(index, &eigthSubRectss[8], distance, circle);
			for (auto pointRec = pointRects.begin(); pointRec != pointRects.end(); pointRec++) {
				if (isInRect(rect, *pointRec))
				{
					setPoint.insert(*pointRec);
				}
			}
			setPoint.insert(eigthSubRectss[8]);
		}

	}
}

bool Canvas::isInRect(Rect *rect, Point pointRect)
{
	return pointRect.getX_origin() < rect->getX_max() && pointRect.getX_origin() > rect->getX_origin() && pointRect.getY_origin() < rect->getY_max() && pointRect.getY_origin() > rect->getY_origin();
}

/*
分割矩形区域
*/

std::vector<Point> Canvas:: cutRectByScalar(Rect *rect, int xScalar, int yScalar){
	this->setXscalar(xScalar);
	this->setYscalar(yScalar);
    std::vector<Point> vectorRect;
    int temp1 = rect->getX_max()-rect->getX_origin();//临时变量，存储矩形区域x方向的长度
    int temp2 = rect->getY_max()-rect->getY_origin();//临时变量，存储矩形区域y方向的长度
    int xTimes = temp1 / xScalar;//temp1是xScalar(分割矩形的x标度)的多少倍
    int xMod = temp1 % xScalar;//分割后矩形x方向上不足一个xScalar标度的剩余值
    int yTimes = temp2 / yScalar;//temp1是yScalar(分割矩形的y标度)的多少倍
    int yMod = temp2 % yScalar;//分割后矩形y方向上不足一个yScalar标度的剩余值
    if(xMod == 0 && yMod == 0){//情况一，刚好把矩形区域完全等分

        for(int i = 0; i < yTimes; i++){
            for(int j = 0; j < xTimes; j++){
                Point pointRect(j * xScalar, i * yScalar);
                vectorRect.push_back(pointRect);
            }

        }
    }

	std::cout << "the space that has been cut:" << std::endl;
	std::vector<Point>::iterator it;
	for (it = vectorRect.begin(); it != vectorRect.end(); it++) {//打印分割后的区域
		std::cout << "(" << (*it).getX_origin() << "," << (*it).getY_origin() << ")" << "\t";
	}
	std::cout << std::endl;

    return vectorRect;

}

/*
计算圆心到子区域四个顶点的距离
*/

std::vector<double> Canvas::distCenterToVertex(Point * point, Circle & circle)
{
	std::vector<double> distance;//存储距离
	std::vector<Point> fourVertexVector;//存储矩形四个顶点坐标

	fourVertexVector = fourVertexOfRect(point);//有四个点，依次是矩形左上方，右上方，左下方，右下方顶点坐标
	Point centerPoint(circle.getX_origin(), circle.getY_origin());//圆心坐标

	/*
	这样做的原因是，可以用distance[0]代表圆心到子区域左上方顶点的距离，
	distance[1]代表到子区域右上方的距离......以此类推，得到圆心到四个顶点的距离
	*/
	for (auto vertex = fourVertexVector.begin(); vertex != fourVertexVector.end(); vertex++) {
		double dist = distanceBtwPoints(centerPoint, *vertex);
		distance.push_back(dist);
	}

	return distance;
}

/*
寻找被障碍物（圆形）占领的子区域
*/

std::set<Point> Canvas::findSubRectHasObstacle(Rect * rect, std::vector<Circle> &vectorCircle)
{
	std::set<Point> setPoint;
	for (auto circle = vectorCircle.begin(); circle != vectorCircle.end(); circle++) {
		Point pointRect = findCenterInWhichSubRect(*circle);//圆心所在子区域
		std::vector<Point> eigthSubRectss = eightSubRectsByOnePoint(&pointRect);//算出八个子区域
		std::vector<double> distance = distCenterToVertex(&pointRect, *circle);//圆心到四个顶点的距离
		addToObstacleSet(setPoint, rect, eigthSubRectss, *circle, distance);//将被障碍物占领的区域加入集合

	}
	std::cout << "the subRect that has been obstacle:" << std::endl;
	for (auto subRectHasObstacle = setPoint.begin(); subRectHasObstacle != setPoint.end();subRectHasObstacle++) {
		
		std::cout << "(" << subRectHasObstacle->x_origin << "," <<subRectHasObstacle->y_origin<<  ")" << std::endl;

	}
	
	return setPoint;
}


/*
由一个子区域起始点的坐标计算出其周围八个子区域起始坐标
*/
std::vector<Point> Canvas::eightSubRectsByOnePoint(Point *pointRect)
{
	std::vector<Point> eightSubRectsVector;

	Point point0(pointRect->getX_origin() - this->getXscalar(), pointRect->getY_origin());//矩形左方区域
	Point point1(pointRect->getX_origin(), pointRect->getY_origin() - this->getYscalar());//矩形上方区域
	Point point2(pointRect->getX_origin() + this->getXscalar(), pointRect->getY_origin());//矩形右方区域
	Point point3(pointRect->getX_origin(), pointRect->getY_origin() + this->getYscalar());//矩形下方区域
	Point point4(pointRect->getX_origin() - this->getXscalar(), pointRect->getY_origin() - this->getYscalar());//矩形左上方区域
	Point point5(pointRect->getX_origin() + this->getXscalar(), pointRect->getY_origin() - this->getYscalar());//矩形右上方区域
	Point point6(pointRect->getX_origin() - this->getXscalar(), pointRect->getY_origin() + this->getYscalar());//矩形左下方区域
	Point point7(pointRect->getX_origin() + this->getXscalar(), pointRect->getY_origin() + this->getYscalar());//矩形右下方区域

	eightSubRectsVector.push_back(point0);//下标0代表矩形左方区域
	eightSubRectsVector.push_back(point1);//下标1代表矩形上方区域
	eightSubRectsVector.push_back(point2);//下标2代表矩形右方区域
	eightSubRectsVector.push_back(point3);//下标3代表矩形下方区域
	eightSubRectsVector.push_back(point4);//下标4代表矩形左上方区域
	eightSubRectsVector.push_back(point5);//下标5代表矩形右上方区域
	eightSubRectsVector.push_back(point6);//下标6代表矩形左下区域
	eightSubRectsVector.push_back(point7);//下标7代表矩形右下方区域
	eightSubRectsVector.push_back(*pointRect);//参数传入的子区域本身

	return eightSubRectsVector;
}

/*
传入矩形左上方顶点坐标计算出四个顶点的坐标存入vector返回
*/

std::vector<Point> Canvas::fourVertexOfRect(Point * pointRect)
{
	std::vector<Point> fourVertexVector;

	Point leftUpPoint(pointRect->getX_origin(), pointRect->getX_origin());//子区域左上方顶点坐标
	Point rightUpPoint(pointRect->getX_origin() + this->getXscalar(), pointRect->getY_origin());//子区域右上方顶点坐标
	Point leftDownPoint(pointRect->getX_origin(), pointRect->getY_origin() + this->getYscalar());//子区域左下方顶点坐标
	Point rightDownPoint(pointRect->getX_origin() + this->getXscalar(), pointRect->getY_origin() + this->getYscalar());//子区域右下方顶点坐标

	fourVertexVector.push_back(leftUpPoint);
	fourVertexVector.push_back(rightUpPoint);
	fourVertexVector.push_back(leftDownPoint);
	fourVertexVector.push_back(rightDownPoint);

	return fourVertexVector;
}

/*
计算出圆心位于哪个子区域
*/

Point Canvas::findCenterInWhichSubRect(Circle &circle)//计算圆心所在子区域
{
	int timesX = (int)(circle.getX_origin()) / (this->getXscalar());
	int timesY = (int)(circle.getY_origin()) / (this->getYscalar());
	int tempX = (timesX * (this->getXscalar()));
	int tempY = (timesY * (this->getYscalar()));
	Point point(tempX, tempY);
	return point;
}

/*
圆经过的区域
*/

std::vector<Point> Canvas::circleBySubRect(int index, Point * pointRect, std::vector<double> &distance, Circle &circle)
{
	std::vector<Point> pointRects;
	std::vector<Point> eigthSubRects;

	eigthSubRects = eightSubRectsByOnePoint(pointRect);

	if (distance[index] == circle.getR())//圆心到顶点的距离等于半径
	{
		if (index == 0) {
			pointRects.push_back(eigthSubRects[0]);
			pointRects.push_back(eigthSubRects[1]);
			
		}
		else if (index == 1) {
			pointRects.push_back(eigthSubRects[1]);
			pointRects.push_back(eigthSubRects[2]);
			
		}
		else if (index == 2)
		{
			pointRects.push_back(eigthSubRects[0]);
			pointRects.push_back(eigthSubRects[3]);
			
		}
		else if (index == 3)
		{
			pointRects.push_back(eigthSubRects[2]);
			pointRects.push_back(eigthSubRects[3]);
			
		}
	}

	else if (distance[index] < circle.getR()) {//圆心到顶点的距离小于半径
		if (index == 0) {
			pointRects.push_back(eigthSubRects[0]);
			pointRects.push_back(eigthSubRects[1]);
			pointRects.push_back(eigthSubRects[4]);
		}
		else if (index == 1) {
			
			pointRects.push_back(eigthSubRects[1]);
			pointRects.push_back(eigthSubRects[2]);
			pointRects.push_back(eigthSubRects[5]);
		}
		else if (index == 2)
		{
			pointRects.push_back(eigthSubRects[0]);
			pointRects.push_back(eigthSubRects[3]);
			pointRects.push_back(eigthSubRects[7]);

		}
		else if (index == 3)
		{
			
			pointRects.push_back(eigthSubRects[2]);
			pointRects.push_back(eigthSubRects[3]);
			pointRects.push_back(eigthSubRects[7]);
		}
	}

	else if (distance[index] > circle.getR()) {//圆心到顶点的距离大于半径
		if (circle.getX_origin() - this->getXscalar() < circle.getR()) {
			pointRects.push_back(eigthSubRects[0]);

			if (circle.getY_origin() - this->getYscalar() < circle.getR()) {
				pointRects.push_back(eigthSubRects[1]);

				if ((this->getXscalar() + pointRect->getX_origin()) - circle.getX_origin() < circle.getR()) {
					pointRects.push_back(eigthSubRects[2]);
				}

				if ((this->getYscalar() + pointRect->getY_origin()) - circle.getY_origin() < circle.getR()) {
					pointRects.push_back(eigthSubRects[3]);

				}				
			}
		}
	}
	return pointRects;
}

void Canvas::setXscalar(int xScalar)
{
	this->xScalar = xScalar;
}

int Canvas::getXscalar()
{
	return this->xScalar;
}

void Canvas::setYscalar(int yScalar)
{
	this->yScalar = yScalar;
}

int Canvas::getYscalar()
{
	return this->yScalar;
}
