#include <cstdlib>
#include <atomic>
#include <iostream>
#include <pthread.h>

namespace ilrd
{
namespace rd90
{

template<typename T>
class Singleton
{
public:
    explicit Singleton();
    ~Singleton();

    T* operator->();
    static void Cleanup();
    void GetCount();

    static T* Instance();
private:
    static T* instancePtr;
    static int instance_count;
};


template<typename T>
T* Singleton<T>::instancePtr = 0;

template<typename T>
int Singleton<T>::instance_count = 0;

template<typename T>
Singleton<T>::Singleton()
{
    Instance();
}

template<typename T>
T* Singleton<T>::operator->()
{
    return (instancePtr);
}

template<typename T>
Singleton<T>::~Singleton()
{
    
}

template<typename T>
void Singleton<T>::GetCount()
{
    std::cout << "num of instances = " << instance_count << std::endl;
}

template<typename T>
void Singleton<T>::Cleanup()
{
    delete (instancePtr);
    instancePtr = reinterpret_cast<T*>(0xDEADBEEF);
}


template<typename T>
T* Singleton<T>::Instance()
{
    if (instancePtr == 0)
    {
        static int initStarted = 0;

        if (!__atomic_test_and_set(&initStarted, __ATOMIC_ACQUIRE))
        {
            __atomic_store_n(&instancePtr, new T, __ATOMIC_SEQ_CST);
            ++instance_count;

            atexit(Cleanup);
        }
        /* spin lock */
        else while (__atomic_load_n(&instancePtr, __ATOMIC_SEQ_CST) == 0);       
    }

    return (instancePtr);
}

} // rd90
} // ilrd