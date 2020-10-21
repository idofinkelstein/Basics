#include <iostream>
#include <cstdlib>

#include "glut_utils.h"
#include "shapes.hpp"

namespace ilrd
{
namespace rd90
{

Point::Point(double m_x, double m_y) : m_x(m_x), m_y(m_y) {}

Point& Point::operator+=(const Point& other)
{
	// a += b

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

void Shape::Draw(){}
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

void Shape::Rotate(double angle)
{
	
}

Circle::Circle(const Point& position, double radius) : Shape(position, 0), radius(radius) {}

void Circle::Draw()
{
	DrawCircle(GetColor(), GetPoint().GetX(), GetPoint().GetY(), radius);
}

Rectangle::Rectangle(const Point& position, double height, double width): Shape(position), height(height), width(width) {}

void Rectangle::Draw()
{
	int x = static_cast<int>(GetPoint().GetX());
	int y = static_cast<int>(GetPoint().GetY());
	int xOffSet = width;
	int yOffSet = height;

	  DrawPolygon(GetColor(),					 4,
        					x,				    	         y,
       						x + xOffSet,	             y,
        					x + xOffSet,			    y + yOffSet,
       						x, 			    				y + yOffSet);
}
/*
class Triangle : public Shape
{
public:
    explicit Triangle(const Point& position, double height, double base, double dist);

    virtual void Draw();

private:
    double height;
    double base;
    double dist;
};
*/

Triangle::Triangle(const Point& position, double height, double base, double dist) : Shape(position), height(height), base(base), dist(dist) {}

void Triangle::Draw()
{

}
}// namespace rd90
}// namespace ilrd
