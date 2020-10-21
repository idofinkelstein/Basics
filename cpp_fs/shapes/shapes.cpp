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
Shape::Shape(const Point& position, double angle, int color) : position(position), angle(angle), color(color) {}

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

int Shape::GetColor() const
{
	return (color);
}

int Shape::setColor(int color)
{
	this->color = color;
}

void Shape::Rotate(double angle)
{
	
}

Circle::Circle(const Point& position, double radius) : Shape(position, 0), radius(radius) {}

void Circle::Draw()
{
	DrawCircle(0x010000, GetPoint().GetX(), GetPoint().GetY(), radius);
}

}// namespace rd90
}// namespace ilrd
