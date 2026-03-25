// #ifndef PARSER_H
// #define PARSER_H

// #include <iostream>
// // #include <arpa/inet.h> // ntohs, ntohl
// #include "packet.h"

// namespace CaptureService
// {

//          struct EthernetHeader
//          {
//                   uint8_t dest[6];
//                   uint8_t src[6];
//                   uint16_t type;
//          };

//          struct IPv4Header
//          {
//                   uint8_t version_ihl;
//                   uint8_t tos;
//                   uint16_t total_length;
//                   uint16_t id;
//                   uint16_t flags_fragment;
//                   uint8_t ttl;
//                   uint8_t protocol;
//                   uint16_t checksum;
//                   uint32_t src_ip;
//                   uint32_t dst_ip;
//          };

//          struct TCPHeader
//          {
//                   uint16_t src_port;
//                   uint16_t dst_port;
//          };

//          struct UDPHeader
//          {
//                   uint16_t src_port;
//                   uint16_t dst_port;
//          };

//          class Parser
//          {
//          public:
//                   static void parse(const Packet &pkt)
//                   {
//                            if (pkt.data.size() < 34)
//                                     return;

//                            const uint8_t *data = pkt.data.data();

//                            // Ethernet
//                            EthernetHeader *eth = (EthernetHeader *)data;
//                            uint16_t eth_type = ntohs(eth->type);

//                            if (eth_type != 0x0800)
//                            {
//                                     std::cout << "Non-IPv4 Packet\n";
//                                     return;
//                            }

//                            // IPv4
//                            IPv4Header *ip = (IPv4Header *)(data + 14);
//                            uint8_t protocol = ip->protocol;

//                            char src_ip[INET_ADDRSTRLEN];
//                            char dst_ip[INET_ADDRSTRLEN];

//                            inet_ntop(AF_INET, &ip->src_ip, src_ip, sizeof(src_ip));
//                            inet_ntop(AF_INET, &ip->dst_ip, dst_ip, sizeof(dst_ip));

//                            std::cout << "Src IP: " << src_ip << " | Dst IP: " << dst_ip;

//                            int ip_header_len = (ip->version_ihl & 0x0F) * 4;

//                            // TCP
//                            if (protocol == 6)
//                            {
//                                     TCPHeader *tcp = (TCPHeader *)(data + 14 + ip_header_len);
//                                     std::cout << " | Protocol: TCP";
//                                     std::cout << " | Src Port: " << ntohs(tcp->src_port);
//                                     std::cout << " | Dst Port: " << ntohs(tcp->dst_port);
//                            }

//                            // UDP
//                            else if (protocol == 17)
//                            {
//                                     UDPHeader *udp = (UDPHeader *)(data + 14 + ip_header_len);
//                                     std::cout << " | Protocol: UDP";
//                                     std::cout << " | Src Port: " << ntohs(udp->src_port);
//                                     std::cout << " | Dst Port: " << ntohs(udp->dst_port);
//                            }

//                            std::cout << "\n";
//                   }
//          };

// }

// #endif


