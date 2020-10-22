/* 


*/

#pragma once

#include <iostream>     // size_t



/*---------------------------------------------------------------------------*/

namespace ilrd
{
namespace rd90
{

/*********************   Free Functions declarations    ***********************/


/************************   Classes declarations    **************************/
class Point
{
public:
    explicit Point(double m_x = 0, double m_y = 0);
    
    Point& operator+=(const Point& other);
    const Point operator+(const Point& other) const; 
    //... Revolve(double angle, const point& ) const // .revolve p3 = 
    // colission() const

    double GetX() const;
    double GetY() const;
	void SetX(double x);
    void SetY(double y);
    
private:
    double m_x;
    double m_y;
};

/*---------------------------------------------------------------------------*/

class Shape
{
    public:
        enum COLORS
        {
            COLOR_RED     = 0x010000,
            COLOR_GREEN   = 0x000100,
            COLOR_BLUE    = 0x000001,
            COLOR_YELLOW  = 0x010100,
            COLOR_MAGENTA = 0x010001,
            COLOR_CYAN    = 0x000101,
            COLOR_WHITE   = 0x010101,
            COLOR_BLACK   = 0x000000,
            COLOR_GRAY    = 0x4000000,
            COLOR_FILL    = 0x8000000
        }; //TBC 

        explicit Shape(const Point& position, double angle = 0, COLORS color = COLOR_MAGENTA);
        virtual ~Shape();

        void Step(const Point& delta);
        void Move(const Point& new_pos);
        void Rotate(double angle);
        const Point& GetPoint() const;
		int GetColor() const;
		void SetColor(int color);
		void Draw(const Point &parentPos = Point(0, 0));

    private:
        virtual void DrawShape(const Point &absPos) = 0;
        Point position;
        double angle;
		int color;
};


/*---------------------------------------------------------------------------*/

class Circle : public Shape
{
public:
    explicit Circle(const Point& position, double radius); // : Shape(positon)

private:
    virtual void DrawShape(const Point &absPos);
    double radius;
};

/*---------------------------------------------------------------------------*/

class Rectangle : public Shape
{
public:
    explicit Rectangle(const Point& position, double height, double width);

private:
     virtual void DrawShape(const Point &absPos);
    double height;
    double width;
};


/*---------------------------------------------------------------------------*/

class Triangle : public Shape
{
public:
    explicit Triangle(const Point& position, double height, double base, double dist);


private:
     virtual void DrawShape(const Point &absPos);
    double height;
    double base;
    double dist;
};

/*---------------------------------------------------------------------------*/

class Group : public Shape
{
public:
    explicit Group(const Point& position); 

    void Add(Shape *shape);

private:
    virtual void DrawShape(const Point &absPos);
    Shape *shapes[50];
    std::size_t size;
};


/***************************   Inline Functions    ****************************/



} // namespace rd90
} // namespace ilrd







