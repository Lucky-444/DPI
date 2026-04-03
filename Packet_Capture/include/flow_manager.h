#ifndef FLOW_MANAGER_H
#define FLOW_MANAGER_H

#include<bits/stdc++.h>
#include <string>
#include <unordered_map>
#include <iostream>

namespace CaptureService
{

         // Unique Flow Key
         struct FlowKey
         {
                  std::string src_ip;
                  std::string dst_ip;
                  uint16_t src_port;
                  uint16_t dst_port;

                  bool operator==(const FlowKey &other) const
                  {
                           return src_ip == other.src_ip &&
                                  dst_ip == other.dst_ip &&
                                  src_port == other.src_port &&
                                  dst_port == other.dst_port;
                  }
         };

         // Hash function for unordered_map
         struct FlowKeyHash
         {
                  size_t operator()(const FlowKey &k) const
                  {
                           return std::hash<std::string>()(k.src_ip + k.dst_ip) ^
                                  std::hash<int>()(k.src_port) ^
                                  std::hash<int>()(k.dst_port);
                  }
         };

         // Flow Data
         struct FlowData
         {
                  int packet_count = 0;
                  int total_bytes = 0;
         };

         class FlowManager
         {
         public:
                  void addPacket(const std::string &src_ip,
                                 const std::string &dst_ip,
                                 uint16_t src_port,
                                 uint16_t dst_port,
                                 uint32_t bytes);

                  void printFlows();

         private:
                  std::unordered_map<FlowKey, FlowData, FlowKeyHash> flows;
         };

} // namespace CaptureService

#endif