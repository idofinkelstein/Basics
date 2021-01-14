#include <cstdlib>
#include <iostream>
#include <cstring>

#include "storage.hpp"

namespace ilrd
{
namespace rd90
{



IStorage::IStorage(/* args */)
{
}



Volatile::Volatile() : m_storageBuffer(new char[256 * M]) {}
/*---------------------------------------------------------------------------*/
Volatile::~Volatile()
{
    delete[] m_storageBuffer;
}
/*---------------------------------------------------------------------------*/
void Volatile::Store(char *data, size_t offset)
{
    std::cout << "Write: " << K << ", " << offset << "." << std::endl;
    memcpy(m_storageBuffer + offset, data, K);
}
/*---------------------------------------------------------------------------*/
void Volatile::Read(char *data, size_t offset)
{
    std::cout << "Read: " << K << ", " << offset << "." << std::endl;
    memcpy(data, m_storageBuffer + offset, K);
}

}
}