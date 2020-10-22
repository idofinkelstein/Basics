#include <iostream>
#include <cstdlib>
#include <cmath>

#include "glut_utils.h"
#include "shapes.hpp"

namespace ilrd
{
namespace rd90
{

Point::Point(double m_x, double m_y) : m_x(m_x), m_y(m_y) {}

Point& Point::operator+=(const Point& other)
{
	m_x += other.m_x;
	m_y += other.m_y;

	return (*this);
}

const Point Point::operator+(const Point& other) const
{
	Point p(*this);

	return (p += other);
}

double Point::GetX() const
{
	return (m_x);
}

double Point::GetY() const
{
	return (m_y);
}

void Point::SetX(double x)
{
	m_x = x;
}

void Point::SetY(double y)
{
	m_y = y;
}

Shape::Shape(const Point& position, double angle, COLORS color) : position(position), angle(angle), color(color) {}

Shape::~Shape() {}

void Shape::Step(const Point& delta)
{
	position += delta;
}

int Shape::GetColor() const
{
	return (color);
}

void Shape::Move(const Point& new_pos)
{
	position = new_pos;
}

const Point &Shape::GetPoint() const
{
	return (position);
}


void Shape::SetColor(int color)
{
	this->color = color;
}

void Shape::Draw(const Point &parentPos)
{
	Point absPos = parentPos + GetPoint();

	DrawShape(absPos);
}

/*
void Shape::Rotate(double angle)
{
	 double sinVal = sin(angle);
    double cosVal = cos(angle);

    // translate point back to origin: 
    double xOffset = GetPoint().GetX() - pivot->m_x;
    double yOffset = p->m_y - pivot->m_y;

     //rotate point & translate point back: 
    p->m_x = pivot->m_x + xOffset * cosVal - yOffset * sinVal;
    p->m_y = pivot->m_y + xOffset * sinVal + yOffset * cosVal;
}
*/
Circle::Circle(const Point& position, double radius) : Shape(position, 0), radius(radius) {}

void Circle::DrawShape(const Point &absPos)
{
	DrawCircle(GetColor(), absPos.GetX(), absPos.GetY(), radius);
}

Rectangle::Rectangle(const Point& position, double height, double width): Shape(position), height(height), width(width) {}

void Rectangle::DrawShape(const Point &absPos)
{
	//Point absPos = parentPos + GetPoint();
	int x = static_cast<int>(absPos.GetX());
	int y = static_cast<int>(absPos.GetY());
	int xOffSet = width;
	int yOffSet = height;

	  DrawPolygon(GetColor(),					 4,
        					x,				    	         y,
       						x + xOffSet,	             y,
        					x + xOffSet,			    y + yOffSet,
       						x, 			    				y + yOffSet);
}


Triangle::Triangle(const Point& position, double height, double base, double dist) : Shape(position), height(height), base(base), dist(dist) {}

void Triangle::DrawShape(const Point &absPos)
{
	int x = static_cast<int>(absPos.GetX());
	int y = static_cast<int>(absPos.GetY());
	int Base = base;
	int Height = height;
	int Dist = dist;

	  DrawPolygon(GetColor(),					 3,
        					x,				    	         y,
       						x + Base,	             y,
       						x + Dist, 			    				y + Height);
}

/*
class Group : public Shape
{
public:
    explicit Group(const Point& position); 

    virtual void Draw();
    void Add(const Shape *shape);

private:
    Shape *shapes[50];
    std::size_t size;
};
*/

Group::Group(const Point& position) : Shape(position), size(0) {}

void Group::Add(Shape *shape)
{
	shapes[size] = shape;
	++size;
}

void Group::DrawShape(const Point &absPos)
{

	for (std::size_t i = 0; i < size; ++i)
	{
		shapes[i]->Draw(absPos);
	} 
}

}// namespace rd90
}// namespace ilrd
