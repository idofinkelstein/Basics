#include "iot.hpp"

namespace ilrd
{
namespace rd90
{

Iot::Iot(std::shared_ptr<IStorage> storage, std::shared_ptr<IServer> server)
: m_storage(storage), 
  m_server(server) {}
/*---------------------------------------------------------------------------*/
void ilrd::rd90::Iot::Send()
{

}

/*---------------------------------------------------------------------------*/
void Iot::Recieve()
{

}

/*---------------------------------------------------------------------------*/
void Iot::Run()
{
    msghdr message;
    char *buff = new char[K];
    memset(&message, 0, sizeof(message));

    while (true)
    {
        m_communicationFd = m_server->Accept();

        
        
        while (true)
        {
            int bytesRead = 0;

            if(-1 ==(bytesRead = recv(m_communicationFd, &m_header, sizeof(AtlasHeader), 0)))
            {
                puts("recv");
                throw("recv()");
            }

            if (bytesRead == 0)
            {break;}

            if (m_header.m_type == IOT_CMD_WRITE)
            {
                recv(m_communicationFd, buff, K, 0);
                m_storage->Store(buff, m_header.m_iotOffset);
                send(m_communicationFd, &m_header, sizeof(AtlasHeader), 0);
            }
            else if (m_header.m_type == IOT_CMD_READ)
            {
                message.msg_iovlen = 2;
                message.msg_iov = new struct iovec[message.msg_iovlen];
                message.msg_iov[0].iov_base = &m_header;
                message.msg_iov[0].iov_len = sizeof(AtlasHeader);
                m_storage->Read(buff, m_header.m_iotOffset);
                message.msg_iov[1].iov_base = buff;
                message.msg_iov[1].iov_len = K;

                if (-1 == (sendmsg(m_communicationFd, &message, 0)))
                {
                    puts("sendmsg");
                    throw("sendmsg() failed");
                }

                delete[] message.msg_iov;
            }
        }
    }
}




}// rd90
}// ilrd90