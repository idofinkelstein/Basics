#include <iostream>
#include <memory>

namespace ilrd
{
namespace rd90
{

class Function
{
public:
    // Free function ctor
    explicit Function(void(fptr)(int));

    // Member function ctor
    template <typename T>
    Function(void(T::*fptr)(int a), T *t);

    void operator()(int);

class I_Function
{
public:    
    virtual void operator()(int) = 0;
    virtual ~I_Function() = default;
};
    
template <typename T>
class MemberFunctionProxy : public I_Function
{
public:
    void operator()(int);
    MemberFunctionProxy(void(T::*fptr)(int), T *t);
private:
    void(T::*m_func)(int);
    T *m_obj;
};    

class FreeFunctionProxy : public I_Function
{
public:
    void operator()(int);
    FreeFunctionProxy(void(fptr)(int));
private:
    void(*m_func)(int);
};    

private:
    std::shared_ptr<I_Function> m_ptr;  
};

void Function::operator()(int val)
{
    (*m_ptr)(val);
}

template <typename T>
Function::Function(void(T::*fptr)(int), T *t)
: m_ptr(new MemberFunctionProxy<T>(fptr, t)) {}

Function::Function(void(fptr)(int))
: m_ptr(new FreeFunctionProxy(fptr)) {}


template <typename T>
Function::MemberFunctionProxy<T>::MemberFunctionProxy(void(T::*fptr)(int), T *t)
: m_func(fptr), 
  m_obj(t) {}


template <typename T>
void Function::MemberFunctionProxy<T>::operator()(int num)
{
    (m_obj->*m_func)(num);  
}

Function::FreeFunctionProxy::FreeFunctionProxy(void(fptr)(int)) : m_func(fptr)
{}

void Function::FreeFunctionProxy::operator()(int val)
{
    m_func(val);
}


} // namespace rd90
} // namespace ilrd

