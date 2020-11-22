
namespace ilrd
{
namespace rd90
{

class Function
{


class I_Function
{
    virtual void operator()(int) = 0;
    virtual ~I_Function();
};
    
template <typename T>
class FunctionProxy : public I_Function
{
public:
    void operator()(int);
    FunctionProxy((void)(T::*m_func)(int), T *t = NULL);
    explicit FunctionProxy();
private:
    T *m_obj;
    (void)(T::*m_func)(int);
};    

private:
    Function *m_ptr;
};




template <typename T>
Function::FunctionProxy<T>::FunctionProxy((void)(T::*m_func)(int), T *t)
{

}

template <typename T>
Function::FunctionProxy<T>::FunctionProxy()
{}


template <typename T>
void Function::FunctionProxy<T>::operator()(int num)
{
    (m_obj->*m_func)(num);
    
    
}





} // namespace rd90
} // namespace ilrd

