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

std::vector<Circle> Canvas:: addCircle(Rect *rect, int count){//生成count个圆并存入vector返回
    std::vector<Circle> vectorCircle;
    std::uniform_int_distribution<int> xRand(rect->getX_origin()+20, rect->getX_max()-20);
	std::uniform_int_distribution<int> yRand(rect->getY_origin()+20, rect->getY_max()-20);
	std::uniform_int_distribution<int> rRand(0, (this->getXscalar()));
    for(int i=0;i<count;i++){//随机生成随机大小的圆并放入vector
        int x = xRand(random);
        int y = yRand(random);
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
        std::cout<<"the space that has been cut:"<<std::endl;
        std::vector<Point>::iterator it;
        for(it=vectorRect.begin();it!=vectorRect.end();it++){
            std::cout<<"("<<(*it).getX_origin()<<","<<(*it).getY_origin()<<")"<<"\t";
        }
		std::cout << std::endl;
    }

    return vectorRect;

}

std::vector<Point> Canvas::findSubRectHasObstacle(Rect * rect, std::vector<Circle> &vectorCircle)
{
	std::vector<Point> setPoint;
	int xScalar = this->getXscalar();
	int yScalar = this->getYscalar();
	for (auto circle = vectorCircle.begin(); circle != vectorCircle.end();circle++) {
		if (circle->getR() < xScalar && circle->getR() < yScalar) {//圆小于分割标度的情况
			int xOrigin = circle->getX_origin();//圆心x坐标
			int yOrigin = circle->getY_origin();//圆心y坐标
			Point pointRect = findCenterInWhichSubRect(*circle);//圆心所在子区域
			std::vector<double> distance = distCenterToVertex(&pointRect, *circle);//圆心到四个顶点的距离
			if ((xOrigin % xScalar)==0 && (yOrigin % yScalar)==0){//圆心刚好在子区域起始点
				Point point(xOrigin, yOrigin);//起始点右下方区域
				Point point1(xOrigin, yOrigin - yScalar);//起始点右上方区域
				Point point2(xOrigin - xScalar, yOrigin);//起始点左下方区域
				Point point3(xOrigin - xScalar, yOrigin - yScalar);//起始点左上方区域
				setPoint.push_back(point);
				setPoint.push_back(point1);
				setPoint.push_back(point2);
				setPoint.push_back(point3);
			}
			
			else if(distance[0]==distance[1]==distance[2])//圆心到四个顶点的距离相同时
			{
				setPoint.push_back(pointRect);
			}
			
			else {
				std::vector<double> ::iterator minDistance = std::min_element(distance.begin(), distance.end());
				int index = minDistance - distance.begin();//获得距离最小值的下标，以确定圆心离哪个子区域最近，0代表左上，1代表右上，2代表左下，3代表右下
				std::vector<Point> pointRects = circleBySubRect(index, &pointRect, distance, *circle);
				for (auto pointRec = pointRects.begin(); pointRec != pointRects.end();pointRec++) {
					setPoint.push_back(*pointRec);
				}
				setPoint.push_back(pointRect);
			}

		}
	}
	setPoint.erase(std::unique(setPoint.begin(), setPoint.end()), setPoint.end());
	std::cout << "the subRect that has been obstacle:" << std::endl;
	for (auto subRectHasObstacle = setPoint.begin(); subRectHasObstacle != setPoint.end();subRectHasObstacle++) {
		
		std::cout << "(" << subRectHasObstacle->getX_origin() << "," << subRectHasObstacle->getY_origin() << ")" << std::endl;

	}
	
	return setPoint;
}

Point Canvas::findCenterInWhichSubRect(Circle &circle)//计算圆心所在子区域
{
	int timesX = (int)(circle.getX_origin()) / (this->getXscalar());
	int timesY = (int)(circle.getY_origin()) / (this->getYscalar());
	int tempX = (timesX * (this->getXscalar()));
	int tempY = (timesY * (this->getYscalar()));
	Point point(tempX, tempY);
	return point;
}

