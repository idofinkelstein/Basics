#pragma once
#include <memory>

#include "storage.hpp"
#include "iot_server.hpp"
#include "atlas.hpp"

namespace ilrd
{
namespace rd90
{

static const int IOT_CMD_READ = 0;
static const int IOT_CMD_WRITE = 1;

class Iot
{
public:
    explicit Iot(std::shared_ptr<IStorage> storage, std::shared_ptr<IServer> server);
    ~Iot() = default;

    Iot(const Iot&) = delete;
    void operator=(const Iot&) = delete;

    void Run();
    void Send();
    void Recieve();
private:
    std::shared_ptr<IStorage> m_storage;
    std::shared_ptr<IServer>  m_server;
    AtlasHeader               m_header;
    int                       m_communicationFd;
};

}// rd90
}// ilrd90