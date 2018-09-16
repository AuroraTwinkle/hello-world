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
    std::uniform_int_distribution<int> xRand(rect->getX_origin(), rect->getX_max()-1);//圆心x坐标范围
	std::uniform_int_distribution<int> yRand(rect->getY_origin(), rect->getY_max()-1);//圆心y坐标范围
	int minXYscalar = std::min(this->xScalar, this->yScalar);//取分割标度的最小值
	
    for(int i=0;i<count;i++){//随机生成随机大小的圆并放入vector
        int x = xRand(random);
        int y = yRand(random);
		int r = 0;
		std::vector<double> distCenterToSides = distCenterToSide(rect, x, y);
		std::uniform_int_distribution<int> rRand(0, minXYscalar);
		r = rRand(random);
		if (distLessXYScalar(distCenterToSides)) {//保证圆心坐标临近边界时半径随机范围相应减少以避免圆超出边界
			double minDist;
			for (int i = 0; i < 3; i++) {
				minDist = std::min(distCenterToSides[i], distCenterToSides[i + 1]);//取圆心到矩形四条边的距离最小值
			}
			std::uniform_int_distribution<int> rRand0(0, minDist);
			r = rRand0(random);
		}		
        Circle circle(x,y,r);
        vectorCircle.push_back(circle);
    }
    return vectorCircle;
}

/*
在Canvas添加一个矩形
*/
Rect Canvas:: addRect(int x_origin, int y_origin, int x_max, int y_max){
    Rect rect(x_origin,y_origin,x_max,y_max);
    return rect;
}
/*
若number1不能被number2整除，则其相除结果加一
*/
int Canvas::addOneToSomeNumber(int number1, int number2)
{
	if (number1 % number2 == 0) {
		return number1 / number2;
	}
	return (number1 / number2) + 1;
}

