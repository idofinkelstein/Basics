template<typename T>
class Singleton
{
private:
    static T* instancePtr;
public:
    explicit Singleton(/* args */);
    ~Singleton();

    static Singleton* Instance();
};

template<typename T>
Singleton<T>::Singleton(/* args */)
{
}

template<typename T>
Singleton<T>::~Singleton()
{
    delete instancePtr;
}

template<typename T>
Singleton<T>* Singleton<T>::Instance()
{
    static T* instancePtr = 0;

    return (instancePtr);
}