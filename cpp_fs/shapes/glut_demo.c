#include <stdio.h>
#include <math.h>
#include <mcheck.h>

#include "glut_utils.h"


typedef struct
{
    double m_x, m_y;
} Point;

/* rectangle data */
static const Point rectDim = { 200, 100 };
static Point rectPos = { 400, 100 };
static int rectStep = 5;

/* circle data */
static const Point circPivot = { 500, 500};
static Point circCenter = { 150, 500};
static double circRadius = 100;
static int drawCircle = 1;

static void DrawFunction();
static int TimerFunction();
static int KeyboardFunction(unsigned char key, int x, int y);
static int MouseFunction(int button, int state, int x, int y);
static int MotionFunction(int x, int y);
static void Revolve(double angle, const Point* pivot, Point* p);


int main(int argc, char** argv)
{
    /*--------------------------- mtrace(); */

    DrawInit(argc, argv, 1000, 1000, DrawFunction);
    DrawSetTimerFunc(TimerFunction, 50);

    /* advanced: extra functionality */
    DrawSetKeyboardFunc(KeyboardFunction);
    DrawSetMouseFunc(MouseFunction);
    DrawSetMotionFunc(MotionFunction);

    DrawMainLoop();

    printf("exit\n");

    return 0;
}


static void DrawFunction()
{
    /* printf("Drawing\n"); */

    /* draw rectangle */
    DrawPolygon(COLOR_MAGENTA, 4,
        (int)(rectPos.m_x),             (int)(rectPos.m_y),
        (int)(rectPos.m_x),             (int)(rectPos.m_y+rectDim.m_y),
        (int)(rectPos.m_x+rectDim.m_x), (int)(rectPos.m_y+rectDim.m_y),
        (int)(rectPos.m_x+rectDim.m_x), (int)(rectPos.m_y));

    if (drawCircle)
        DrawCircle(COLOR_GREEN, circCenter.m_x, circCenter.m_y, circRadius);
    
    DrawEllipse(COLOR_GREEN, 500, 500, 200, 80, 100);
}


static int TimerFunction()
{
    rectPos.m_y += rectStep;
    if (rectPos.m_y > 800 || rectPos.m_y < 100)
        rectStep = -rectStep;

    Revolve(+3.14/180, &circPivot, &circCenter);

    return 1;  /* draw */
}


static int KeyboardFunction(unsigned char key, int x, int y)
{
    printf("Keyboard: %02x,%d,%d\n", key, x, y);

    if (key == 0x1b /* ESC */)
        return -1;

    return 0;
}


static int MouseFunction(int button, int state, int x, int y)
{
    /* printf("Mouse: %d,%d,%d,%d\n", button, state, x, y); */

    if (state == 1 && button == MOUSE_WHEEL_UP)
    {
        circRadius *= 1.1;
        return 1;
    }
    if (state == 1 && button == MOUSE_WHEEL_DOWN)
    {
        circRadius *= 0.9;
        return 1;
    }

    if (button == MOUSE_LEFT)
    {
        drawCircle = state;
        return 1;
    }

    return 0;
}


static int MotionFunction(int x, int y)
{
    printf("Mouse: %d,%d\n", x, y);

    return 0;
}


static void Revolve(double angle, const Point* pivot, Point* p)
{
    double sinVal = sin(angle);
    double cosVal = cos(angle);

    /* translate point back to origin: */
    double xOffset = p->m_x - pivot->m_x;
    double yOffset = p->m_y - pivot->m_y;

    /* rotate point & translate point back: */
    p->m_x = pivot->m_x + xOffset * cosVal - yOffset * sinVal;
    p->m_y = pivot->m_y + xOffset * sinVal + yOffset * cosVal;
}
