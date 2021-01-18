#include "command.hpp"


namespace ilrd
{
namespace rd90
{

void ilrd::rd90::Read::ExecuteRequest( AtlasHeader& header, BioRequest *bio, int iotFd, int idx)
{
    (void)idx;
    msghdr message;

    memset(&message, 0, sizeof(message));

    message.msg_iovlen = 1;
    message.msg_iov = new struct iovec[message.msg_iovlen];

    message.msg_iov[0].iov_base = &header;
    message.msg_iov[0].iov_len = sizeof(header);

    if (-1 == (sendmsg(iotFd, &message, 0)))
    {
        throw("sendmsg() failed");
    }

    delete[] message.msg_iov;
}
/*---------------------------------------------------------------------------*/
void ilrd::rd90::Read::ExecuteReplay(const AtlasHeader& header, BioRequest *bio, int iotFd)
{
    ReadAll(iotFd, bio->dataBuf + header.m_fragmentNum * SLICE_SIZE, header.m_len);
}
/*---------------------------------------------------------------------------*/
void ilrd::rd90::Write::ExecuteRequest( AtlasHeader& header, BioRequest *bio, int iotFd, int idx)
{
    msghdr message;

    memset(&message, 0, sizeof(message));

    message.msg_iovlen = 2;
    message.msg_iov = new struct iovec[message.msg_iovlen];

    message.msg_iov[0].iov_base = &header;
    message.msg_iov[0].iov_len = sizeof(header);
    message.msg_iov[1].iov_base = bio->dataBuf + idx * SLICE_SIZE;
    message.msg_iov[1].iov_len = SLICE_SIZE;

    if (-1 == (sendmsg(iotFd, &message, 0)))
    {
        throw("sendmsg() failed");
    }

    delete[] message.msg_iov;
}
/*---------------------------------------------------------------------------*/
void ilrd::rd90::Write::ExecuteReplay(const AtlasHeader& header, BioRequest *bio, int iotFd)
{
    // Do nothing.
    (void)header, (void)bio, (void)iotFd;
}
/*---------------------------------------------------------------------------*/

}// rd90
}// ilrd