#pragma once
#include <unordered_map>
#include <functional>

namespace ilrd
{
namespace rd90
{

template <typename BASE, typename KEY>
class Factory
{
public:
    template<typename TYPE>
    void Register(KEY key);

    BASE *Create(KEY key);

private:
    template<typename TYPE>
    static BASE *Intanciate();

    std::unordered_map<KEY, std::function<BASE*(void)> > m_types;
};

template<class BASE, class KEY> 
template<class TYPE>
void Factory<BASE, KEY>::Register(KEY key)
{
    std::function<BASE*(void)> f = Intanciate<TYPE>;
    m_types[key] =  f;
}

template<class BASE, class KEY> 
BASE *Factory<BASE, KEY>::Create(KEY key)
{
    return m_types[key]();
}

template<class BASE, class KEY> 
template<class TYPE>
BASE *Factory<BASE, KEY>::Intanciate()
{
    return new TYPE();
}


}// rd90
}// ilrd