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
    std::uniform_real_distribution<double> xRand(rect->getX_origin()+20, rect->getX_max()-20);
	std::uniform_real_distribution<double> yRand(rect->getY_origin()+20, rect->getY_max()-20);
	std::uniform_real_distribution<double> rRand(0, (this->getXscalar()));
    for(int i=0;i<count;i++){//随机生成随机大小的圆并放入vector
        double x = xRand(random);
        double y = yRand(random);
        double r = rRand(random);
        Circle circle(x,y,r);
        vectorCircle.push_back(circle);
    }
    return vectorCircle;
}

Rect Canvas:: addRect(double x_origin, double y_origin, double x_max, double y_max){
    Rect rect(x_origin,y_origin,x_max,y_max);
    return rect;
}

std::vector<Point> Canvas:: cutRectByScalar(Rect *rect, double xScalar, double yScalar){
	this->setXscalar(xScalar);
	this->setYscalar(yScalar);
    std::vector<Point> vectorRect;
    double temp1 = rect->getX_max()-rect->getX_origin();//临时变量，存储矩形区域x方向的长度
    double temp2 = rect->getY_max()-rect->getY_origin();//临时变量，存储矩形区域y方向的长度
    int xTimes = temp1 / xScalar;//temp1是xScalar(分割矩形的x标度)的多少倍
    double xMod = temp1-xTimes * xScalar;//分割后矩形x方向上不足一个xScalar标度的剩余值
    int yTimes = temp2 / yScalar;//temp1是yScalar(分割矩形的y标度)的多少倍
    double yMod = temp2-yTimes * yScalar;//分割后矩形y方向上不足一个yScalar标度的剩余值
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

std::set<Point> Canvas::findSubRectHasObstacle(Rect * rect, std::vector<Circle> vectorCircle)
{
	std::set<Point> setPoint;
	for (auto circle = vectorCircle.begin(); circle != vectorCircle.end();) {
		if (circle->getR() < this->getXscalar() && circle->getR() < this->getYscalar()) {
			Point pointRect = findCenterInWhichSubRect(*circle);
			setPoint.insert(pointRect);
		}
	}

	return setPoint;
}

Point Canvas::findCenterInWhichSubRect(Circle circle)//计算圆心所在子区域
{
	int timesX = (int)(circle.getX_origin()) / (this->getXscalar());
	int timesY = (int)(circle.getY_origin()) / (this->getYscalar());
	double tempX = (timesX * (this->getXscalar()));
	double tempY = (timesY * (this->getYscalar()));
	Point point(tempX, tempY);
	return point;
}

void Canvas::setXscalar(double xScalar)
{
	this->xScalar = xScalar;
}

double Canvas::getXscalar()
{
	return this->xScalar;
}

void Canvas::setYscalar(double yScalar)
{
	this->yScalar = yScalar;
}

double Canvas::getYscalar()
{
	return this->yScalar;
}
