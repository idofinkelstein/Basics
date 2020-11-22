
namespace ilrd
{
namespace rd90
{


class I_Function
{
    virtual void operator()(int) = 0;
};
    
template<typename T>
class Function : public I_Function
{
public:
    void operator()(int);
    explict Function(void(T::*m_func)(int), T *t);
private:
    T *m_obj;
    (void)(*T::m_func)(int);
};    


template<typename T>
void Function<T>::operator()(int num)
{
    m_func(num);
    
}





} // namespace rd90
} // namespace ilrd

