#pragma once

#include <cstddef>

namespace ilrd
{
namespace rd90
{

const int K = 1024;
const int M = K * K;

class IStorage
{
private:
    /* data */
public:
    IStorage(/* args */);
    virtual ~IStorage() = default;
    virtual void Store(char *data, size_t offset) = 0;
    virtual void Read(char *data, size_t offset) = 0;
};

class Volatile : public IStorage
{
public:
    explicit Volatile();
    ~Volatile();

    void Store(char *data, size_t offset);
    void Read(char *data, size_t offset);

    Volatile(const Volatile& other) = delete;
    void operator=(const Volatile& other) = delete;
private:
    char *m_storageBuffer;

};

class NonVolatile : public IStorage
{
public:
    // TODO:
    // explicit NonVolatile();

    NonVolatile(const NonVolatile& other) = delete;
    void operator=(const NonVolatile& other) = delete;

    void Store(char *data, size_t offset){}
    void Read(char *data, size_t offset){}


private:
    int m_storageFile;

};

}// rd90
}// ilrd