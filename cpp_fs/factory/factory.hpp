#pragma once
#include <unordered_map>
#include <functional>

namespace ilrd
{
namespace rd90
{

template <typename BASE, typename KEY, typename ARG>
class Factory
{
public:
    template<typename TYPE>
    void Register(KEY key);

    BASE *Create(KEY key, ARG arg = ARG());

private:
    template<typename TYPE>
    static BASE *Instanciate(ARG arg = ARG());

    std::unordered_map<KEY, std::function<BASE*(ARG)> > m_types;
};

template<class BASE, class KEY, class ARG> 
template<class TYPE> 
void Factory<BASE, KEY, ARG>::Register(KEY key)
{
    std::function<BASE*(ARG)> f = Instanciate<TYPE>;
    m_types[key] =  f;
}

template<class BASE, class KEY, class ARG> 
BASE *Factory<BASE, KEY, ARG>::Create(KEY key, ARG arg)

{
    return m_types[key](arg);
}

template<class BASE, class KEY, class ARG> 
template<class TYPE> 
BASE *Factory<BASE, KEY, ARG>::Instanciate(ARG arg)
{
    return new TYPE(arg);
}


}// rd90
}// ilrd