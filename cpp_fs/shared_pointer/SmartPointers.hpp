#include <cstddef>

#pragma once

/*---------------------------------------------------------------------------*/

namespace ilrd
{
namespace rd90
{

/************************   Classes declarations    **************************/

template <typename T>
class SharedPtr
{
public:
    explicit SharedPtr(T *ptr = NULL);
    ~SharedPtr();
    SharedPtr(const SharedPtr& other);

    SharedPtr& operator=(const SharedPtr& other);
    bool operator!();
    size_t UseCount() const;
	

    T *operator->() const;
    T& operator*() const;
    
private:
    T *m_ptr; 
    size_t *m_counter;

    void Cleanup();
};


template <typename T>
SharedPtr<T>::SharedPtr(T *ptr) : 
              m_ptr(ptr), 
              m_counter(new size_t(1)) {}

template <typename T>
SharedPtr<T>::~SharedPtr()
{
    Cleanup();
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& other) : 
              m_ptr(other.m_ptr),
              m_counter(&(++(*other.m_counter)))  {}


template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& other)
{
    if (this != &other)
    {
        Cleanup();
        m_counter = other.m_counter;
        m_ptr = other.m_ptr;
    }

    return (*this);
}

template <typename T>
bool SharedPtr<T>::operator!()
{
    return (m_ptr == NULL);
}

template <typename T>
void SharedPtr<T>::Cleanup()
{
    if (--(*m_counter) == 0)
    {
        delete m_ptr;
        delete m_counter;
    }
}

template <typename T>
size_t SharedPtr<T>::UseCount() const
{
    return (*m_counter);
}

template <typename T>
T *SharedPtr<T>::operator->() const
{
    return (m_ptr);
}

template <typename T>
T& SharedPtr<T>::operator*() const
{
    return (*m_ptr);
}

} //namespace rd90
} //namespace ilrd 


