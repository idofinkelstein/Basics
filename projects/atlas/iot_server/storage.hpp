#pragma once

namespace ilrd
{
namespace rd90
{


class IStorage
{
private:
    /* data */
public:
    IStorage(/* args */);
    ~IStorage();
};

class Volatile : public IStorage
{
public:
    explicit Volatile();
    ~Volatile();

    Volatile(const Volatile& other) = delete;
    void operator=(const Volatile& other) = delete;
private:
    char *m_storageBuffer;

};

class NonVolatile : public IStorage
{
public:

    NonVolatile(const NonVolatile& other) = delete;
    void operator=(const NonVolatile& other) = delete;

private:
    int m_storageFile;

};

}// rd90
}// ilrd