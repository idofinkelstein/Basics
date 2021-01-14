#include "storage.hpp"
#include "iot_server.hpp"
#include "iot.hpp"

using namespace ilrd::rd90;

int main()
{
    std::shared_ptr<IStorage> heapStorage(new Volatile);
    std::shared_ptr<IServer> tcp(new TCPServer("29000"));

    Iot iot(heapStorage, tcp);
    iot.Run();
    
    

    return 0;
}