/*
将被障碍物占领的子区域加入集合
*/

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
			setPoint.insert(eigthSubRectss[8]);//子区域本身
		}

		else {
			std::vector<double> ::iterator minDistance = std::min_element(distance.begin(), distance.end());
			int index = minDistance - distance.begin();//获得距离最小值的下标，以确定圆心离哪个子区域最近，0代表左上，1代表右上，2代表左下，3代表右下
			std::vector<Point> pointRects = circleBySubRect(index, &eigthSubRectss[8], distance, circle);
			for (auto pointRec = pointRects.begin(); pointRec != pointRects.end(); pointRec++) {
				if (isInRect(rect, *pointRec))//若子区域合法，即子区域在大矩形区域内
				{
					setPoint.insert(*pointRec);
				}
			}
			setPoint.insert(eigthSubRectss[8]);//子区域本身
		}

	}
}
/*
判断是否有圆心到矩形四边的距离小于分割标度
*/
bool Canvas::distLessXYScalar(std::vector<double> distCenterToSides)
{
	return distCenterToSides[0] < this->xScalar || distCenterToSides[1] < this->xScalar || distCenterToSides[2]< this->yScalar || distCenterToSides[3] < this->yScalar;
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
	int xTimes = addOneToSomeNumber(temp1, xScalar);//temp1是xScalar(分割矩形的x标度)的多少倍
    int xMod = temp1 % xScalar;//分割后矩形x方向上不足一个xScalar标度的剩余值
    int yTimes = addOneToSomeNumber(temp2 , yScalar);//temp1是yScalar(分割矩形的y标度)的多少倍
    int yMod = temp2 % yScalar;//分割后矩形y方向上不足一个yScalar标度的剩余值
   
    for(int i = 0; i < yTimes; i++){
       for(int j = 0; j < xTimes; j++){
           Point pointRect(j * xScalar, i * yScalar);
           vectorRect.push_back(pointRect);
        }

    }
    

	std::cout << "the space that has been cut:" << std::endl;
	std::vector<Point>::iterator it;
	int ii = 0;//用来控制打印格式
	int jj = 0;//用来控制打印格式
	for (it = vectorRect.begin(); it != vectorRect.end(); it++) {//打印分割后的区域
		std::cout << "(" << (*it).getX_origin() << "," << (*it).getY_origin() << ")" << "\t";
		ii++;

		if (xMod != 0&&ii==xTimes) {
			std::cout << "the x length of the last column subRect in this line is:" << xMod;
		}
		if (ii == xTimes) {
			jj++;
			std::cout << std::endl;
			ii = 0;
		}
		if (yMod != 0 && jj == yTimes) {
			std::cout << "all the y lengths of last line's subRects are:" << yMod;
		}
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
计算点到矩形四边的距离
*/

std::vector<double> Canvas::distCenterToSide(Rect *rect, int x, int y)
{
	std::vector<double> distanceToSide;

	distanceToSide.push_back(x - rect->getX_origin()); //distanceToSide[0]代表点到矩形左边的距离
	distanceToSide.push_back(rect->getX_max() - x);//distanceToSide[1]代表点到矩形右边的距离
	distanceToSide.push_back(y - rect->getY_origin());//distanceToSide[2]代表点到矩形上边的距离
	distanceToSide.push_back(rect->getY_max() - y);//distanceToSide[3]代表点到矩形下边的距离

	return distanceToSide;
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
	for (auto subRectHasObstacle = setPoint.begin(); subRectHasObstacle != setPoint.end();subRectHasObstacle++) {//遍历打印被占领区域
		
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
	std::vector<Point> eightSubRects = eightSubRectsByOnePoint(pointRect);

	for (int i = 4; i < 8; i++) {
		fourVertexVector.push_back(eightSubRects[i]); //eightSubRects[4], [5], [6], [7]分别代表左上，右上，左下，右下子区域
	}

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
	bool isLessDist = distance[index] < circle.getR();//圆心到顶点的距离是否小于半径
	bool isEqualDist = distance[index] == circle.getR();//圆心到顶点的距离是否等于半径
	bool isGreaterDist = distance[index] > circle.getR();//圆心到顶点的距离是否大于半径

	if (isEqualDist)//圆心到顶点的距离等于半径
	{
		if (index == 0) {//圆心到矩形左上方顶点距离最近
			pointRects.push_back(eigthSubRects[0]);//子区域本身左方子区域
			pointRects.push_back(eigthSubRects[1]);//子区域本身上方子区域
			if (isLessDist) {
				pointRects.push_back(eigthSubRects[4]);//子区域本身左上方子区域
			}
		}
		else if (index == 1) {//圆心到矩形右上方顶点距离最近
			pointRects.push_back(eigthSubRects[1]);//子区域本身上方子区域
			pointRects.push_back(eigthSubRects[2]);//子区域本身右方子区域
			if (isLessDist) {
				pointRects.push_back(eigthSubRects[5]);//子区域本身右上方子区域
			}
		}
		else if (index == 2)////圆心到矩形左下方顶点距离最近
		{
			pointRects.push_back(eigthSubRects[0]);//子区域本身左方子区域
			pointRects.push_back(eigthSubRects[3]);//子区域本身下方子区域
			if (isLessDist) {
				pointRects.push_back(eigthSubRects[7]);//子区域本身右下方子区域
			}
		}
		else if (index == 3)////圆心到矩形右下方顶点距离最近
		{
			pointRects.push_back(eigthSubRects[2]);//子区域本身右方子区域
			pointRects.push_back(eigthSubRects[3]);//子区域本身下方子区域
			if (isLessDist) {
				pointRects.push_back(eigthSubRects[7]);//子区域本身右下方子区域
			}
		}
	}

	else if (isGreaterDist) {//圆心到顶点的距离大于半径
		if (circle.getX_origin() - pointRect->getX_origin() < circle.getR()) {//圆心到子区域左边的距离小于半径
			pointRects.push_back(eigthSubRects[0]);//子区域本身左方子区域
		}
		if (circle.getY_origin() - pointRect->getY_origin() < circle.getR()) {//圆心到子区域上边的距离小于半径
			pointRects.push_back(eigthSubRects[1]);//子区域本身上方子区域
		}
		if ((this->getXscalar() + pointRect->getX_origin()) - circle.getX_origin() < circle.getR()) {//圆心到子区域右边的距离小于半径
			pointRects.push_back(eigthSubRects[2]);//子区域本右方子区域
		}

		if ((this->getYscalar() + pointRect->getY_origin()) - circle.getY_origin() < circle.getR()) {//圆心到子区域下边的距离小于半径
			pointRects.push_back(eigthSubRects[3]);//子区域本身下方子区域

		}				
	}

	/*
	下面这段代码用于调试用，可去掉
	
	std::cout << "the circle:" << "(" << circle.getX_origin() << "," << circle.getY_origin()<<","<<circle.getR() << ")" << "has obstacle:";
	for (auto ptRect = pointRects.begin(); ptRect != pointRects.end(); ptRect++) {
		std::cout << "(" << ptRect->getX_origin() << "," << ptRect->getY_origin() << ")";
	}
	std::cout << std::endl;
	
	*/
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
