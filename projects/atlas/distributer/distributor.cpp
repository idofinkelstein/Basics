#include "distributor.hpp"

namespace ilrd
{
namespace rd90
{

const int BLOCK_SIZE = 1024;

DistModulu::DistModulu(std::shared_ptr< std::vector<int> > fds)
{

}

void DistModulu::Distribute(const std::shared_ptr<ReqSlicer> &slicer)
{
    uint64_t offset = slicer->GetOffset();
    int iot = (offset / BLOCK_SIZE) / m_fds->size();
}







} // namespace rd90
} // namespace ilrd