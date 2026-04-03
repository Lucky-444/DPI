#include "packet_parser.h"
#include <winsock2.h>
#include <ws2tcpip.h>
using namespace std;

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

                  std::cout << " | Src IP: " << src_ip << std::endl
                          << " | Dst IP: " << dst_ip << std::endl;

                  // ================= TCP =================
                  if (ip->protocol == 6)
                  {
                           TCPHeader *tcp = (TCPHeader *)(data + 14 + ip_header_len);

                           std::cout << " | Protocol: TCP" << endl;
                           std::cout << " | Src Port: " << ntohs(tcp->src_port) << std::endl;
                           std::cout << " | Dst Port: " << ntohs(tcp->dst_port) << std::endl;
                  }

                  // ================= UDP =================
                  else if (ip->protocol == 17)
                  {
                           UDPHeader *udp = (UDPHeader *)(data + 14 + ip_header_len);

                           std::cout << " | Protocol: UDP" << std::endl;
                           std::cout << " | Src Port: " << ntohs(udp->src_port) << std::endl;
                           std::cout << " | Dst Port: " << ntohs(udp->dst_port) << std::endl;
                  }

                  std::cout << "\n";
        }

        bool PacketParser::parsed(const Packet &pkt, ParsedPacket &out)
        {
                // Minimum Ethernet + IPv4 header size
                if (pkt.data.size() < 34)
                        return false;

                const uint8_t *data = pkt.data.data();

                // ===============================
                // 🔥 Ethernet Header
                // ===============================
                const EthernetHeader *eth = reinterpret_cast<const EthernetHeader *>(data);
                uint16_t eth_type = ntohs(eth->type);

                // Only IPv4
                if (eth_type != 0x0800)
                        return false;

                // ===============================
                // 🔥 IPv4 Header
                // ===============================
                const IPv4Header *ip = reinterpret_cast<const IPv4Header *>(data + 14);

                int ip_header_len = (ip->version_ihl & 0x0F) * 4;

                char src_ip[INET_ADDRSTRLEN];
                char dst_ip[INET_ADDRSTRLEN];

                inet_ntop(AF_INET, &(ip->src_ip), src_ip, INET_ADDRSTRLEN);
                inet_ntop(AF_INET, &(ip->dst_ip), dst_ip, INET_ADDRSTRLEN);

                out.src_ip = src_ip;
                out.dest_ip = dst_ip;
                out.has_ip = true;

                // ===============================
                // 🔥 Protocol Handling
                // ===============================
                if (ip->protocol == 6) // TCP
                {
                        const TCPHeader *tcp = reinterpret_cast<const TCPHeader *>(data + 14 + ip_header_len);

                        out.src_port = ntohs(tcp->src_port);
                        out.dest_port = ntohs(tcp->dst_port);
                        out.protocol = "TCP";
                }
                else if (ip->protocol == 17) // UDP
                {
                        const UDPHeader *udp = reinterpret_cast<const UDPHeader *>(data + 14 + ip_header_len);

                        out.src_port = ntohs(udp->src_port);
                        out.dest_port = ntohs(udp->dst_port);
                        out.protocol = "UDP";
                }
                else
                {
                        // Ignore other protocols
                        return false;
                }

                return true;
        }
}