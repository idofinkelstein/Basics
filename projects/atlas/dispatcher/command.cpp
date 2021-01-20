#include "command.hpp"


namespace ilrd
{
namespace rd90
{

Read::Read(CommandData *data) :
    m_header(data->m_header),
    m_bio(data->m_bio),
    m_iotFd(data->m_iotFd),
    m_idx(data->m_idx)
{}

void ilrd::rd90::Read::ExecuteRequest()
{
    msghdr message;
    InitMsg(message, m_header, 1);
    
    if (-1 == (sendmsg(m_iotFd, &message, 0)))
    {
        throw("sendmsg() failed");
    }

    delete[] message.msg_iov;
}
/*---------------------------------------------------------------------------*/
void ilrd::rd90::Read::ExecuteReplay()
{
    ReadAll(m_iotFd, m_bio->dataBuf + m_header.m_fragmentNum * SLICE_SIZE, m_header.m_len);
}
/*---------------------------------------------------------------------------*/
Write::Write(CommandData *data) :
    m_header(data->m_header),
    m_bio(data->m_bio),
    m_iotFd(data->m_iotFd),
    m_idx(data->m_idx)
{}
/*---------------------------------------------------------------------------*/
void ilrd::rd90::Write::ExecuteRequest()
{
    msghdr message;

    InitMsg(message, m_header, 2);

    message.msg_iov[1].iov_base = m_bio->dataBuf + m_idx * SLICE_SIZE;
    message.msg_iov[1].iov_len = SLICE_SIZE;

    if (-1 == (sendmsg(m_iotFd, &message, 0)))
    {
        throw("sendmsg() failed");
    }

    delete[] message.msg_iov;
}
/*---------------------------------------------------------------------------*/
void ilrd::rd90::Write::ExecuteReplay()
{
    // Do nothing.
}
/*---------------------------------------------------------------------------*/

void ilrd::rd90::ICommand::InitMsg(msghdr &message, AtlasHeader &header, int numOfFields)
{
    memset(&message, 0, sizeof(message));

    message.msg_iovlen = numOfFields;
    message.msg_iov = new struct iovec[message.msg_iovlen];

    message.msg_iov[0].iov_base = &header;
    message.msg_iov[0].iov_len = sizeof(header);
}

CommandData::CommandData(AtlasHeader &header, BioRequest *bio, int iotFd, int idx) :  
    m_header(header),
    m_bio(bio),
    m_iotFd(iotFd),
    m_idx(idx)
{}

}// rd90
}// ilrd