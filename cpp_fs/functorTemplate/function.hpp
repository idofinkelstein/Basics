#include <iostream>
#include <memory>


namespace ilrd
{
namespace rd90
{

template<typename ARG, typename RET>
class Function
{
public:

    // Free function ctor
    explicit Function(RET(fptr)(ARG));

    // Member function ctor
    template <typename S>
    Function(RET(S::*fptr)(ARG a), S *t);

    RET operator()(ARG);

class I_Function
{
public:    
    virtual RET operator()(ARG) = 0;
    virtual ~I_Function() = default;
};

// Handles calls of member function on an object    
template <typename S>
class MemberFunctionProxy : public I_Function
{
public:
    RET operator()(ARG);
    MemberFunctionProxy(RET(S::*fptr)(ARG), S *t);
private:
    RET(S::*m_func)(ARG);
    S *m_obj;
};    

// Handled calls to free function
class FreeFunctionProxy : public I_Function
{
public:
    RET operator()(ARG);
    FreeFunctionProxy(RET(fptr)(ARG));
private:
    RET(*m_func)(ARG);
};    

private:
    std::shared_ptr<I_Function> m_ptr;  
};

/*----------------------class Function: definition---------------------------*/
template <typename ARG, typename RET>
template <typename S>
Function<ARG, RET>::Function(RET(S::*fptr)(ARG), S *t)
: m_ptr(new MemberFunctionProxy<S>(fptr, t)) {}

template <typename ARG, typename RET>
Function<ARG, RET>::Function(RET(fptr)(ARG))
: m_ptr(new FreeFunctionProxy(fptr)) {}

template <typename ARG, typename RET>
RET Function<ARG, RET>::operator()(ARG val)
{
    return (*m_ptr)(val);
}

/*-------------------class MemberFunctionProxy: definition------------------------------*/
template <typename ARG, typename RET>
template <typename S>
Function<ARG, RET>::MemberFunctionProxy<S>::MemberFunctionProxy(RET(S::*fptr)(ARG), S *t)
: m_func(fptr), 
  m_obj(t) {}

template <typename ARG, typename RET>
template<typename S>
RET Function<ARG, RET>::MemberFunctionProxy<S>::operator()(ARG num)
{
    return (m_obj->*m_func)(num);  
}

/*-------------------class FreeFunctionProxy: definition------------------------------*/
template<typename ARG, typename RET>
Function<ARG, RET>::FreeFunctionProxy::FreeFunctionProxy(RET(fptr)(ARG)) : m_func(fptr)
{}

template<typename ARG, typename RET>
RET Function<ARG, RET>::FreeFunctionProxy::operator()(ARG val)
{
    return m_func(val);
}

} // namespace rd90
} // namespace ilrd

