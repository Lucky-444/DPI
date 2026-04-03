#include "flow_manager.h"

namespace CaptureService
{

         void FlowManager::addPacket(const std::string &src_ip,
                                     const std::string &dst_ip,
                                     uint16_t src_port,
                                     uint16_t dst_port,
                                     uint32_t bytes)
         {
                  FlowKey key{src_ip, dst_ip, src_port, dst_port};

                  flows[key].packet_count++;
                  flows[key].total_bytes += bytes;
         }

         void FlowManager::printFlows()
         {
                  for (auto &entry : flows)
                  {
                           auto &k = entry.first;
                           auto &v = entry.second;

                           std::cout << k.src_ip << ":" << k.src_port
                                     << " → "
                                     << k.dst_ip << ":" << k.dst_port << "\n";

                           std::cout << "Packets: " << v.packet_count
                                     << " | Bytes: " << v.total_bytes << "\n\n";
                  }
         }

}