#include <cstdlib>
#include <cstdio>
#include <iostream>

struct Item
{
    int m_val;
    size_t m_timestamp;
};


class Arr
{
public:
    explicit Arr(size_t size);
    int GetVal(size_t idx);
    void SetVal(size_t idx, int val);
    void SetAll(int val);
    friend class Item;

private:
    Item *arr;
    Item all;
    static size_t s_timestamp;
};

size_t Arr::s_timestamp = 0;


Arr::Arr(size_t size) : arr(new Item[size])
{
    for (size_t i = 0; i < size; ++i)
    {
        arr[i].m_timestamp = 0;
        arr[i].m_val = 0;
    }
    all.m_timestamp = 0;
    all.m_val = 0;
}


void Arr::SetVal(size_t idx, int val)
{
    arr[idx].m_val = val;
    arr[idx].m_timestamp = s_timestamp++;
}

void Arr::SetAll(int val)
{
    all.m_val = val;
    all.m_timestamp = s_timestamp++;
}

int Arr::GetVal(size_t idx)
{
    if (arr[idx].m_timestamp > all.m_timestamp)
    {
        return arr[idx].m_val;
    }

    return all.m_val;
}

int main ()
{
    Arr arr(8);

    for (int i = 0; i < 8; ++i)
    {
        arr.SetVal(i, i);
    }

    for (int i = 0; i < 8; ++i)
    {
        std::cout << arr.GetVal(i) << std::endl;
    }

    arr.SetAll(12);

    for (int i = 0; i < 8; ++i)
    {
        std::cout << arr.GetVal(i) << std::endl;
    }

    return 0;
}

