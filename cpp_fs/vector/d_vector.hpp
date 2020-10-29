/*
Dynamic vector is a random access dynamic array. 
Template class - can hold any types as long as they support:
    - copy initialization and destruction
    - assignment operator

Main operations on vector:
    -   Push back - adds an element to the end of the vector
    -   Pop back - removes the last element in the vector
    -   get capacity - returns the current capacity of the vector
    -   get size - returns the current number of elements in the vector
    -   operator[] const- retrieve element from specific index (read only)
    -   operator[] - retrieve access to specific index (read / write)
    -   resize - reallocates and initializes memory to the new capacity
    -   reserve - reallocates uninitialized memory to the new capacity
*/
#pragma once

#include <cstring>
#include <cstddef> //size_t

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
    void PushBack(const T& data);
    void PopBack();
    size_t Size() const;
    size_t Capacity() const;
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    void Resize(size_t new_size, T t = T());
    void Reserve(size_t new_size);

private:
    DVector(const DVector& other);
    DVector& operator=(const DVector& other);

    size_t capacity;
    size_t size;
    T *data;    // array of T members
};


template <typename T>
DVector<T>::DVector(size_t init_size) : capacity(init_size),
                                        size(init_size),
                                        data(new T[capacity])

{
        
}

template <typename T>
DVector<T>::~DVector()
{
    delete[] data;     
}

template <typename T>
void DVector<T>::PushBack(const T& data)
{
    ++size;

    if(size >= capacity)
    {
        T *tmp_data = new T[capacity * INC_FACTOR];
        memcpy(tmp_data, this->data, (size - 1) * sizeof(T));

        delete[] this->data;
        this->data = tmp_data;

        capacity *= 2;
    }

    this->data[size - 1] = data;

}



} // namespace rd90
} // namespace ilrd