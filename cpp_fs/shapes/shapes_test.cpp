#include <iostream>
#include <cstdlib>

#include "glut_utils.h"
#include "shapes.hpp"
typedef void (*DRAW_FUNC_T)();
static int TimerFunction();
static void DrawFunction();

using namespace ilrd::rd90;

Point p1(100,100), p2(500, 500), delta(4, 4),negdelta(-4,-4);
Shape *circle1 = new Circle(p1, 5);
Circle circle2(p2, 40);

int main(int argc, char** argv)
{
	
	DrawInit(argc, argv, 1000, 1000, DrawFunction);
	DrawSetTimerFunc(TimerFunction, 20);

	DrawMainLoop();

	

	return 0;
}

static int TimerFunction()
{
	circle1->Step(delta);
	
	if(circle1->GetPoint().GetX() > 900 || circle1->GetPoint().GetX() < 100)
	{
		delta.SetX(-delta.GetX());
		delta.SetY(-delta.GetY());
	}

    return 1;  /* draw */
}


static void DrawFunction()
{
	circle1->Draw();
	circle2.Draw();

	
}
