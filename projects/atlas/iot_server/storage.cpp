#include <cstdlib>

#include "storage.hpp"

namespace ilrd
{
namespace rd90
{

const int K = 1024;
const int M = K * K;

IStorage::IStorage(/* args */)
{
}

IStorage::~IStorage()
{
}


Volatile::Volatile() : m_storageBuffer(new char[256 * M]) {}

Volatile::~Volatile()
{
    delete[] m_storageBuffer;
}


}
}