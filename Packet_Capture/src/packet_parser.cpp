#include "packet_parser.h"
#include <winsock2.h>
#include <ws2tcpip.h>

namespace CaptureService
{

         void PacketParser::parse(const Packet &pkt)
         {
                  if (pkt.data.size() < 34)
                           return;

                  const uint8_t *data = pkt.data.data();

                  // ================= Ethernet =================
                  EthernetHeader *eth = (EthernetHeader *)data;
                  uint16_t eth_type = ntohs(eth->type);

                  if (eth_type != 0x0800)
                  {
                           std::cout << "Non-IPv4 Packet\n";
                           return;
                  }

                  // ================= IPv4 =================
                  IPv4Header *ip = (IPv4Header *)(data + 14);

                  char src_ip[INET_ADDRSTRLEN];
                  char dst_ip[INET_ADDRSTRLEN];

                  inet_ntop(AF_INET, &ip->src_ip, src_ip, sizeof(src_ip));
                  inet_ntop(AF_INET, &ip->dst_ip, dst_ip, sizeof(dst_ip));

                  int ip_header_len = (ip->version_ihl & 0x0F) * 4;

                  std::cout << "Src IP: " << src_ip
                            << " | Dst IP: " << dst_ip;

                  // ================= TCP =================
                  if (ip->protocol == 6)
                  {
                           TCPHeader *tcp = (TCPHeader *)(data + 14 + ip_header_len);

                           std::cout << " | Protocol: TCP";
                           std::cout << " | Src Port: " << ntohs(tcp->src_port);
                           std::cout << " | Dst Port: " << ntohs(tcp->dst_port);
                  }

                  // ================= UDP =================
                  else if (ip->protocol == 17)
                  {
                           UDPHeader *udp = (UDPHeader *)(data + 14 + ip_header_len);

                           std::cout << " | Protocol: UDP";
                           std::cout << " | Src Port: " << ntohs(udp->src_port);
                           std::cout << " | Dst Port: " << ntohs(udp->dst_port);
                  }

                  std::cout << "\n";
         }

}