std::vector<Point> Canvas::circleBySubRect(int index, Point * pointRect, std::vector<double> &distance, Circle &circle)
{
	std::vector<Point> pointRects;
	Point point1(pointRect->getX_origin() - this->getXscalar(), pointRect->getY_origin());//圆心左方区域
	Point point2(pointRect->getX_origin(), pointRect->getY_origin() - this->getYscalar());//圆心上方区域
	Point point3(pointRect->getX_origin() + this->getXscalar(), pointRect->getY_origin());//圆心右方区域
	Point point4(pointRect->getX_origin(), pointRect->getY_origin() + this->getYscalar());//圆心下方区域
	Point point5(pointRect->getX_origin() - this->getXscalar(), pointRect->getY_origin() - this->getYscalar());//圆心左上方区域
	Point point6(pointRect->getX_origin() + this->getXscalar(), pointRect->getY_origin() - this->getYscalar());//圆心右上方区域
	Point point7(pointRect->getX_origin() - this->getXscalar(), pointRect->getY_origin() + this->getYscalar());//圆心左下方区域
	Point point8(pointRect->getX_origin() + this->getXscalar(), pointRect->getY_origin() + this->getYscalar());//圆心右下方区域
	if (distance[index] == circle.getR())//圆心到顶点的距离等于半径
	{
		if (index == 0) {
			pointRects.push_back(point1);
			pointRects.push_back(point2);
			pointRects.push_back(point5);
		}
		else if (index == 1) {
			pointRects.push_back(point3);
			pointRects.push_back(point2);
			pointRects.push_back(point6);
		}
		else if (index == 2)
		{
			pointRects.push_back(point1);
			pointRects.push_back(point4); 
			pointRects.push_back(point7);
		}
		else if(index==3)
		{
			pointRects.push_back(point3);
			pointRects.push_back(point4);
			pointRects.push_back(point8);
		}
	}

	else if (distance[index] < circle.getR()) {//圆心到顶点的距离小于半径
		if (index == 0) {
			pointRects.push_back(point1);
			pointRects.push_back(point2);
		}
		else if (index == 1) {
			pointRects.push_back(point3);
			pointRects.push_back(point2);
		}
		else if (index == 2)
		{
			pointRects.push_back(point1);
			pointRects.push_back(point4);
		}
		else if (index == 3)
		{
			pointRects.push_back(point3);
			pointRects.push_back(point4);
		}
	}

	else if (distance[index] > circle.getR()) {//圆心到顶点的距离大于半径
		if (circle.getX_origin() - this->getXscalar() < circle.getR()) {
			pointRects.push_back(point1);
		}

		if (circle.getY_origin() - this->getYscalar() < circle.getR()) {
			pointRects.push_back(point2);
		}

		if ((this->getXscalar()+ pointRect->getX_origin())-circle.getX_origin() < circle.getR()) {
			pointRects.push_back(point3);
		}

		if ((this->getYscalar() + pointRect->getY_origin()) - circle.getY_origin() < circle.getR()) {
			pointRects.push_back(point4);
		}
		
	}

	return pointRects;
}

std::vector<double> Canvas::distCenterToVertex(Point * point, Circle &circle)
{
	std::vector<double> distance;
	int circleCenterX = circle.getX_origin();
	int circleCenterY = circle.getY_origin();//圆心坐标

	int leftUpX = point->getX_origin();
	int leftUpY = point->getY_origin();//子区域左上方顶点坐标

	int rightUpX = point->getX_origin() + this->getXscalar();
	int rightUpY = point->getY_origin();//子区域右上方顶点坐标

	int leftDownX = point->getX_origin();
	int leftDownY = point->getY_origin() + this->getYscalar();//子区域左下方顶点坐标

	int rightDownX = point->getX_origin() + this->getXscalar();
	int rightDownY = point->getY_origin() + this->getYscalar();//子区域右下方顶点坐标

	double distLeftUp = sqrt((circleCenterX - leftUpX)*(circleCenterX - leftUpX) + (circleCenterY - leftUpY)*(circleCenterY - leftUpY));
	double distRightUp = sqrt((circleCenterX - rightUpX)*(circleCenterX - rightUpX) + (circleCenterY - rightUpY)*(circleCenterY - rightUpY));
	double distLeftDown = sqrt((circleCenterX - leftDownX)*(circleCenterX - leftDownX) + (circleCenterY - leftDownY)*(circleCenterY - leftDownY));
	double distRightDown = sqrt((circleCenterX - rightDownX)*(circleCenterX - rightDownX) + (circleCenterY - rightDownY)*(circleCenterY - rightDownY));

	/*
	这样做的原因是，可以用distance[0]代表圆心到子区域左上方顶点的距离，
	distance[1]代表到子区域右上方的距离......以此类推，得到圆心到四个顶点的距离
	*/
	distance.push_back(distLeftUp);
	distance.push_back(distRightUp);
	distance.push_back(distLeftDown);
	distance.push_back(distRightDown);




	return distance;
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
