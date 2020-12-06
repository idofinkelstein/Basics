#pragma once

#include <iostream>
#include <memory>


namespace ilrd
{
namespace rd90
{

template<typename>
class Function;

template<typename ARG, typename RET, typename S>
Function<RET(void)> Bind(RET(S::*func)(ARG arg), S *object, const ARG& arg);

template<typename ARG, typename RET>
Function<RET(void)> Bind(RET(*func)(ARG arg), const ARG& arg);

template<typename ARG, typename RET>
class Function<RET(void)>
{
public:

    explicit Function() {}

    // Free function ctor
    explicit Function(RET(fptr)(ARG), const ARG &arg);

    // Member function ctor
    template <typename S>
    Function(RET(S::*fptr)(ARG a), S *t, const ARG &arg);

    RET operator()();

private:
	class I_Function
	{
	public:    
		virtual RET operator()() = 0;
		virtual ~I_Function() = default;
	};

	// Handles calls of member function on an object    
	template <typename S>
	class MemberFunctionProxy : public I_Function
	{
	public:
		RET operator()();
		MemberFunctionProxy(RET(S::*fptr)(ARG), S *t, const ARG& arg);
	private:
		RET(S::*m_func)(ARG);
		S *m_obj;
		ARG m_arg;
	};    

	// Handled calls to free function
	class FreeFunctionProxy : public I_Function
	{
	public:
		RET operator()();
		FreeFunctionProxy(RET(fptr)(ARG), const ARG& arg);
	private:
		RET(*m_func)(ARG);
		ARG m_arg;
	};    

    std::shared_ptr<I_Function> m_ptr;  
};

/*----------------------class Function: definition---------------------------*/
template <typename ARG, typename RET>
template <typename S>
Function<RET(void)>::Function(RET(S::*fptr)(ARG), S *t)
: m_ptr(new MemberFunctionProxy<S>(fptr, t)) {}

template <typename ARG, typename RET>
Function<RET(void)>::Function(RET(fptr)(ARG))
: m_ptr(new FreeFunctionProxy(fptr)) {}

template <typename ARG, typename RET>
RET Function<RET(void)>::operator()()
{
    return (*m_ptr)();
}

/*-------------------class MemberFunctionProxy: definition------------------------------*/
template <typename ARG, typename RET>
template <typename S>
Function<RET(void)>::MemberFunctionProxy<S>::MemberFunctionProxy(RET(S::*fptr)(ARG), S *t, const ARG& arg)
: m_func(fptr), 
  m_obj(t),
  m_arg(arg) {}

template <typename ARG, typename RET>
template<typename S>
RET Function<RET(void)>::MemberFunctionProxy<S>::operator()()
{
    return (m_obj->*m_func)(m_arg);  
}

/*-------------------class FreeFunctionProxy: definition------------------------------*/
template<typename ARG, typename RET>
Function<RET(void)>::FreeFunctionProxy::FreeFunctionProxy(RET(fptr)(ARG), const ARG& arg)
: m_func(fptr),
  m_arg(arg)
{}

template<typename ARG, typename RET>
RET Function<RET(void)>::FreeFunctionProxy::operator()()
{
    return m_func(m_arg);
}

template<typename ARG, typename RET>
Function<RET(void)> Bind(RET(*func)(ARG arg), ARG arg)
{
    return (Function<RET(void)>(func, arg));
}

template<typename ARG, typename RET, typename S>
Function<RET(void)> Bind(RET(S::*func)(ARG arg), S *object, ARG arg)
{
    return (Function<RET(void)>(func,object, arg));
}

} // namespace rd90
} // namespace ilrd

