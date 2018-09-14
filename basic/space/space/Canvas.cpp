//
// Created by Aurora on 2018/9/14.
//

#include "Canvas.h"

std::default_random_engine Canvas::random(time(NULL));


Canvas::Canvas()
{

}


Canvas::~Canvas()
{

}

std::vector<Circle> Canvas:: addCircle(Rect *rect, int count){//生成count个圆并存入vector返回
    std::vector<Circle> vectorCircle;
    std::uniform_real_distribution<double> xRand(rect->getX_origin()+20, rect->getX_max()-20);
	std::uniform_real_distribution<double> yRand(rect->getY_origin()+20, rect->getY_max()-20);
	std::uniform_real_distribution<double> rRand(0,20);
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

std::vector<Point> Canvas:: cutRectByScalar(Rect *rect, double x, double y){
    std::vector<Point> vectorRect;
    double temp1 = rect->getX_max()-rect->getX_origin();
    double temp2 = rect->getY_max()-rect->getY_origin();
    int xTimes = temp1 / x;
    double xMod = temp1-xTimes * x;
    int yTimes = temp2 / y;
    double yMod = temp2-yTimes * y;
    if(xMod == 0 && yMod == 0){

        for(int i = 0; i < yTimes; i++){
            for(int j = 0; j < xTimes; j++){
                Point pointRect(j * x, i * y);
                vectorRect.push_back(pointRect);
            }

        }
        std::cout<<"the space that has been cut:"<<std::endl;
        std::vector<Point>::iterator it;
        for(it=vectorRect.begin();it!=vectorRect.end();it++){
            std::cout<<"("<<(*it).getX_origin()<<","<<(*it).getY_origin()<<")"<<"\t";
        }
    }

    return vectorRect;

}