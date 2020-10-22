#include <iostream>
#include <cstdlib>

#include "glut_utils.h"
#include "shapes.hpp"
typedef void (*DRAW_FUNC_T)();
static int TimerFunction();
static void DrawFunction();

using namespace ilrd::rd90;

static Point p1(100,100), p2(500, 500), delta(4, 4),grpStep(4,0);
static Shape *circle1 = new Circle(p1, 10);
static Shape *rec = new Rectangle(p1, 50, 100);
static Shape *tri1 = new Triangle(p2, 50, 100, 50);
static Shape *tri2 = new Triangle(p2 + Point(0 ,+25), -50, 100, 50);
static Circle circle2(p2, 40);
static Shape *grp1 = new Group(Point(214,111));
static Shape *grp2 = new Group(Point(70,70));

int main(int argc, char** argv)
{
	circle1->SetColor(COLOR_BLUE);
	rec->SetColor(COLOR_YELLOW);
	static_cast<Group*>(grp1)->Group::Add(rec);	
	static_cast<Group*>(grp1)->Group::Add(tri1);
	static_cast<Group*>(grp2)->Group::Add(tri1);
	static_cast<Group*>(grp2)->Group::Add(tri2);


	DrawInit(argc, argv, 1000, 1000, DrawFunction);
	DrawSetTimerFunc(TimerFunction, 20);

	DrawMainLoop();

	

	return 0;
}

static int TimerFunction()
{
	circle1->Step(delta);
	grp1->Step(grpStep);	
	grp2->Step(grpStep);	

	if(circle1->GetPoint().GetX() > 900 || circle1->GetPoint().GetX() < 100)
	{
		delta.SetX(-delta.GetX());
		delta.SetY(-delta.GetY());
		grpStep.SetX(-grpStep.GetX());
	}

    return 1;  /* draw */
}


static void DrawFunction()
{
	circle1->Draw();
	circle2.Draw();
	rec->Draw();
	tri1->Draw();
	
	
	grp1->Draw(grp1->GetPoint());
	grp2->Draw(grp2->GetPoint());

	
}
