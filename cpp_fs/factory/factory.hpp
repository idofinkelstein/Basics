#pragma once

#include <unordered_map> // unordered map
#include <memory>        // shared pointer

namespace ilrd
{
namespace rd90
{

// this class creates instances of derived class from base class BASE and returns
// a shared pointer to that instance.
template <typename BASE, typename KEY, typename ARG>
class Factory
{
public:
    // register a concrete class acording to some key.
    template<typename TYPE>
    void Register(KEY key);

    // virtural constructor to use by client.
    std::shared_ptr<BASE> Create(KEY key, const ARG& arg);

private:
    template<typename TYPE>
    static std::shared_ptr<BASE> Instanciate(const ARG& arg);

    std::unordered_map<KEY, std::shared_ptr<BASE>(*)(const ARG&) > m_types;
};

/*-----------------------class Factory Definition-----------------------------*/
/*----------------------------------------------------------------------------*/
template<class BASE, class KEY, class ARG> 
template<class TYPE> 
void Factory<BASE, KEY, ARG>::Register(KEY key)
{
    m_types[key] =  Instanciate<TYPE>;
}
/*----------------------------------------------------------------------------*/
template<class BASE, class KEY, class ARG> 
std::shared_ptr<BASE> Factory<BASE, KEY, ARG>::Create(KEY key, const ARG &arg)
{
    return m_types[key](arg);
}
/*----------------------------------------------------------------------------*/
template<class BASE, class KEY, class ARG> 
template<class TYPE> 
std::shared_ptr<BASE> Factory<BASE, KEY, ARG>::Instanciate(const ARG &arg)
{
    return std::shared_ptr<BASE>(new TYPE(arg));
}
/*----------------------------------------------------------------------------*/

}// rd90
}// ilrd