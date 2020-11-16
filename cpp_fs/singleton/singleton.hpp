#include <cstdlib>
//#include <atomic>

template<typename T>
class Singleton
{
public:
    explicit Singleton(/* args */);
    ~Singleton();

    T* operator->();
    static void Cleanup();

    static Singleton* Instance();
private:
    static T* instancePtr;
};


template<typename T>
T* Singleton<T>::instancePtr = 0;

template<typename T>
Singleton<T>::Singleton(/* args */)
{
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
void Singleton<T>::Cleanup()
{
    delete (instancePtr);
}


template<typename T>
Singleton<T>* Singleton<T>::Instance()
{
    if (instancePtr == 0)
    {
        static int initStarted = 0;

        if (!__atomic_test_and_set(&initStarted, __ATOMIC_ACQUIRE))
        {
            __atomic_store(&instancePtr, new T, __ATOMIC_SEQ_CST);

            atexit(Cleanup);
        }
        else while (__atomic_load(&instancePtr, __ATOMIC_SEQ_CST) == 0)
        {
            /* code */
        }
        
    }

    return (instancePtr);
}