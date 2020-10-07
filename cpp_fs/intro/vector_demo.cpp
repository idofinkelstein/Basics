#include <iostream>
#include <string.h>
#include <stdlib.h>

struct Vector
{
	explicit Vector();
	explicit Vector(size_t capacity);
	Vector &operator=(const Vector& other);
	~Vector();
	Vector(const Vector& other);

	size_t capacity;
	size_t size;
	void **data;
};

Vector::Vector(): capacity(10), size(0)
{
	data = static_cast<void**>(malloc(sizeof(void*) * capacity));
	
	/* just for debug */
	std::cout << this << std::endl;
	std::cout << capacity << std::endl;
	std::cout << size << std::endl;
}

Vector::Vector(size_t capacity): capacity(capacity), size(0)
{
	data = static_cast<void**>(malloc(sizeof(void*) * capacity));

	/* just for debug */
	std::cout << this << std::endl;
	std::cout << capacity << std::endl;
	std::cout << size << std::endl;
}

Vector::Vector(const Vector& other): capacity(other.capacity), 
														size(other.size),
 														data(static_cast<void**>(malloc(sizeof(void*) * other.capacity)))
{
	memcpy(data, other.data, capacity * sizeof(void*));

	/* just for debug */
	std::cout << this << std::endl;
	std::cout << capacity << std::endl;
	std::cout << size << std::endl;
}

Vector &Vector::operator=(const Vector& other)
{
	memcpy(data, other.data, capacity * sizeof(void*));
	this->capacity = other.capacity;
	this->size = other.size;

	/* just for debug */
	std::cout << this << std::endl;
	std::cout << &other << std::endl;
	std::cout << capacity << std::endl;
	std::cout << size << std::endl;

	return (*this);
}

Vector::~Vector()
{
	free(data);
	std::cout << "destroied" << std::endl;
}

int main()
{
	Vector v1;
	Vector v2(20);
	Vector v3 = v2;

	v1 = v3;

	return 0;
}


