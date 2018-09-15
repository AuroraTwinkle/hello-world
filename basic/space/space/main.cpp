#include <iostream>
#include "Canvas.h"

int main() {
    Canvas canvas;
    Rect rect = canvas.addRect(0,0,100,100);
	canvas.cutRectByScalar(&rect, 10, 10);
	std::vector<Circle> vectorCircle = canvas.addCircle(&rect,10);
	canvas.findSubRectHasObstacle(&rect, vectorCircle);
    return 0;
}