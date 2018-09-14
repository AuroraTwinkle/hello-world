#include <iostream>
#include "Canvas.h"

int main() {
    Canvas canvas;
    Rect rect = canvas.addRect(0,0,100,100);
	canvas.addCircle(&rect,6);
    canvas.cutRectByScalar(&rect,10,100);
    return 0;
}