/*
Dynamic vector is a random access dynamic array. 
Template class - can hold any types as long as they support:
    - copy initialization and destruction
    - assignment operator

Main operations on vector:
    -   Push back - adds an element to the end of the vector
    -   Pop back - removes the last element in the vector
    -   get m_capacity - returns the current m_capacity of the vector
    -   get m_size - returns the current number of elements in the vector
    -   operator[] const- retrieve element from specific index (read only)
    -   operator[] - retrieve access to specific index (read / write)
    -   resize - reallocates and initializes memory to the new m_capacity
    -   reserve - reallocates uninitialized memory to the new m_capacity
*/
#pragma once

#include <cstring>
#include <cstddef> //size_t
#include <cassert>
#include <new>

namespace ilrd
{
namespace rd90
{

enum factor
{
    INC_FACTOR = 2,
    DEC_FACTOR = 2,
    RESIZE_FACTOR = 4
};

template <typename T>
class DVector
{
public:
    explicit DVector(size_t init_size = 0);
    ~DVector();
    void PushBack(const T& m_data);
    void PopBack();
    inline size_t Size() const;
    inline size_t Capacity() const;
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    void Resize(size_t new_size, const T& t = T());
    void Reserve(size_t new_capacity);

private:
    DVector(const DVector& other);
    DVector& operator=(const DVector& other);
	void ChangeCapacity(size_t size);
	void Init(size_t start_index, size_t end_index, const T& t = T());

    size_t m_capacity;
    size_t m_size;
    T *m_data;    // array of T members
};


template <typename T>
DVector<T>::DVector(size_t init_size) : m_capacity(init_size * RESIZE_FACTOR + 1),
                                        m_size(init_size),
                                        m_data(static_cast<T*>(operator new (sizeof(T) * 
															   m_capacity)))
{
	Init(0, m_size);
}

template <typename T>
DVector<T>::~DVector()
{
	for (size_t i = 0; i < Size(); ++i)
	{
		m_data[i].~T();
	}

    operator delete (m_data);     
}

template <typename T>
void DVector<T>::PushBack(const T& data)
{
    if(m_size >= m_capacity)
    {
		ChangeCapacity(m_capacity * INC_FACTOR);
    }

    ++m_size;
	new (&m_data[m_size - 1]) T(data);
}

template <typename T>
 void DVector<T>::PopBack()
{
	if (0 != m_size)
	{
		m_data[m_size - 1].~T();
		--m_size;
	}
	else
	{
		return;
	}

	// reduces capacity by 2 in case of size < (current capacity / 4) 
	if (m_size < (m_capacity / RESIZE_FACTOR)) 
	{
		ChangeCapacity(m_capacity / DEC_FACTOR); 
	}
}

template <typename T>
inline size_t DVector<T>::Size() const
{
	return m_size;
}

template <typename T>
inline size_t DVector<T>::Capacity() const
{
	return m_capacity;
}

template <typename T>
T& DVector<T>::operator[](size_t index)
{
	assert(index < m_size);

	return (const_cast<T&>( static_cast<const DVector&>(*this)[index]) );
}

template <typename T>
const T& DVector<T>::operator[](size_t index) const
{
	return m_data[index];
}

template <typename T>
void DVector<T>::Reserve(size_t new_capacity)
{
	if (new_capacity > Capacity())
	{
		ChangeCapacity(new_capacity);
	}
}

template <typename T>
void DVector<T>::ChangeCapacity(size_t size)
{
	T *tmp_data = static_cast<T*>(operator new (sizeof(T) * size));

	for(size_t i = 0; i < m_size; ++i)
	{
		new (&tmp_data[i]) T(m_data[i]);

		m_data[i].~T();
	}

	operator delete (this->m_data);
    this->m_data = tmp_data;

	m_capacity = size;
}

template <typename T>
void DVector<T>::Resize(size_t new_size, const T& t)
{
	size_t start = 0, end = 0;

	if (new_size < Size())
	{
		m_size = new_size;
	}	
	else if (new_size > Size() && new_size <= Capacity())
	{
		start = Size();
		end = m_size = new_size;
	}
	else if (new_size > Capacity())
	{
		start = Size();
		ChangeCapacity(new_size);
		m_size = new_size;
		end = Capacity();
	}

	Init(start, end, t);
}

template <typename T>
void DVector<T>::Init(size_t start_index, size_t end_index, const T& t)
{
	for (size_t i = start_index; i < end_index; ++i)
	{
		new (&m_data[i]) T(t);
	}
}

} // namespace rd90
} // namespace ilrd
