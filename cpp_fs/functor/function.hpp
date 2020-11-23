#include <iostream>
#include <memory>

namespace ilrd
{
namespace rd90
{

class Function
{
public:
    template <typename T>
    explicit Function(void(T::*m_fptr)(int a), T *t);
    void operator()(int);

class I_Function
{
//public:    
    virtual void operator()(int) = 0;
    virtual ~I_Function();
};
    


template <typename T>
class FunctionProxy : public I_Function
{
public:
    void operator()(int);
    FunctionProxy(void(T::*m_fptr)(int), T *t);
private:
    T *m_obj;
    void(T::*m_func)(int);
};    

private:
    std::shared_ptr<I_Function> m_ptr;  
};

void Function::operator()(int)
{
    
}

template <typename T>
Function::Function(void(T::*m_fptr)(int), T *t)
: m_ptr(new FunctionProxy<T>(m_fptr, t)) {}


template <typename T>
Function::FunctionProxy<T>::FunctionProxy(void(T::*m_fptr)(int), T *t)
: m_func(m_fptr), 
  m_obj(t) {}


template <typename T>
void Function::FunctionProxy<T>::operator()(int num)
{
    (m_obj->*m_func)(num);  
}





} // namespace rd90
} // namespace ilrd

